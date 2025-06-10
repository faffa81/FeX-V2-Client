#ifndef GAME_CLIENT_COMPONENTS_FEX_TRANSLATE_H
#define GAME_CLIENT_COMPONENTS_FEX_TRANSLATE_H

#include <game/client/component.h>
#include <engine/shared/console.h>
#include <queue>
#include <string>
#include <future>


struct TranslationRequest {
    int ClientId;
    bool IsWhisper;
    bool Auto;
    int Sender;
    int Team;
    char aMessage[256];
    char aTargetLang[8];
    char aSourceLang[8];
    bool HasSourceLang;
};

struct TranslationState {
    bool AutoTranslate;
    char TargetLang[8];
    std::queue<TranslationRequest> TranslationQueue;
    std::future<std::string> CurrentTranslation;
    TranslationRequest CurrentRequest;
    bool HasCurrentRequest = false;

    bool HasPendingTranslations() const {
        return !TranslationQueue.empty() || 
               (CurrentTranslation.valid() && 
                CurrentTranslation.wait_for(std::chrono::seconds(0)) != std::future_status::ready);
    }
};

class CTranslate : public CComponent
{
    TranslationState m_State;

    int m_LastTargetId;
    char LastTranslateLang[8];
public:
    virtual void OnInit() override;
    virtual void OnReset() override;
    virtual void OnRender() override;
    virtual void OnConsoleInit() override;
    virtual int Sizeof() const override { return sizeof(*this); }

    void QueueTranslation(const TranslationRequest& req) {
        m_State.TranslationQueue.push(req);
    }

    static void ConLastTranslate(IConsole::IResult *pResult, void *pUserData);
    static void ConTranslate(IConsole::IResult *pResult, void *pUserData);
    static void ConTranslateWhisper(IConsole::IResult *pResult, void *pUserData);
    static void ConAutoTranslate(IConsole::IResult *pResult, void *pUserData);

    void OnTranslationComplete(const char* pOriginal, const char* pTranslated);

private:
    bool TranslateText(const char *pText, const char *pTargetLang, const char *pSourceLang, std::string &Result);
    void StartNextTranslation();
    void HandleCompletedTranslation();
};

#endif