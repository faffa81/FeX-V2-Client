/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <engine/graphics.h>
#include <engine/keys.h>
#include <engine/serverbrowser.h>
#include <engine/textrender.h>

#include <engine/client/updater.h>
#include <engine/shared/config.h>

#include <game/client/gameclient.h>
#include <game/client/ui.h>
#include <game/client/ui_scrollregion.h>

#include <game/generated/client_data.h>
#include <game/localization.h>
#include <game/version.h>

#include "menus.h"

#if defined(CONF_PLATFORM_ANDROID)
#include <android/android_main.h>
#endif
#include "fex/fexversion.h"

using namespace FontIcons;


void CMenus::RenderStartMenu(CUIRect MainView)
{
	GameClient()->m_MenuBackground.ChangePosition(CMenuBackground::POS_START);

	// render logo
	Graphics()->TextureSet(g_pData->m_aImages[IMAGE_BANNER].m_Id);
	Graphics()->QuadsBegin();
	Graphics()->SetColor(1, 1, 1, 1);
	IGraphics::CQuadItem QuadItem(MainView.w / 2 - 170, 60, 360, 103);
	Graphics()->QuadsDrawTL(&QuadItem, 1);
	Graphics()->QuadsEnd();

	const float Rounding = 10.0f;
	const float VMargin = MainView.w / 2 - 190.0f;
	const float VFrames = MainView.w / 2 - 200.0f;

	float screenAspect = Graphics()->ScreenAspect();
    const float designWidth = 1280.0f;
    const float designHeight = designWidth / screenAspect;
    
    const float baseHeight = 720.0f;
    float scale = designHeight / baseHeight;

	ColorRGBA Color = ColorRGBA(0.0f, 0.0f, 0.0f, 0.25f);
	ColorRGBA TextColor = ColorRGBA(0.0f, 0.0f, 0.0f, 0.25f);
	int Theme = g_Config.m_ClStartMenuTheme;
	if(Theme == 1) // Dark
	{
		Color = ColorRGBA(0.0f, 0.0f, 0.0f, 0.25f);
		TextColor = ColorRGBA(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if(Theme == 2) // Light
	{
		Color = ColorRGBA(1.0f, 1.0f, 1.0f, 0.25f);
		TextColor = ColorRGBA(0.0f, 0.0f, 0.0f, 1.0f);
	}
	else if(Theme == 3) // Custom
	{
		Color = color_cast<ColorRGBA>(ColorHSLA(g_Config.m_ClStartMenuColor));
		TextColor = color_cast<ColorRGBA>(ColorHSLA(g_Config.m_ClStartMenuTextColor));
	}

	ColorRGBA ColorA = ColorRGBA(Color.r,Color.g,Color.b,Color.a = 0.25f);

	CUIRect Button;
	int NewPage = -1;

	RenderBar(MainView);
	if(g_Config.m_ClStartMenuInfo)
		RenderPlayerPanelTopRight(MainView);

	CUIRect ExtMenu, ExtMenuFrame;
	MainView.VSplitLeft(30.0f, nullptr, &ExtMenu);
	MainView.VSplitLeft(30.0f, nullptr, &ExtMenuFrame);
	ExtMenu.VSplitLeft(100.0f, &ExtMenu, nullptr);
	ExtMenuFrame.VSplitLeft(100.0f, &ExtMenuFrame, nullptr);
	ExtMenuFrame.VMargin(-5.25f, &ExtMenuFrame);
	ExtMenuFrame.HSplitBottom(150.0f, nullptr, &ExtMenuFrame);
	ExtMenuFrame.HSplitBottom(-5.0f, &ExtMenuFrame, nullptr);
	if(g_Config.m_ClStartMenuFrames)
	{
		ExtMenuFrame.Draw(ColorA, IGraphics::CORNER_ALL, Rounding / scale);
	}

	TextRender()->TextColor(TextColor);
	ExtMenu.HSplitBottom(20.0f, &ExtMenu, &Button);
	static CButtonContainer s_DiscordButton;
	if(DoButton_Menu(&s_DiscordButton, Localize("Discord"), 0, &Button, BUTTONFLAG_LEFT, nullptr, IGraphics::CORNER_ALL, 5.0f / scale, 0.0f, ColorA))
	{
		Client()->ViewLink(Localize("https://ddnet.org/discord"));
	}

	ExtMenu.HSplitBottom(5.0f, &ExtMenu, nullptr); // little space
	ExtMenu.HSplitBottom(20.0f, &ExtMenu, &Button);
	static CButtonContainer s_LearnButton;
	if(DoButton_Menu(&s_LearnButton, Localize("Learn"), 0, &Button, BUTTONFLAG_LEFT, nullptr, IGraphics::CORNER_ALL, 5.0f / scale, 0.0f, ColorA))
	{
		Client()->ViewLink(Localize("https://wiki.ddnet.org/"));
	}

	ExtMenu.HSplitBottom(5.0f, &ExtMenu, nullptr); // little space
	ExtMenu.HSplitBottom(20.0f, &ExtMenu, &Button);
	static CButtonContainer s_TutorialButton;
	static float s_JoinTutorialTime = 0.0f;
	if(DoButton_Menu(&s_TutorialButton, Localize("Tutorial"), 0, &Button, BUTTONFLAG_LEFT, nullptr, IGraphics::CORNER_ALL, 5.0f / scale, 0.0f, ColorA) ||
		(s_JoinTutorialTime != 0.0f && Client()->LocalTime() >= s_JoinTutorialTime))
	{
		// Activate internet tab before joining tutorial to make sure the server info
		// for the tutorial servers is available.
		SetMenuPage(PAGE_INTERNET);
		RefreshBrowserTab(true);
		const char *pAddr = ServerBrowser()->GetTutorialServer();
		if(pAddr)
		{
			Client()->Connect(pAddr);
			s_JoinTutorialTime = 0.0f;
		}
		else if(s_JoinTutorialTime == 0.0f)
		{
			dbg_msg("menus", "couldn't find tutorial server, retrying in 5 seconds");
			s_JoinTutorialTime = Client()->LocalTime() + 5.0f;
		}
		else
		{
			Client()->AddWarning(SWarning(Localize("Can't find a Tutorial server")));
			s_JoinTutorialTime = 0.0f;
		}
	}

	ExtMenu.HSplitBottom(5.0f, &ExtMenu, nullptr); // little space
	ExtMenu.HSplitBottom(20.0f, &ExtMenu, &Button);
	static CButtonContainer s_WebsiteButton;
	if(DoButton_Menu(&s_WebsiteButton, Localize("Website"), 0, &Button, BUTTONFLAG_LEFT, nullptr, IGraphics::CORNER_ALL, 5.0f / scale, 0.0f, ColorA))
	{
		Client()->ViewLink("https://ddnet.org/");
	}

	ExtMenu.HSplitBottom(5.0f, &ExtMenu, nullptr); // little space
	ExtMenu.HSplitBottom(20.0f, &ExtMenu, &Button);
	static CButtonContainer s_NewsButton;
	if(DoButton_Menu(&s_NewsButton, Localize("News"), 0, &Button, BUTTONFLAG_LEFT, nullptr, IGraphics::CORNER_ALL, 5.0f / scale, 0.0f, g_Config.m_UiUnreadNews ? ColorRGBA(0.0f, 1.0f, 0.0f, 0.25f) : ColorA) || CheckHotKey(KEY_N))
		NewPage = PAGE_NEWS;

	ExtMenu.HSplitBottom(5.0f, &ExtMenu, nullptr); // little space
	ExtMenu.HSplitBottom(20.0f, &ExtMenu, &Button);
	static CButtonContainer s_UpdateButton;
	if(DoButton_Menu(&s_UpdateButton, Localize("FeX Updates"), 0, &Button, BUTTONFLAG_LEFT, nullptr, IGraphics::CORNER_ALL, 5.0f / scale, 0.0f, g_Config.m_UiUnreadNews ? ColorRGBA(0.0f, 1.0f, 0.0f, 0.25f) : ColorA) || CheckHotKey(KEY_N))
		NewPage = PAGE_UPDATES;

	CUIRect Menu, MenuFrame, MenuFrameDown;
	MainView.VMargin(VMargin, &Menu);
	MainView.VMargin(VFrames, &MenuFrame);
	MainView.VMargin(VFrames, &MenuFrameDown);
	Menu.HSplitBottom(25.0f, &Menu, nullptr);
	MenuFrame.HSplitTop(180.0f, nullptr, &MenuFrame);
	MenuFrame.HSplitBottom(150.0f, &MenuFrame, nullptr);
	MenuFrameDown.HSplitBottom(75.0f, nullptr, &MenuFrameDown);
	MenuFrameDown.HSplitTop(60.0f, &MenuFrameDown, nullptr);
	if(g_Config.m_ClStartMenuFrames)
	{
		MenuFrame.Draw(ColorA, IGraphics::CORNER_ALL, Rounding / scale);
		MenuFrameDown.Draw(ColorA, IGraphics::CORNER_ALL, Rounding / scale);
	}

	Menu.HSplitBottom(40.0f, &Menu, &Button);
	static CButtonContainer s_QuitButton;
	bool UsedEscape = false;
	if(DoButton_Menu(&s_QuitButton, Localize("Quit"), 0, &Button, BUTTONFLAG_LEFT, nullptr, IGraphics::CORNER_ALL, Rounding / scale, 0.5f, ColorA) || (UsedEscape = Ui()->ConsumeHotkey(CUi::HOTKEY_ESCAPE)) || CheckHotKey(KEY_Q))
	{
		if(UsedEscape || m_pClient->Editor()->HasUnsavedData() || (GameClient()->CurrentRaceTime() / 60 >= g_Config.m_ClConfirmQuitTime && g_Config.m_ClConfirmQuitTime >= 0))
		{
			m_Popup = POPUP_QUIT;
		}
		else
		{
			Client()->Quit();
		}
	}

	Menu.HSplitBottom(100.0f, &Menu, nullptr);
	Menu.HSplitBottom(40.0f, &Menu, &Button);
	static CButtonContainer s_SettingsButton;
	if(DoButton_Menu(&s_SettingsButton, Localize("Settings"), 0, &Button, BUTTONFLAG_LEFT, g_Config.m_ClShowStartMenuImages ? "settings" : nullptr, IGraphics::CORNER_ALL, Rounding / scale, 0.5f, ColorA) || CheckHotKey(KEY_S))
		NewPage = PAGE_SETTINGS;

	Menu.HSplitBottom(5.0f, &Menu, nullptr); // little space
	Menu.HSplitBottom(40.0f, &Menu, &Button);
	static CButtonContainer s_LocalServerButton;

#if !defined(CONF_PLATFORM_ANDROID)
	if(!is_process_alive(m_ServerProcess.m_Process))
		KillServer();
#endif

	if(DoButton_Menu(&s_LocalServerButton, IsServerRunning() ? Localize("Stop server") : Localize("Run server"), 0, &Button, BUTTONFLAG_LEFT, g_Config.m_ClShowStartMenuImages ? "local_server" : nullptr, IGraphics::CORNER_ALL, Rounding / scale, 0.5f, IsServerRunning() ? ColorRGBA(0.0f, 1.0f, 0.0f, 0.25f) : ColorA) || (CheckHotKey(KEY_R) && Input()->KeyPress(KEY_R)))
	{
		if(IsServerRunning())
		{
			KillServer();
			GameClient()->m_aSavedLocalRconPassword[0] = '\0';
		}
		else
		{
			char aRandomPass[17];
			secure_random_password(aRandomPass, sizeof(aRandomPass), 16);
			char aPass[64];
			str_format(aPass, sizeof(aPass), "auth_add %s admin %s", DEFAULT_SAVED_RCON_USER, aRandomPass);
			const char *apArguments[] = {aPass};
			RunServer(apArguments, std::size(apArguments));
			str_copy(GameClient()->m_aSavedLocalRconPassword, aRandomPass);
		}
	}

	Menu.HSplitBottom(5.0f, &Menu, nullptr); // little space
	Menu.HSplitBottom(40.0f, &Menu, &Button);
	static CButtonContainer s_MapEditorButton;
	if(DoButton_Menu(&s_MapEditorButton, Localize("Editor"), 0, &Button, BUTTONFLAG_LEFT, g_Config.m_ClShowStartMenuImages ? "editor" : nullptr, IGraphics::CORNER_ALL, Rounding / scale, 0.5f, m_pClient->Editor()->HasUnsavedData() ? ColorRGBA(0.0f, 1.0f, 0.0f, 0.25f) : ColorA) || CheckHotKey(KEY_E))
	{
		g_Config.m_ClEditor = 1;
		Input()->MouseModeRelative();
	}

	Menu.HSplitBottom(5.0f, &Menu, nullptr); // little space
	Menu.HSplitBottom(40.0f, &Menu, &Button);
	static CButtonContainer s_DemoButton;
	if(DoButton_Menu(&s_DemoButton, Localize("Demos"), 0, &Button, BUTTONFLAG_LEFT, g_Config.m_ClShowStartMenuImages ? "demos" : nullptr, IGraphics::CORNER_ALL, Rounding / scale, 0.5f, ColorA) || CheckHotKey(KEY_D))
	{
		NewPage = PAGE_DEMOS;
	}

	Menu.HSplitBottom(5.0f, &Menu, nullptr); // little space
	Menu.HSplitBottom(40.0f, &Menu, &Button);
	static CButtonContainer s_PlayButton;
	if(DoButton_Menu(&s_PlayButton, Localize("Play", "Start menu"), 0, &Button, BUTTONFLAG_LEFT, g_Config.m_ClShowStartMenuImages ? "play_game" : nullptr, IGraphics::CORNER_ALL, Rounding / scale, 0.5f, ColorA) || Ui()->ConsumeHotkey(CUi::HOTKEY_ENTER) || CheckHotKey(KEY_P))
	{
		NewPage = g_Config.m_UiPage >= PAGE_INTERNET && g_Config.m_UiPage <= PAGE_FAVORITE_COMMUNITY_5 ? g_Config.m_UiPage : PAGE_INTERNET;
	}

	// render version
	CUIRect CurVersion, ConsoleButton, VersionFrame, VersionButton;
	MainView.HSplitBottom(45.0f / scale, nullptr, &CurVersion);
	MainView.HSplitBottom(45.0f / scale, nullptr, &VersionFrame);
	VersionFrame.VSplitRight(38.0f / scale, &VersionFrame, nullptr);
	VersionFrame.VSplitRight(160.0f / scale, nullptr, &VersionFrame);
	VersionFrame.VMargin(-5.5f / scale, &VersionFrame);
	VersionFrame.HSplitBottom(54.5f / scale, nullptr, &VersionFrame);
	VersionFrame.HSplitBottom(-5.5f / scale, &VersionFrame, nullptr);
	if(g_Config.m_ClStartMenuFrames)
	{
		VersionFrame.Draw(ColorA, IGraphics::CORNER_ALL, Rounding / scale);
	}
	CurVersion.VSplitRight(40.0f / scale, &CurVersion, nullptr);
	CurVersion.HSplitTop(20.0f / scale, &ConsoleButton, &CurVersion);
	CurVersion.HSplitTop(5.0f / scale, nullptr, &CurVersion);

	ConsoleButton.VSplitRight(40.0f / scale, &VersionButton, &ConsoleButton);
	VersionButton.VSplitRight(10.0f / scale, &VersionButton, nullptr);
	VersionButton.VSplitRight(107.5f / scale, nullptr, &VersionButton);


	char DDNETRL[128];
	str_format(DDNETRL, sizeof(DDNETRL), Localize("%s: %s"), GAME_NAME, GAME_RELEASE_VERSION);
	char FEXRL[128];
	str_format(FEXRL, sizeof(FEXRL), Localize("%s: %s"), CLIENT_NAME, FEX_RELEASE_VERSION);
	Ui()->DoLabel(&CurVersion, DDNETRL, 12.0f / scale, TEXTALIGN_LEFT);
	CurVersion.HSplitTop(20.0f / scale, nullptr, &CurVersion);
	Ui()->DoLabel(&CurVersion, FEXRL, 12.0f / scale, TEXTALIGN_LEFT);

	static CButtonContainer s_VersionButton;
	if(DoButton_Menu(&s_VersionButton, Localize("FeX Versions"), 0, &VersionButton, BUTTONFLAG_LEFT, nullptr, IGraphics::CORNER_ALL, 5.0f / scale, 0.0f, ColorA))
	{
		Client()->ViewLink("https://github.com/faffa81/FeX-V2-Client/releases/");
	}

	static CButtonContainer s_ConsoleButton;
	TextRender()->SetFontPreset(EFontPreset::ICON_FONT);
	TextRender()->SetRenderFlags(ETextRenderFlags::TEXT_RENDER_FLAG_ONLY_ADVANCE_WIDTH | ETextRenderFlags::TEXT_RENDER_FLAG_NO_X_BEARING | ETextRenderFlags::TEXT_RENDER_FLAG_NO_Y_BEARING | ETextRenderFlags::TEXT_RENDER_FLAG_NO_PIXEL_ALIGNMENT | ETextRenderFlags::TEXT_RENDER_FLAG_NO_OVERSIZE);
	if(DoButton_Menu(&s_ConsoleButton, FONT_ICON_TERMINAL, 0, &ConsoleButton, BUTTONFLAG_LEFT, nullptr, IGraphics::CORNER_ALL, 5.0f / scale, 0.0f, ColorA))
	{
		GameClient()->m_GameConsole.Toggle(CGameConsole::CONSOLETYPE_LOCAL);
	}
	TextRender()->SetRenderFlags(0);
	TextRender()->SetFontPreset(EFontPreset::DEFAULT_FONT);

	CUIRect VersionUpdate;
	MainView.HSplitBottom(15.0f, nullptr, &VersionUpdate);
	VersionUpdate.VMargin(VMargin * scale, &VersionUpdate);
#if defined(CONF_AUTOUPDATE)
	CUIRect UpdateButton;
	VersionUpdate.VSplitRight(100.0f, &VersionUpdate, &UpdateButton);
	VersionUpdate.VSplitRight(10.0f, &VersionUpdate, nullptr);

	char aBuf[128];
	const IUpdater::EUpdaterState State = Updater()->GetCurrentState();
	const bool NeedUpdate = str_comp(Client()->LatestVersion(), "0");

	if(State == IUpdater::CLEAN && NeedUpdate)
	{
		static CButtonContainer s_VersionUpdate;
		if(DoButton_Menu(&s_VersionUpdate, Localize("Update now"), 0, &UpdateButton, BUTTONFLAG_LEFT, 0, IGraphics::CORNER_ALL, 5.0f, 0.0f, ColorA))
		{
			Updater()->InitiateUpdate();
		}
	}
	else if(State == IUpdater::NEED_RESTART)
	{
		static CButtonContainer s_VersionUpdate;
		if(DoButton_Menu(&s_VersionUpdate, Localize("Restart"), 0, &UpdateButton, BUTTONFLAG_LEFT, 0, IGraphics::CORNER_ALL, 5.0f, 0.0f, ColorA))
		{
			Client()->Restart();
		}
	}
	else if(State >= IUpdater::GETTING_MANIFEST && State < IUpdater::NEED_RESTART)
	{
		Ui()->RenderProgressBar(UpdateButton, Updater()->GetCurrentPercent() / 100.0f);
	}

	if(State == IUpdater::CLEAN && NeedUpdate)
	{
		str_format(aBuf, sizeof(aBuf), Localize("DDNet %s is out!"), Client()->LatestVersion());
		TextRender()->TextColor(1.0f, 0.4f, 0.4f, 1.0f);
	}
	else if(State == IUpdater::CLEAN)
	{
		aBuf[0] = '\0';
	}
	else if(State >= IUpdater::GETTING_MANIFEST && State < IUpdater::NEED_RESTART)
	{
		char aCurrentFile[64];
		Updater()->GetCurrentFile(aCurrentFile, sizeof(aCurrentFile));
		str_format(aBuf, sizeof(aBuf), Localize("Downloading %s:"), aCurrentFile);
	}
	else if(State == IUpdater::FAIL)
	{
		str_copy(aBuf, Localize("Update failed! Check log…"));
		TextRender()->TextColor(1.0f, 0.4f, 0.4f, 1.0f);
	}
	else if(State == IUpdater::NEED_RESTART)
	{
		str_copy(aBuf, Localize("DDNet Client updated!"));
		TextRender()->TextColor(TextColor);
	}
	Ui()->DoLabel(&VersionUpdate, aBuf, 14.0f, TEXTALIGN_ML);
	TextRender()->TextColor(TextRender()->DefaultTextColor());
#endif
	if(str_comp(GameClient()->m_Update.m_aVersionStr, "0") != 0)
	{
		// Split VersionUpdate into two halves.
		// CUIRect ManualButton, AutoButton;
		// VersionUpdate.VSplitMid(&ManualButton, &AutoButton);

		char aBuf[64];
		str_format(aBuf, sizeof(aBuf), Localize("FeX v%s is out!"), GameClient()->m_Update.m_aVersionStr);

		// Left button: Manual download.
		static CButtonContainer s_ManualUpdate;
		if(DoButton_Menu(&s_ManualUpdate, Localize(aBuf), 0, &VersionUpdate, BUTTONFLAG_LEFT, 0, IGraphics::CORNER_ALL, 5.0f, 0.0f, ColorA))
		{
			// Open the GitHub release page
			Client()->ViewLink("https://github.com/faffa81/FeX-V2-Client/releases/latest");
		}

		// Right button: Auto Update.
		// static CButtonContainer s_AutoUpdate;
		// if(DoButton_Menu(&s_AutoUpdate, Localize("Auto Update"), 0, &AutoButton, BUTTONFLAG_LEFT, 0, IGraphics::CORNER_ALL, 5.0f, 0.0f, ColorA))
		// {
		// 	// Start the auto updater.
		// 	GameClient()->m_FexUpdater.InitiateUpdate();
		// }
	}

	if(NewPage != -1)
	{
		m_ShowStart = false;
		SetMenuPage(NewPage);
	}
	TextRender()->TextColor(TextRender()->DefaultTextColor());
}

void CMenus::RunServer(const char **ppArguments, const size_t NumArguments)
{
#if defined(CONF_PLATFORM_ANDROID)
	if(StartAndroidServer(ppArguments, NumArguments))
	{
		m_ForceRefreshLanPage = true;
	}
	else
	{
		Client()->AddWarning(SWarning(Localize("Server could not be started. Make sure to grant the notification permission in the app settings so the server can run in the background.")));
	}
#else
	char aBuf[IO_MAX_PATH_LENGTH];
	Storage()->GetBinaryPath(PLAT_SERVER_EXEC, aBuf, sizeof(aBuf));
	// No / in binary path means to search in $PATH, so it is expected that the file can't be opened. Just try executing anyway.
	if(str_find(aBuf, "/") == nullptr || fs_is_file(aBuf))
	{
		m_ServerProcess.m_Process = shell_execute(aBuf, EShellExecuteWindowState::BACKGROUND, ppArguments, NumArguments);
		m_ForceRefreshLanPage = true;
	}
	else
	{
		Client()->AddWarning(SWarning(Localize("Server executable not found, can't run server")));
	}
#endif
}

void CMenus::KillServer()
{
#if defined(CONF_PLATFORM_ANDROID)
	ExecuteAndroidServerCommand("shutdown");
	m_ForceRefreshLanPage = true;
#else
	if(m_ServerProcess.m_Process && kill_process(m_ServerProcess.m_Process))
	{
		m_ServerProcess.m_Process = INVALID_PROCESS;
		m_ForceRefreshLanPage = true;
	}
#endif
}

bool CMenus::IsServerRunning() const
{
#if defined(CONF_PLATFORM_ANDROID)
	return IsAndroidServerRunning();
#else
	return m_ServerProcess.m_Process != INVALID_PROCESS;
#endif
}
