#include <engine/shared/config.h>
#include <game/client/gameclient.h>
#include "translator.h"
#include <curl/curl.h>
#include <engine/shared/json.h>

// Callback for CURL to write response data
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void CTranslate::OnInit()
{
    m_State.AutoTranslate = false;
    str_copy(m_State.TargetLang, "en", sizeof(m_State.TargetLang));
    m_LastTargetId = -1;
}

void CTranslate::OnReset()
{
    // Clear any pending translations
    while(!m_State.TranslationQueue.empty())
        m_State.TranslationQueue.pop();
}

void CTranslate::OnConsoleInit()
{
    Console()->Register("Translate", "s[message] ?s[lang]", CFGFLAG_CLIENT, ConTranslate, this, "Translate message");
    Console()->Register("TargetTranslate", "s[target] s[message] ?s[lang]", CFGFLAG_CLIENT, ConTranslateWhisper, this, "Translate and mention user and message");
    Console()->Register("LastTranslate", "s[message]", CFGFLAG_CLIENT, ConLastTranslate, this, "Quick translate to the last target used");
    Console()->Register("AutoTranslate", "?s[lang]", CFGFLAG_CLIENT, ConAutoTranslate, this, "Toggle auto translation");
}

bool CTranslate::TranslateText(const char *pText, const char *pTargetLang, const char *pSourceLang, std::string &Result)
{
    CURL *curl = curl_easy_init();
    if(!curl)
        return false;

    char *escapedText = curl_easy_escape(curl, pText, 0);
    char aUrl[1024];

    const char *pSrcLang = (pSourceLang && pSourceLang[0]) ? pSourceLang : "auto";
    
    str_format(aUrl, sizeof(aUrl), 
        "https://translate.googleapis.com/translate_a/single?client=gtx&sl=%s&tl=%s&dt=t&q=%s",
        pSrcLang, pTargetLang, escapedText);

    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, aUrl);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

    CURLcode res = curl_easy_perform(curl);
    curl_free(escapedText);
    curl_easy_cleanup(curl);

    if(res != CURLE_OK)
    {
        Result = "Translation failed: Network error";
        return false;
    }

    // Parse JSON using DDNet's JSON parser
    json_settings JsonSettings;
    mem_zero(&JsonSettings, sizeof(JsonSettings));
    char aError[256];
    json_value *pJson = json_parse_ex(&JsonSettings, response.c_str(), response.length(), aError);
    
    if(!pJson)
    {
        Result = "Translation failed: Invalid response";
        return false;
    }

    // Navigate JSON structure for the free API response format
    if(pJson->type == json_array)
    {
        const json_value* pTranslations = json_array_get(pJson, 0);
        if(pTranslations && pTranslations->type == json_array)
        {
            const json_value* pTransPair = json_array_get(pTranslations, 0);
            if(pTransPair && pTransPair->type == json_array)
            {
                const json_value* pTransText = json_array_get(pTransPair, 0);
                if(pTransText && pTransText->type == json_string)
                {
                    Result = pTransText->u.string.ptr;
                    json_value_free(pJson);
                    return true;
                }
            }
        }
    }

    json_value_free(pJson);
    Result = "Translation failed: Invalid format";
    return false;
}

void CTranslate::StartNextTranslation()
{
    if(m_State.TranslationQueue.empty() || m_State.CurrentTranslation.valid())
        return;

    m_State.CurrentRequest = m_State.TranslationQueue.front();
    m_State.HasCurrentRequest = true;
    m_State.TranslationQueue.pop();

    m_State.CurrentTranslation = std::async(std::launch::async,
        [this, req = m_State.CurrentRequest]() -> std::string {
            std::string result;
            if(TranslateText(req.aMessage, req.aTargetLang, 
                         req.HasSourceLang ? req.aSourceLang : nullptr,
                         result))
            {
                return result;
            }
            else
            {
                return std::string("");
            }
        });
}

