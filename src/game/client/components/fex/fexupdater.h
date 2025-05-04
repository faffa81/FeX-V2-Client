#ifndef GAME_CLIENT_COMPONENTS_FEX_UPDATER_H
#define GAME_CLIENT_COMPONENTS_FEX_UPDATER_H

#include <game/client/component.h>
#include <engine/shared/http.h>
#include <engine/storage.h>
#include <deque>
#include <vector>
#include <string>
#include <memory>
#include <mutex>

// Macros definitions (adjust to your project)
// FeX.exe and FeX-Server.exe are the executables.
#ifndef CLIENT_EXEC
    #define CLIENT_EXEC "FeX.exe"
#endif
#ifndef SERVER_EXEC
    #define SERVER_EXEC "FeX-Server.exe"
#endif

#ifndef PLAT_CLIENT_EXEC
    #define PLAT_CLIENT_EXEC CLIENT_EXEC
#endif
#ifndef PLAT_SERVER_EXEC
    #define PLAT_SERVER_EXEC SERVER_EXEC
#endif

#ifndef PLAT_CLIENT_DOWN
    #define PLAT_CLIENT_DOWN "FeX-Client.zip"
#endif
#ifndef PLAT_SERVER_DOWN
    #define PLAT_SERVER_DOWN "FeX-Server.zip"
#endif

#ifndef PLAT_NAME
    #if defined(CONF_FAMILY_WINDOWS)
        #define PLAT_NAME "win64"
    #elif defined(CONF_PLATFORM_LINUX)
        #define PLAT_NAME "linux"
    #elif defined(CONF_PLATFORM_MACOS)
        #define PLAT_NAME "macos"
    #else
        #define PLAT_NAME "unknown"
    #endif
#endif



// Updater states modeled after DDNet’s updater.
enum EFexUpdaterState {
    FEX_UPDATER_CLEAN,
    FEX_UPDATER_GETTING_MANIFEST,
    FEX_UPDATER_GOT_MANIFEST,
    FEX_UPDATER_PARSING_UPDATE,
    FEX_UPDATER_DOWNLOADING,
    FEX_UPDATER_MOVE_FILES,
    FEX_UPDATER_NEED_RESTART,
    FEX_UPDATER_FAIL
};

class CFexUpdater : public CComponent
{
public:
    CFexUpdater();
    virtual ~CFexUpdater() {}

    virtual void OnInit() override;
    virtual void OnRender() override;
    virtual int Sizeof() const override { return sizeof(*this); }

    // Initiates the update process using GitHub’s API.
    void InitiateUpdate();
    // Called each frame to drive the update state machine.
    void Update();

    // Downloads a file from the update server.
    void FetchFile(const char *pFile, const char *pDestPath = nullptr);

    // The old JSON style manifest parser.
    void ParseUpdate();
    void PerformUpdate();
    void RunningUpdate();
    void CommitUpdate();

    // Helpers for moving files.
    bool MoveFile(const char *pFile);
    bool ReplaceClient();
    bool ReplaceServer();

    // Setters and getters for internal state.
    void SetCurrentState(EFexUpdaterState NewState);
    EFexUpdaterState GetCurrentState();

    // Add a file job (a pair: filename, bool flag: true=download, false=remove).
    void AddFileJob(const char *pFile, bool Job);

    // Updater status.
    int m_Percent;
    char m_aStatus[512];

    // Flags to indicate if client/server update is needed and fetched.
    bool m_ClientUpdate, m_ServerUpdate;
    bool m_ClientFetched, m_ServerFetched;
    // Temporary file names for new executables.
    char m_aClientExecTmp[IO_MAX_PATH_LENGTH];
    char m_aServerExecTmp[IO_MAX_PATH_LENGTH];

    // The current HTTP task.
    std::shared_ptr<CHttpRequest> m_pCurrentTask;
    // File jobs (filename and a download flag) to process.
    std::deque<std::pair<std::string, bool>> m_FileJobs;
    std::deque<std::pair<std::string, bool>>::iterator m_CurrentJob;

    // Interfaces from the kernel.
    IEngine *m_pEngine;
    IStorage *m_pStorage;
    IClient *m_pClient;
    CHttp *m_pHttp;

    // Mutex for thread safety.
    std::mutex m_Lock;

    // Latest release version (tag without leading "v")
    char m_aLatestVersion[32];

private:
    EFexUpdaterState m_State;
};

class CFexUpdaterFetchTask : public CHttpRequest
{
    char m_aUrl[512];
    char m_aDest[512];
    CFexUpdater *m_pUpdater;
protected:
    virtual void OnCompletion(EHttpState State) override;
    virtual void OnProgress() override;
public:
    // Construct fetch task from file and destination path.
    CFexUpdaterFetchTask(CFexUpdater *pUpdater, const char *pFile, const char *pDestPath);
};

#endif
