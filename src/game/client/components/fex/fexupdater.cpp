#include "fexupdater.h"

#include <base/system.h>
#include <engine/client.h>
#include <engine/engine.h>
#include <engine/external/json-parser/json.h>
#include <engine/shared/json.h>
#include <cstdlib>   // for system()
#include <stdio.h>
#include <string.h>
#include <game/client/components/fex/fexversion.h>

using std::string;

// Helper: Build updater URL given the file and release tag.
static const char *BuildUpdaterUrl(char *pBuf, int BufSize, const char *pFile, const char *pTag)
{
    CConsole *m_pConsole;
    str_format(pBuf, BufSize, "https://github.com/faffa81/FeX-V2-Client/releases/download/%s/%s", pTag, pFile);
    m_pConsole->Print(IConsole::OUTPUT_LEVEL_STANDARD, "FeX[updater]", pBuf);
    return pBuf;
}

static const char *GetUpdaterDestPath(char *pBuf, int BufSize, const char *pFile, const char *pDestPath)
{
    if(!pDestPath || !pDestPath[0])
        pDestPath = pFile;
    str_format(pBuf, BufSize, "update/%s", pDestPath);
    return pBuf;
}

// --- CFexUpdaterFetchTask Implementation ---

CFexUpdaterFetchTask::CFexUpdaterFetchTask(CFexUpdater *pUpdater, const char *pFile, const char *pDestPath)
    : CHttpRequest("") // We'll set the URL below.
    , m_pUpdater(pUpdater)
{
    // Use latest tag if available, else "v" + FEX_RELEASE_VERSION.
    const char *pTag = (m_pUpdater->m_aLatestVersion[0] != '\0') ?
                         m_pUpdater->m_aLatestVersion :
                         ("v" FEX_RELEASE_VERSION);
    BuildUpdaterUrl(m_aUrl, sizeof(m_aUrl), pFile, pTag);
    WriteToFile(m_pUpdater->m_pStorage, GetUpdaterDestPath(m_aDest, sizeof(m_aDest), pFile, pDestPath), -2);
    // Instead of calling an undefined SetUrl(), we assume CHttpRequest uses the URL from a member.
    // If such a member does not exist, you may add a setter in your engine.
    // For now, we ignore m_Uri.
}

void CFexUpdaterFetchTask::OnProgress()
{
    std::lock_guard<std::mutex> lock(m_pUpdater->m_Lock);
    m_pUpdater->m_Percent = Progress();
}

void CFexUpdaterFetchTask::OnCompletion(EHttpState State)
{
    // Get file name from m_aDest.
    const char *pFileName = strrchr(m_aDest, '/');
    pFileName = pFileName ? pFileName + 1 : m_aDest;
    if(!str_comp(pFileName, "update.json"))
    {
        if(State == EHttpState::DONE)
            m_pUpdater->SetCurrentState(FEX_UPDATER_GOT_MANIFEST);
        else if(State == EHttpState::ERROR)
            m_pUpdater->SetCurrentState(FEX_UPDATER_FAIL);
    }
}

////////////////// CFexUpdater //////////////////////

CFexUpdater::CFexUpdater()
{
    m_pClient = nullptr;
    m_pStorage = nullptr;
    m_pEngine = nullptr;
    m_pHttp = nullptr;
    m_State = FEX_UPDATER_CLEAN;
    m_Percent = 0;
    m_pCurrentTask = nullptr;
    m_ClientUpdate = m_ServerUpdate = m_ClientFetched = m_ServerFetched = false;
    IStorage::FormatTmpPath(m_aClientExecTmp, sizeof(m_aClientExecTmp), CLIENT_EXEC);
    IStorage::FormatTmpPath(m_aServerExecTmp, sizeof(m_aServerExecTmp), SERVER_EXEC);
    m_aStatus[0] = '\0';
    m_aLatestVersion[0] = '\0';
}

void CFexUpdater::OnInit()
{
    m_pClient = Kernel()->RequestInterface<IClient>();
    m_pStorage = Kernel()->RequestInterface<IStorage>();
    m_pEngine = Kernel()->RequestInterface<IEngine>();
	m_pHttp = Kernel()->RequestInterface<CHttp>();
}

void CFexUpdater::SetCurrentState(EFexUpdaterState NewState)
{
    std::lock_guard<std::mutex> lock(m_Lock);
    m_State = NewState;
}

EFexUpdaterState CFexUpdater::GetCurrentState()
{
    std::lock_guard<std::mutex> lock(m_Lock);
    return m_State;
}

void CFexUpdater::FetchFile(const char *pFile, const char *pDestPath)
{
    std::lock_guard<std::mutex> lock(m_Lock);
    m_pCurrentTask = std::make_shared<CFexUpdaterFetchTask>(this, pFile, pDestPath);
    str_copy(m_aStatus, m_pCurrentTask->Dest(), sizeof(m_aStatus));
    m_pHttp->Run(m_pCurrentTask);
    if (!m_pHttp)
    {
        dbg_msg("FeX[updater]", "ERROR: m_pHttp is not initialized!");
        return;
    }
}

