#ifndef GAME_CLIENT_COMPONENTS_FEX_FEXQUICKACTIONS_H
#define GAME_CLIENT_COMPONENTS_FEX_FEXQUICKACTIONS_H

#include <engine/console.h>
#include <game/client/component.h>
#include <vector>

#define ACTIONS_FILE "fex_quickactions.cfg"

class IConfigManager;

enum
{
    ACTION_PAGE_MAX_NAME = 16,
    ACTION_MAX_NAME = 32,
    ACTION_MAX_CMD = 1024,
    MAX_PAGES = 32,
    MAX_ACTIONS_PER_PAGE = 3
};

struct SAction
{
    char m_aName[ACTION_MAX_NAME];
    char m_aCommand[ACTION_MAX_CMD];
};

struct SPage
{
    char m_aName[ACTION_PAGE_MAX_NAME];
    SAction m_aActions[MAX_ACTIONS_PER_PAGE];
    int m_NumActions;

    SPage() : m_NumActions(0) { m_aName[0] = '\0'; }
};

class CActions : public CComponent
{
    static void ConfigSaveCallback(IConfigManager *pConfigManager, void *pUserData);

    void WriteLine(const char *pLine);
    class IStorage *m_pStorage = nullptr;
    IOHANDLE m_ActionsFile = nullptr;

public:
    virtual int Sizeof() const override { return sizeof(*this); }
    virtual bool OnInput(const IInput::CEvent &Event) override;
    virtual void OnConsoleInit() override;
    virtual void OnReset() override;

    bool AddPage(const char *pPageName);
    bool RemovePage(int PageIndex);

    bool AddActionToPage(int PageIndex, const char *pActionName, const char *pActionCommand);
    bool RemoveActionFromPage(int PageIndex, int ActionIndex);

    static void ConAddPage(IConsole::IResult *pResult, void *pUserData);
    static void ConRemovePage(IConsole::IResult *pResult, void *pUserData);
    static void ConAddActionToPage(IConsole::IResult *pResult, void *pUserData);
    static void ConRemoveActionFromPage(IConsole::IResult *pResult, void *pUserData);

public:
    bool m_SpectatorActionMenuActive;
    int m_SpectatorActionPage;
    float m_SpectatorActionMenuAlpha;
    int64_t m_SpectatorActionMenuShowTime;
	int64_t m_SpectatorActionMenuNotShowTime;
	bool m_SpectatorActionMenuClosing;

    SPage m_aPages[MAX_PAGES];
    int m_NumPages;

    void InitDefaultPages();

    vec2 WorldToScreen(vec2 WorldPos);

    void LoadQuickActionsFromFile();

    void PrepareSpectatorActionIcons();

    void RenderSpectatorActionMenu();
    void HandleSpectatorActionInput(int Key);

    vec2 m_SpectatorActionMenuPos{0, 0};
};

#endif // GAME_CLIENT_COMPONENTS_FEX_FEXQUICKACTIONS_H