void CTranslate::HandleCompletedTranslation() 
{
    if(!m_State.CurrentTranslation.valid())
        return;
    
    if(m_State.CurrentTranslation.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
    {
        std::string result = m_State.CurrentTranslation.get();
        if(!result.empty() && m_State.HasCurrentRequest)
        {
            char aBuffer[512];
            if(m_State.CurrentRequest.Auto)
            {
                str_format(aBuffer, sizeof(aBuffer), "%s [%s]", result.c_str(), m_State.CurrentRequest.aMessage);
                m_pClient->m_Chat.AddLine(m_State.CurrentRequest.Sender, m_State.CurrentRequest.Team, aBuffer);
            }
            else if(m_State.CurrentRequest.IsWhisper)
            {
                str_format(aBuffer, sizeof(aBuffer), "%s: %s", 
                    m_pClient->m_aClients[m_State.CurrentRequest.ClientId].m_aName,
                    result.c_str(),
                    m_State.CurrentRequest.aMessage);
                m_pClient->m_Chat.SendChat(0, aBuffer);
            }
            else
            {
                str_format(aBuffer, sizeof(aBuffer), "%s", result.c_str(), m_State.CurrentRequest.aMessage);
                m_pClient->m_Chat.SendChat(0, aBuffer);
            }
        }
        m_State.HasCurrentRequest = false;
    }
}

void CTranslate::OnRender()
{
    if(!m_State.CurrentTranslation.valid() && !m_State.TranslationQueue.empty())
    {
        StartNextTranslation();
    }
    HandleCompletedTranslation();
}

void CTranslate::ConTranslate(IConsole::IResult *pResult, void *pUserData)
{
    CTranslate *pSelf = (CTranslate*)pUserData;
    if(pResult->NumArguments() < 1)
        return;

    TranslationRequest req;
    req.IsWhisper = false;
    req.Auto = false;
    req.HasSourceLang = false;

    str_copy(req.aMessage, pResult->GetString(0));

    if(pResult->NumArguments() > 1)
    {
        const char *pLang = pResult->GetString(1);
        str_copy(req.aTargetLang, pLang);
        str_copy(pSelf->LastTranslateLang, pLang);
    }
    else
    {
        if(pSelf->LastTranslateLang[0] != '\0')
            str_copy(req.aTargetLang, pSelf->LastTranslateLang);
        else
            str_copy(req.aTargetLang, pSelf->m_State.TargetLang);
    }

    pSelf->QueueTranslation(req);
}

void CTranslate::ConTranslateWhisper(IConsole::IResult *pResult, void *pUserData)
{
    CTranslate *pSelf = (CTranslate*)pUserData;
    if(pResult->NumArguments() < 2)
        return;

    const char *pTarget = pResult->GetString(0);
    int ClientId = pSelf->GameClient()->GetClientId(pTarget);
    if(ClientId < 0)
    {
        pSelf->GameClient()->aMessage("Could not find the specified player");
        return;
    }
    
    TranslationRequest req;
    req.ClientId = ClientId;
    req.IsWhisper = true;
    req.Auto = false;
    req.HasSourceLang = false;
    pSelf->m_LastTargetId = req.ClientId;
    str_copy(req.aMessage, pResult->GetString(1));
    
    if(pResult->NumArguments() > 2)
    {
        const char *pLang = pResult->GetString(1);
        str_copy(req.aTargetLang, pLang);
        str_copy(pSelf->LastTranslateLang, pLang);
    }
    else
    {
        if(pSelf->LastTranslateLang[0] != '\0')
            str_copy(req.aTargetLang, pSelf->LastTranslateLang);
        else
            str_copy(req.aTargetLang, pSelf->m_State.TargetLang);
    }
    
    pSelf->QueueTranslation(req);
}

void CTranslate::ConLastTranslate(IConsole::IResult *pResult, void *pUserData)
{
    CTranslate *pSelf = (CTranslate*)pUserData;
    if(pResult->NumArguments() < 1)
        return;

    if(pSelf->m_LastTargetId < 0)
    {
        pSelf->GameClient()->aMessage("No last translate target available");
        return;
    }
    
    TranslationRequest req;
    req.ClientId = pSelf->m_LastTargetId;
    req.IsWhisper = true;
    req.Auto = false;
    req.HasSourceLang = false;

    str_copy(req.aMessage, pResult->GetString(0));

    if(pResult->NumArguments() > 1)
    {
        const char *pLang = pResult->GetString(1);
        str_copy(req.aTargetLang, pLang);
        str_copy(pSelf->LastTranslateLang, pLang);
    }
    else
    {
        if(pSelf->LastTranslateLang[0] != '\0')
            str_copy(req.aTargetLang, pSelf->LastTranslateLang);
        else
            str_copy(req.aTargetLang, pSelf->m_State.TargetLang);
    }
    
    pSelf->QueueTranslation(req);
}



void CTranslate::ConAutoTranslate(IConsole::IResult *pResult, void *pUserData)
{
    CTranslate *pSelf = (CTranslate*)pUserData;
    
    if(pResult->NumArguments() > 0)
    {
        str_copy(pSelf->m_State.TargetLang, pResult->GetString(0));
        str_copy(g_Config.m_ClAutoTranslateLang, pResult->GetString(0));
    }


    pSelf->m_State.AutoTranslate = !pSelf->m_State.AutoTranslate;
    g_Config.m_ClAutoTranslate = !g_Config.m_ClAutoTranslate;
    
    if(pSelf->m_State.AutoTranslate)
        pSelf->GameClient()->aMessage("Auto-translation enabled");
    else
        pSelf->GameClient()->aMessage("Auto-translation disabled");
}