void CFexUpdater::InitiateUpdate()
{
    SetCurrentState(FEX_UPDATER_GETTING_MANIFEST);
    const char *pManifestUrl = "https://api.github.com/repos/faffa81/FeX-V2-Client/releases/latest";
    m_pCurrentTask = HttpGet(pManifestUrl);
    if(!m_pCurrentTask)
    {
        dbg_msg("FeX[updater]", "HttpGet returned null for URL: %s", pManifestUrl);
        SetCurrentState(FEX_UPDATER_FAIL);
        return;
    }
    m_pCurrentTask->Timeout(CTimeout{10000, 0, 500, 10});
    m_pCurrentTask->IpResolve(IPRESOLVE::V4);
    m_pHttp->Run(m_pCurrentTask);
}


void CFexUpdater::OnRender()
{
    switch(GetCurrentState())
    {
    case FEX_UPDATER_GETTING_MANIFEST:
        if(m_pCurrentTask && m_pCurrentTask->Done())
        {
            if(m_pCurrentTask->State() == EHttpState::DONE)
            {
                // Parse GitHub JSON.
                unsigned char *pResult = nullptr;
                size_t resultLength = 0;
                m_pCurrentTask->Result(&pResult, &resultLength);
                void *pBuf = static_cast<void *>(pResult);
                unsigned Length = (unsigned)str_length((const char *)pBuf);
                json_value *pJson = json_parse((json_char*)pBuf, Length);
                if(pJson && pJson->type == json_object)
                {
                    const json_value *pTag = json_object_get(pJson, "tag_name");
                    if(pTag && pTag->type == json_string)
                    {
                        const char *pTagStr = json_string_get(pTag);
                        if(pTagStr[0] == 'v')
                            pTagStr++;
                        str_copy(m_aLatestVersion, pTagStr, sizeof(m_aLatestVersion));
                        if(str_comp(m_aLatestVersion, FEX_RELEASE_VERSION) > 0)
                        {
                            SetCurrentState(FEX_UPDATER_GOT_MANIFEST);
                        }
                        else
                        {
                            SetCurrentState(FEX_UPDATER_CLEAN);
                        }
                    }
                    json_value_free(pJson);
                }
                else
                    SetCurrentState(FEX_UPDATER_FAIL);
            }
            else
                SetCurrentState(FEX_UPDATER_FAIL);
        }
        break;
    case FEX_UPDATER_GOT_MANIFEST:
        {
#if defined(CONF_FAMILY_WINDOWS)
            AddFileJob("FeX-5.1-win64.zip", true);
#elif defined(CONF_PLATFORM_LINUX)
            AddFileJob("FeX-5.1-linux.zip", true);
#elif defined(CONF_PLATFORM_MACOS)
            AddFileJob("FeX-5.1-macos.zip", true);
#endif
            SetCurrentState(FEX_UPDATER_DOWNLOADING);
            m_CurrentJob = m_FileJobs.begin();
        }
        break;
    case FEX_UPDATER_DOWNLOADING:
        RunningUpdate();
        break;
    case FEX_UPDATER_MOVE_FILES:
        CommitUpdate();
        break;
    case FEX_UPDATER_FAIL:
        dbg_msg("FeX[updater]", "Update failed: %s", m_aStatus);
        break;
    case FEX_UPDATER_NEED_RESTART:
        dbg_msg("FeX[updater]", "Update applied; please restart FeX");
        break;
    case FEX_UPDATER_CLEAN:
    default:
        break;
    }
}

void CFexUpdater::AddFileJob(const char *pFile, bool Job)
{
    m_FileJobs.emplace_front(pFile, Job);
}

void CFexUpdater::PerformUpdate()
{
    SetCurrentState(FEX_UPDATER_PARSING_UPDATE);
    m_CurrentJob = m_FileJobs.begin();
    SetCurrentState(FEX_UPDATER_DOWNLOADING);
}

void CFexUpdater::RunningUpdate()
{
    if(m_pCurrentTask)
    {
        if(!m_pCurrentTask->Done())
            return;
        else if(m_pCurrentTask->State() == EHttpState::ERROR || m_pCurrentTask->State() == EHttpState::ABORTED)
        {
            SetCurrentState(FEX_UPDATER_FAIL);
            return;
        }
    }
    if(m_CurrentJob != m_FileJobs.end())
    {
        auto &Job = *m_CurrentJob;
        if(Job.second)
        {
            const char *pFile = Job.first.c_str();
            size_t len = str_length(pFile);
#if defined(CONF_FAMILY_WINDOWS)
            if(!str_comp_nocase(pFile + len - 4, ".dll"))
            {
                char aBuf[512];
                str_copy(aBuf, pFile, sizeof(aBuf));
                str_copy(aBuf + len - 4, "-" PLAT_NAME, sizeof(aBuf) - len + 4);
                str_append(aBuf, pFile + len - 4);
                FetchFile(aBuf, pFile);
            }
            else
#endif
            {
                FetchFile(pFile);
            }
        }
        else
        {
            m_pStorage->RemoveBinaryFile(Job.first.c_str());
        }
        m_CurrentJob++;
    }
    else
    {
        if(m_ServerUpdate && !m_ServerFetched)
        {
            FetchFile(PLAT_SERVER_DOWN, m_aServerExecTmp);
            m_ServerFetched = true;
            return;
        }
        if(m_ClientUpdate && !m_ClientFetched)
        {
            FetchFile(PLAT_CLIENT_DOWN, m_aClientExecTmp);
            m_ClientFetched = true;
            return;
        }
        SetCurrentState(FEX_UPDATER_MOVE_FILES);
    }
}

void CFexUpdater::CommitUpdate()
{
    bool Success = true;
    for(auto &FileJob : m_FileJobs)
    {
        if(FileJob.second)
            Success &= MoveFile(FileJob.first.c_str());
    }
    if(m_ClientUpdate)
        Success &= ReplaceClient();
    if(m_ServerUpdate)
        Success &= ReplaceServer();
    if(!Success)
        SetCurrentState(FEX_UPDATER_FAIL);
    else if(m_pClient->State() == IClient::STATE_ONLINE || m_pClient->EditorHasUnsavedData())
        SetCurrentState(FEX_UPDATER_NEED_RESTART);
    else
    {
        m_pClient->Restart();
    }
}

bool CFexUpdater::MoveFile(const char *pFile)
{
    char aBuf[256];
    size_t len = str_length(pFile);
    bool Success = true;
#if !defined(CONF_FAMILY_WINDOWS)
    if(!str_comp_nocase(pFile + len - 4, ".dll"))
        return Success;
#endif
#if !defined(CONF_PLATFORM_LINUX)
    if(!str_comp_nocase(pFile + len - 3, ".so"))
        return Success;
#endif
    if(!str_comp_nocase(pFile + len - 4, ".dll") ||
       !str_comp_nocase(pFile + len - 4, ".ttf") ||
       !str_comp_nocase(pFile + len - 3, ".so"))
    {
        str_format(aBuf, sizeof(aBuf), "%s.old", pFile);
        m_pStorage->RenameBinaryFile(pFile, aBuf);
        str_format(aBuf, sizeof(aBuf), "update/%s", pFile);
        Success &= m_pStorage->RenameBinaryFile(aBuf, pFile);
    }
    else
    {
        str_format(aBuf, sizeof(aBuf), "update/%s", pFile);
        Success &= m_pStorage->RenameBinaryFile(aBuf, pFile);
    }
    return Success;
}

bool CFexUpdater::ReplaceClient()
{
    dbg_msg("FeX[updater]", "replacing " PLAT_CLIENT_EXEC);
    bool Success = true;
    char aPath[IO_MAX_PATH_LENGTH];

    m_pStorage->RemoveBinaryFile(CLIENT_EXEC ".old");
    Success &= m_pStorage->RenameBinaryFile(PLAT_CLIENT_EXEC, CLIENT_EXEC ".old");
    str_format(aPath, sizeof(aPath), "update/%s", m_aClientExecTmp);
    Success &= m_pStorage->RenameBinaryFile(aPath, PLAT_CLIENT_EXEC);
#if !defined(CONF_FAMILY_WINDOWS)
    m_pStorage->GetBinaryPath(PLAT_CLIENT_EXEC, aPath, sizeof(aPath));
    char aBuf[512];
    str_format(aBuf, sizeof(aBuf), "chmod +x %s", aPath);
    if(system(aBuf))
    {
        dbg_msg("FeX[updater]", "ERROR: failed to set client executable bit");
        Success = false;
    }
#endif
    return Success;
}

bool CFexUpdater::ReplaceServer()
{
    dbg_msg("FeX[updater]", "replacing " PLAT_SERVER_EXEC);
    bool Success = true;
    char aPath[IO_MAX_PATH_LENGTH];

    m_pStorage->RemoveBinaryFile(SERVER_EXEC ".old");
    Success &= m_pStorage->RenameBinaryFile(PLAT_SERVER_EXEC, SERVER_EXEC ".old");
    str_format(aPath, sizeof(aPath), "update/%s", m_aServerExecTmp);
    Success &= m_pStorage->RenameBinaryFile(aPath, SERVER_EXEC);
#if !defined(CONF_FAMILY_WINDOWS)
    m_pStorage->GetBinaryPath(SERVER_EXEC, aPath, sizeof(aPath));
    char aBuf[512];
    str_format(aBuf, sizeof(aBuf), "chmod +x %s", aPath);
    if(system(aBuf))
    {
        dbg_msg("FeX[updater]", "ERROR: failed to set server executable bit");
        Success = false;
    }
#endif
    return Success;
}
