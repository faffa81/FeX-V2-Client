#include <base/log.h>
#include <base/math.h>
#include <base/system.h>

#include <engine/graphics.h>
#include <engine/shared/config.h>
#include <engine/shared/linereader.h>
#include <engine/shared/localization.h>
#include <engine/shared/protocol7.h>
#include <engine/storage.h>
#include <engine/textrender.h>

#include <game/generated/protocol.h>

#include <game/client/animstate.h>
#include <game/client/components/chat.h>
#include <game/client/components/menu_background.h>
#include <game/client/components/sounds.h>
#include <game/client/components/fex/fexbindwheel.h>
#include <game/client/gameclient.h>
#include <game/client/render.h>
#include <game/client/skin.h>
#include <game/client/ui.h>
#include <game/client/ui_listbox.h>
#include <game/client/ui_scrollregion.h>
#include <game/localization.h>

#include "../binds.h"
#include "../countryflags.h"
#include "../menus.h"
#include "../skins.h"
#include "game/client/components/fex/fextrails.h"

#include <array>
#include <chrono>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

using namespace FontIcons;
using namespace std::chrono_literals;

enum {
    FEX_TAB_SETTINGS = 0,
    FEX_TAB_VISUAL = 1,
    FEX_TAB_WARLIST = 2,
	FEX_TAB_BINDWHEEL = 3,
	FEX_TAB_STATUSBAR = 4,
    NUMBER_OF_FEX_TABS = 5
};

typedef struct
{
	const char *m_pName;
	const char *m_pCommand;
	int m_KeyId;
	int m_ModifierCombination;
} CKeyInfo;

static float s_Time = 0.0f;

const float FontSize = 14.0f;
const float LineSize = 20.0f;
const float HeadlineFontSize = 20.0f;
const float StandardFontSize = 14.0f;
const float EditBoxFontSize = 12.0f;

const float LineMargin = 20.0f;
const float Margin = 10.0f;
const float MarginSmall = 5.0f;
const float MarginExtraSmall = 2.5f;
const float MarginBetweenSections = 30.0f;
const float MarginBetweenViews = 30.0f;

const float HeadlineHeight = HeadlineFontSize + 0.0f;

const float HeaderHeight = FontSize + 5.0f + Margin;

const float ColorPickerLineSize = 25.0f;
const float ColorPickerLabelSize = 13.0f;
const float ColorPickerLineSpacing = 5.0f;

void CMenus::RenderSettingsFeX(CUIRect MainView)
{
	static int s_CurTab = 0;
    CUIRect TabBar, Button;
    int TabCount = NUMBER_OF_FEX_TABS;
    
    // Tab buttons

    MainView.HSplitTop(LineSize * 1.1f, &TabBar, &MainView);
	const float TabWidth = TabBar.w / TabCount;
	static CButtonContainer s_aPageTabs[NUMBER_OF_FEX_TABS] = {};
	const char *apTabNames[NUMBER_OF_FEX_TABS] = {
		Localize("FeX Settings"),
		Localize("FeX Visual Settings"),
		Localize("FeX Warlist"),
		Localize("FeX Bindwheel"),
		Localize("FeX Statusbar"),
	};

    for(int Tab = 0; Tab < NUMBER_OF_FEX_TABS; ++Tab)
	{
		int LeftTab = 0;
		int RightTab = NUMBER_OF_FEX_TABS - 1;

		TabBar.VSplitLeft(TabWidth, &Button, &TabBar);

		int Corners = Tab == LeftTab ? IGraphics::CORNER_L : Tab == RightTab ? IGraphics::CORNER_R :
													 IGraphics::CORNER_NONE;
		if(LeftTab == RightTab)
			Corners = IGraphics::CORNER_ALL;

		if(DoButton_MenuTab(&s_aPageTabs[Tab], apTabNames[Tab], s_CurTab == Tab, &Button, Corners, nullptr, nullptr, nullptr, nullptr, 4.0f))
		{
			s_CurTab = Tab;
		}
	}

	MainView.HSplitTop(Margin, nullptr, &MainView);

	if(Client()->State() == IClient::STATE_LOADING)
	{
		// Set the current tab based on the configuration
		if(g_Config.m_ClMenuTab == 1)
		{
			s_CurTab = FEX_TAB_SETTINGS;
		}
		else if(g_Config.m_ClMenuTab == 2)
		{
			s_CurTab = FEX_TAB_VISUAL;
		}
		else if(g_Config.m_ClMenuTab == 3)
		{
			s_CurTab = FEX_TAB_WARLIST;
		}
		else if(g_Config.m_ClMenuTab == 4)
		{
			s_CurTab = FEX_TAB_BINDWHEEL;
		}
		else if(g_Config.m_ClMenuTab == 5)
		{
			s_CurTab = FEX_TAB_STATUSBAR;
		}
	}

    // Render the selected tab content
    if(s_CurTab == FEX_TAB_SETTINGS)
    {
		g_Config.m_ClMenuTab = 1;
        // FeX Settings Tab
        CUIRect FreezeKillSettings, AutomationSettings, Settings1v1, FastInputSettings, ChatSettings, MiscSettings, Label;
		
		static CScrollRegion s_ScrollRegion;
		vec2 ScrollOffset(0.0f, 0.0f);
		CScrollRegionParams ScrollParams;
		ScrollParams.m_ScrollUnit = 120.0f;
		s_ScrollRegion.Begin(&MainView, &ScrollOffset, &ScrollParams);
		MainView.y += ScrollOffset.y;
        
        // Split the view into two sections with proper spacing
		MainView.VSplitMid(&FreezeKillSettings, &Settings1v1);

		// ************** Left Side ************** //
		{
			// ************** Freeze Kill ************** //
			{
				static float Offset = 0.0f;
				FreezeKillSettings.VMargin(5.0f, &FreezeKillSettings);
				FreezeKillSettings.HSplitTop(57.5f + Offset, &FreezeKillSettings, &AutomationSettings);
				if(s_ScrollRegion.AddRect(FreezeKillSettings))
				{
					Offset = 0.0f;
					// Freezekill frame
					FreezeKillSettings.Draw(ColorRGBA(1,1,1,0.25f), IGraphics::CORNER_ALL, 5.0f);
					FreezeKillSettings.VMargin(Margin, &FreezeKillSettings);
					
					// Freeze Kill heading
					FreezeKillSettings.HSplitTop(HeaderHeight, &Button, &FreezeKillSettings);
					Ui()->DoLabel(&Button, Localize("Freeze Kill"), HeadlineFontSize, TEXTALIGN_ML);
	
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClFreezeKill, Localize("Kill on Freeze"), &g_Config.m_ClFreezeKill, &FreezeKillSettings, LineSize);
	
					if(g_Config.m_ClFreezeKill)
					{
						Offset = Offset + 120.0f;
						DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClFreezeKillMultOnly, Localize("Only Enable on Multeasymap"), &g_Config.m_ClFreezeKillMultOnly, &FreezeKillSettings, LineSize);
	
						DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClFreezeKillIgnoreKillProt, Localize("Ignore Kill Protection"), &g_Config.m_ClFreezeKillIgnoreKillProt, &FreezeKillSettings, LineSize);
	
						DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClFreezeDontKillMoving, Localize("Don't Kill if Moving"), &g_Config.m_ClFreezeDontKillMoving, &FreezeKillSettings, LineSize);
	
						DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClFreezeKillOnlyFullFrozen, Localize("Only Kill if Fully Frozen"), &g_Config.m_ClFreezeKillOnlyFullFrozen, &FreezeKillSettings, LineSize);
	
						DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClFreezeKillWaitMs, Localize("Wait Until Kill"), &g_Config.m_ClFreezeKillWaitMs, &FreezeKillSettings, LineSize);
	
						DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClFreezeKillColor, Localize("Color for Freeze Kill bar"), &g_Config.m_ClFreezeKillColor, &FreezeKillSettings, LineSize);
						if(g_Config.m_ClFreezeKillWaitMs)
						{
							Offset = Offset + 40.0f;
							FreezeKillSettings.HSplitTop(2 * LineSize, &Button, &FreezeKillSettings);
							Ui()->DoScrollbarOption(&g_Config.m_ClFreezeKillMs, &g_Config.m_ClFreezeKillMs, &Button, Localize("Milliseconds to Wait For"), 1, 5000, &CUi::ms_LinearScrollbarScale, CUi::SCROLLBAR_OPTION_MULTILINE, "ms");
						}
						if(g_Config.m_ClFreezeKillColor)
						{
							Offset = Offset + 25.0f;
							static CButtonContainer s_freezeColor;
							DoLine_ColorPicker(&s_freezeColor, ColorPickerLineSize, ColorPickerLabelSize, ColorPickerLineSpacing, &FreezeKillSettings, Localize("freeze kill bar color"), &g_Config.m_ClFreezeKillColorCol, ColorRGBA(1.0f, 0.0f, 1.0f), false);	
						}
	
					}
				}
			}

			// ************** Automation ************** //
			{
				static float Offset = 0.0f;
				AutomationSettings.HSplitTop(10.0f, nullptr, &AutomationSettings);
				AutomationSettings.HSplitTop(280.0f + Offset, &AutomationSettings, &FastInputSettings);
				if(s_ScrollRegion.AddRect(AutomationSettings))
				{
					Offset = 0.0f;
					// Dummy connect frame
					AutomationSettings.Draw(ColorRGBA(1,1,1,0.25f), IGraphics::CORNER_ALL, 5.0f);
					AutomationSettings.Margin(15.0f, &AutomationSettings);
					
					// Auto dummy connect heading
					AutomationSettings.HSplitTop(HeaderHeight, &Button, &AutomationSettings);
					Ui()->DoLabel(&Button, Localize("Auto dummy connect"), HeadlineFontSize, TEXTALIGN_ML);
					
					// Auto Join Dummy
	
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClAutoJoinDummy, Localize("Auto dummy connect toggle (enables auto dummy join)"), &g_Config.m_ClAutoJoinDummy, &AutomationSettings, LineSize);
					
					// Auto dummy switch
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClAutoJoinDummySwitch, Localize("Auto dummy switch toggle (switches back to player)"), &g_Config.m_ClAutoJoinDummySwitch, &AutomationSettings, LineSize);
					
					// Auto dummy connect delay
					AutomationSettings.HSplitTop(5.0f, nullptr, &AutomationSettings); // Add spacing
					AutomationSettings.HSplitTop(20.0f, &Button, &AutomationSettings);
					Ui()->DoScrollbarOption(&g_Config.m_ClAutoJoinDummyDelay, &g_Config.m_ClAutoJoinDummyDelay, 
						&Button, "Auto dummy connect delay", 1, 20, &CUi::ms_LogarithmicScrollbarScale);
	
					// Auto team connect heading
					AutomationSettings.HSplitTop(25.0f, &Button, &AutomationSettings);
					Ui()->DoLabel(&Button, Localize("Auto Team join"), HeadlineFontSize, TEXTALIGN_ML);
					
					// Auto Join team
					AutomationSettings.HSplitTop(5.0f, nullptr, &AutomationSettings); // Add spacing
					AutomationSettings.HSplitTop(20.0f, &Button, &AutomationSettings);
					Ui()->DoScrollbarOption(&g_Config.m_ClAutoJoinTeam, &g_Config.m_ClAutoJoinTeam, 
						&Button, "Auto join Team", 0, 63, &CUi::ms_LogarithmicScrollbarScale);
					
					// Auto team lock
	
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClAutoJoinTeamLock, Localize("Auto Team lock"), &g_Config.m_ClAutoJoinTeamLock, &AutomationSettings, LineSize);
					
					// Auto team join delay
					AutomationSettings.HSplitTop(5.0f, nullptr, &AutomationSettings); // Add spacing
					AutomationSettings.HSplitTop(20.0f, &Button, &AutomationSettings);
					Ui()->DoScrollbarOption(&g_Config.m_ClAutoJoinTeamDelay, &g_Config.m_ClAutoJoinTeamDelay, 
						&Button, "Auto team join delay", 1, 20, &CUi::ms_LogarithmicScrollbarScale);\


					AutomationSettings.HSplitTop(2.5f, &Button, &AutomationSettings);

					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClAutoReplyTabbedOut, Localize("Auto Reply Tabbed out"), &g_Config.m_ClAutoReplyTabbedOut, &AutomationSettings, LineSize);

					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClAutoReplyPinged, Localize("Auto Reply Pinged"), &g_Config.m_ClAutoReplyPinged, &AutomationSettings, LineSize);

					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClAutoReplyMuted, Localize("Auto Reply muted"), &g_Config.m_ClAutoReplyMuted, &AutomationSettings, LineSize);

	
					if(g_Config.m_ClAutoReplyPinged)
					{
						Offset = Offset + 45.0f;
						AutomationSettings.HSplitTop(20.0f, &Button, &AutomationSettings);
						static CLineInput s_AutoPingedInput(g_Config.m_ClAutoReplyMsgPinged, sizeof(g_Config.m_ClAutoReplyMsgPinged));
						Ui()->DoLabel(&Button, "Auto pinged message:", 14.0f, TEXTALIGN_ML);
						AutomationSettings.HSplitTop(25.0f, &Button, &AutomationSettings);
						Ui()->DoEditBox(&s_AutoPingedInput, &Button, 14.0f);
					}
					if(g_Config.m_ClAutoReplyTabbedOut)
					{
						Offset = Offset + 45.0f;
						AutomationSettings.HSplitTop(20.0f, &Button, &AutomationSettings);
						static CLineInput s_AutoTabbedInput(g_Config.m_ClAutoReplyMsgTabbed, sizeof(g_Config.m_ClAutoReplyMsgTabbed));
						Ui()->DoLabel(&Button, "Auto tabbed out pinged message:", 14.0f, TEXTALIGN_ML);
						AutomationSettings.HSplitTop(25.0f, &Button, &AutomationSettings);
						Ui()->DoEditBox(&s_AutoTabbedInput, &Button, 14.0f);
					}
					if(g_Config.m_ClAutoReplyMuted)
					{
						Offset = Offset + 45.0f;
						AutomationSettings.HSplitTop(20.0f, &Button, &AutomationSettings);
						static CLineInput s_AutoMutedInput(g_Config.m_ClAutoReplyMutedMsg, sizeof(g_Config.m_ClAutoReplyMutedMsg));
						Ui()->DoLabel(&Button, "Auto muted message:", 14.0f, TEXTALIGN_ML);
						AutomationSettings.HSplitTop(25.0f, &Button, &AutomationSettings);
						Ui()->DoEditBox(&s_AutoMutedInput, &Button, 14.0f);
					}
				}
			}

			// ************** Fast Input Settings ************** //
			{
				FastInputSettings.HSplitTop(10.0f, nullptr, &FastInputSettings);
				FastInputSettings.HSplitTop(385.0f, &FastInputSettings, nullptr);
				if(s_ScrollRegion.AddRect(FastInputSettings))
				{
					FastInputSettings.Draw(ColorRGBA(1,1,1,0.25f), IGraphics::CORNER_ALL, 5.0f);
					FastInputSettings.Margin(Margin, &FastInputSettings);
	
					// ***** Input ***** //
					FastInputSettings.HSplitTop(HeaderHeight, &Label, &FastInputSettings);
					Ui()->DoLabel(&Label, Localize("Input"), HeadlineFontSize, TEXTALIGN_ML);
	
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClFastInput, Localize("Fast Inputs (-20ms visual delay)"), &g_Config.m_ClFastInput, &FastInputSettings, LineSize);
	
					if(g_Config.m_ClFastInput)
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClFastInputOthers, Localize("Extra tick other tees (increases other tees latency, \nmakes dragging slightly easier when using fast input)"), &g_Config.m_ClFastInputOthers, &FastInputSettings, LineSize);
					else
					FastInputSettings.HSplitTop(LineSize, nullptr, &FastInputSettings);
					// A little extra spacing because these are multi line
					FastInputSettings.HSplitTop(MarginSmall, nullptr, &FastInputSettings);
	
					// ***** Anti Latency Tools ***** //
					FastInputSettings.HSplitTop(HeaderHeight, &Label, &FastInputSettings);
					Ui()->DoLabel(&Label, Localize("Anti Latency Tools"), HeadlineFontSize, TEXTALIGN_ML);
					FastInputSettings.HSplitTop(MarginSmall, nullptr, &FastInputSettings);
	
					FastInputSettings.HSplitTop(LineSize, &Button, &FastInputSettings);
					Ui()->DoScrollbarOption(&g_Config.m_ClPredictionMargin, &g_Config.m_ClPredictionMargin, &Button, Localize("Prediction Margin"), 10, 75, &CUi::ms_LinearScrollbarScale, CUi::SCROLLBAR_OPTION_NOCLAMPVALUE, "ms");
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClRemoveAnti, Localize("Remove prediction & antiping in freeze"), &g_Config.m_ClRemoveAnti, &FastInputSettings, LineSize);
					if(g_Config.m_ClRemoveAnti)
					{
					if(g_Config.m_ClUnfreezeLagDelayTicks < g_Config.m_ClUnfreezeLagTicks)
					g_Config.m_ClUnfreezeLagDelayTicks = g_Config.m_ClUnfreezeLagTicks;
					FastInputSettings.HSplitTop(LineSize, &Button, &FastInputSettings);
					DoSliderWithScaledValue(&g_Config.m_ClUnfreezeLagTicks, &g_Config.m_ClUnfreezeLagTicks, &Button, Localize("Amount"), 100, 300, 20, &CUi::ms_LinearScrollbarScale, CUi::SCROLLBAR_OPTION_NOCLAMPVALUE, "ms");
					FastInputSettings.HSplitTop(LineSize, &Button, &FastInputSettings);
					DoSliderWithScaledValue(&g_Config.m_ClUnfreezeLagDelayTicks, &g_Config.m_ClUnfreezeLagDelayTicks, &Button, Localize("Delay"), 100, 3000, 20, &CUi::ms_LinearScrollbarScale, CUi::SCROLLBAR_OPTION_NOCLAMPVALUE, "ms");
					}
					else
					FastInputSettings.HSplitTop(LineSize * 2, nullptr, &FastInputSettings);
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClUnpredOthersInFreeze, Localize("Dont predict other players if you are frozen"), &g_Config.m_ClUnpredOthersInFreeze, &FastInputSettings, LineSize);
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClPredMarginInFreeze, Localize("Adjust your prediction margin while frozen"), &g_Config.m_ClPredMarginInFreeze, &FastInputSettings, LineSize);
					FastInputSettings.HSplitTop(LineSize, &Button, &FastInputSettings);
					if(g_Config.m_ClPredMarginInFreeze)
					Ui()->DoScrollbarOption(&g_Config.m_ClPredMarginInFreezeAmount, &g_Config.m_ClPredMarginInFreezeAmount, &Button, Localize("Frozen Margin"), 0, 100, &CUi::ms_LinearScrollbarScale, 0, "ms");
	
					// ***** Improved Anti Ping ***** //
					FastInputSettings.HSplitTop(HeaderHeight, &Label, &FastInputSettings);
					Ui()->DoLabel(&Label, Localize("Anti Ping Smoothing"), HeadlineFontSize, TEXTALIGN_ML);
					FastInputSettings.HSplitTop(MarginSmall, nullptr, &FastInputSettings);
	
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClAntiPingImproved, Localize("Use new smoothing algorithm"), &g_Config.m_ClAntiPingImproved, &FastInputSettings, LineSize);
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClAntiPingStableDirection, Localize("Optimistic prediction along stable direction"), &g_Config.m_ClAntiPingStableDirection, &FastInputSettings, LineSize);
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClAntiPingNegativeBuffer, Localize("Negative stability buffer (for Gores)"), &g_Config.m_ClAntiPingNegativeBuffer, &FastInputSettings, LineSize);
					FastInputSettings.HSplitTop(LineSize, &Button, &FastInputSettings);
					Ui()->DoScrollbarOption(&g_Config.m_ClAntiPingUncertaintyScale, &g_Config.m_ClAntiPingUncertaintyScale, &Button, Localize("Uncertainty duration"), 50, 400, &CUi::ms_LinearScrollbarScale, CUi::SCROLLBAR_OPTION_NOCLAMPVALUE, "%");
				}
			}
		}

		// ************** Right Side ************** //

		{
			// ************** 1v1 Settings ************** //
			{
				static float Offset = 0.0f;
				Settings1v1.VMargin(5.0f, &Settings1v1);
				Settings1v1.HSplitTop(160.0f + Offset, &Settings1v1, &ChatSettings);
				if(s_ScrollRegion.AddRect(Settings1v1))
				{
					Offset = 0.0f;
					Settings1v1.Draw(ColorRGBA(1,1,1,0.25f), IGraphics::CORNER_ALL, 5.0f);
					Settings1v1.VMargin(Margin, &Settings1v1);

					Settings1v1.HSplitTop(HeaderHeight, &Label, &Settings1v1);
					Ui()->DoLabel(&Label, Localize("1v1"), HeadlineFontSize, TEXTALIGN_ML);

					// Score Limit Slider
					Settings1v1.HSplitTop(20.0f, &Button, &Settings1v1);
					Ui()->DoScrollbarOption(&g_Config.m_Cl1v1ModeScoreLimit, &g_Config.m_Cl1v1ModeScoreLimit, 
						&Button, "Score Limit", 1, 50, &CUi::ms_LogarithmicScrollbarScale);
	
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_Cl1v1ModeShowHud, Localize("1v1 Mode hud"), &g_Config.m_Cl1v1ModeShowHud, &Settings1v1, LineSize);

					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_Cl1v1ModeEcho, Localize("1v1 Mode Echo message"), &g_Config.m_Cl1v1ModeEcho, &Settings1v1, LineSize);
	
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_Cl1v1ModeKillLock, Localize("1v1 Mode kill lock"), &g_Config.m_Cl1v1ModeKillLock, &Settings1v1, LineSize);

					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_Cl1v1ModeHudColor, Localize("1v1 Mode hud color"), &g_Config.m_Cl1v1ModeHudColor, &Settings1v1, LineSize);

					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_Cl1v1ModeCustom, Localize("1v1 Mode chat message"), &g_Config.m_Cl1v1ModeCustom, &Settings1v1, LineSize);
					if(g_Config.m_Cl1v1ModeHudColor)
					{
						Offset = Offset + 25.0f;
						static CButtonContainer s_1v1Color;
						DoLine_ColorPicker(&s_1v1Color, ColorPickerLineSize, ColorPickerLabelSize, ColorPickerLineSpacing, &Settings1v1, Localize("1v1 text color"), &g_Config.m_Cl1v1ModeTextColor, ColorRGBA(1.0f, 1.0f, 1.0f), false);
					}
					if(g_Config.m_Cl1v1ModeCustom)
					{
						Offset = Offset + 80.0f;
						Settings1v1.HSplitTop(35.0f, &Label, &Settings1v1);
						Ui()->DoLabel(&Label, Localize("Custom 1v1 Message: %s = string, %d = score | example: %s %d | %d %s"), HeadlineFontSize, TEXTALIGN_ML);

						Settings1v1.HSplitTop(20.0f, &Button, &Settings1v1);
						static CLineInput s_1v1CustomMsgInput(g_Config.m_Cl1v1ModeCustomMsg, sizeof(g_Config.m_Cl1v1ModeCustomMsg));
						s_1v1CustomMsgInput.SetEmptyText("%s %d | %d %s");
						Ui()->DoLabel(&Button, "1v1 message:", 14.0f, TEXTALIGN_ML);
						Settings1v1.HSplitTop(25.0f, &Button, &Settings1v1);
						Ui()->DoEditBox(&s_1v1CustomMsgInput, &Button, 14.0f);
					}
				}
			}

			// ************** Chat Settings ************** //
			{
				ChatSettings.HSplitTop(10.0f, nullptr, &ChatSettings);
				ChatSettings.HSplitTop(385.0f, &ChatSettings, &MiscSettings);
				if(s_ScrollRegion.AddRect(ChatSettings))
				{
					ChatSettings.Draw(ColorRGBA(1,1,1,0.25f), IGraphics::CORNER_ALL, 5.0f);
					ChatSettings.Margin(Margin, &ChatSettings);
	
					ChatSettings.HSplitTop(HeaderHeight, &Button, &ChatSettings);
					Ui()->DoLabel(&Button, Localize("Chat Settings"), HeadlineFontSize, TEXTALIGN_ML);
					{	
						DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClShowMutedInConsole, ("Show Messages of Muted People in The Console"), &g_Config.m_ClShowMutedInConsole, &ChatSettings, LineSize);
	
						DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClHideEnemyChat, ("Hide Enemy Chat (Shows in Console)"), &g_Config.m_ClHideEnemyChat, &ChatSettings, LineSize);
	
						
	
						ChatSettings.HSplitTop(10.0f, &Button, &ChatSettings);
	
						// Please no one ask me.
						std::array<float, 5> Sizes = {
							TextRender()->TextBoundingBox(FontSize, "Friend Prefix").m_W,
							TextRender()->TextBoundingBox(FontSize, "Spec Prefix").m_W,
							TextRender()->TextBoundingBox(FontSize, "Server Prefix").m_W,
							TextRender()->TextBoundingBox(FontSize, "Client Prefix").m_W,
							TextRender()->TextBoundingBox(FontSize, "Warlist Prefix").m_W,
						};
						float Length = *std::max_element(Sizes.begin(), Sizes.end()) + 20.0f;
	
						{
							ChatSettings.HSplitTop(19.9f, &Button, &MainView);
	
							Button.VSplitLeft(0.0f, &Button, &ChatSettings);
							Button.VSplitLeft(Length, &Label, &Button);
							Button.VSplitLeft(85.0f, &Button, 0);
	
							static CLineInput s_PrefixMsg;
							s_PrefixMsg.SetBuffer(g_Config.m_ClFriendPrefix, sizeof(g_Config.m_ClFriendPrefix));
							s_PrefixMsg.SetEmptyText("alt + num3");
							if(DoButton_CheckBox(&g_Config.m_ClMessageFriend, "Friend Prefix", g_Config.m_ClMessageFriend, &ChatSettings))
							{
								g_Config.m_ClMessageFriend ^= 1;
							}
							Ui()->DoEditBox(&s_PrefixMsg, &Button, 14.0f);
						}
	
						// spectate prefix
						ChatSettings.HSplitTop(21.0f, &Button, &ChatSettings);
						{
							ChatSettings.HSplitTop(19.9f, &Button, &MainView);
	
							Button.VSplitLeft(0.0f, &Button, &ChatSettings);
							Button.VSplitLeft(Length, &Label, &Button);
							Button.VSplitLeft(85.0f, &Button, 0);
	
							static CLineInput s_PrefixMsg;
							s_PrefixMsg.SetBuffer(g_Config.m_ClSpecPrefix, sizeof(g_Config.m_ClSpecPrefix));
							s_PrefixMsg.SetEmptyText("alt+7");
							if(DoButton_CheckBox(&g_Config.m_ClSpectatePrefix, "Spec Prefix", g_Config.m_ClSpectatePrefix, &ChatSettings))
							{
								g_Config.m_ClSpectatePrefix ^= 1;
							}
							Ui()->DoEditBox(&s_PrefixMsg, &Button, 14.0f);
						}
	
						// server prefix
						ChatSettings.HSplitTop(21.0f, &Button, &ChatSettings);
						{
							ChatSettings.HSplitTop(19.9f, &Button, &MainView);
	
							Button.VSplitLeft(0.0f, &Button, &ChatSettings);
							Button.VSplitLeft(Length, &Label, &Button);
							Button.VSplitLeft(85.0f, &Button, 0);
	
							static CLineInput s_PrefixMsg;
							s_PrefixMsg.SetBuffer(g_Config.m_ClServerPrefix, sizeof(g_Config.m_ClServerPrefix));
							s_PrefixMsg.SetEmptyText("*** ");
							if(DoButton_CheckBox(&g_Config.m_ClChatServerPrefix, "Server Prefix", g_Config.m_ClChatServerPrefix, &ChatSettings))
							{
								g_Config.m_ClChatServerPrefix ^= 1;
							}
							Ui()->DoEditBox(&s_PrefixMsg, &Button, 14.0f);
						}
	
						// client prefix
						ChatSettings.HSplitTop(21.0f, &Button, &ChatSettings);
						{
							ChatSettings.HSplitTop(19.9f, &Button, &MainView);
	
							Button.VSplitLeft(0.0f, &Button, &ChatSettings);
							Button.VSplitLeft(Length, &Label, &Button);
							Button.VSplitLeft(85.0f, &Button, 0);
	
							static CLineInput s_PrefixMsg;
							s_PrefixMsg.SetBuffer(g_Config.m_ClClientPrefix, sizeof(g_Config.m_ClClientPrefix));
							s_PrefixMsg.SetEmptyText("alt0151");
							if(DoButton_CheckBox(&g_Config.m_ClChatClientPrefix, "Client Prefix", g_Config.m_ClChatClientPrefix, &ChatSettings))
							{
								g_Config.m_ClChatClientPrefix ^= 1;
							}
							Ui()->DoEditBox(&s_PrefixMsg, &Button, 14.0f);
						}
						ChatSettings.HSplitTop(21.0f, &Button, &ChatSettings);
						{
							ChatSettings.HSplitTop(19.9f, &Button, &MainView);
	
							Button.VSplitLeft(0.0f, &Button, &ChatSettings);
							Button.VSplitLeft(Length, &Label, &Button);
							Button.VSplitLeft(85.0f, &Button, 0);
	
							static CLineInput s_PrefixMsg;
							s_PrefixMsg.SetBuffer(g_Config.m_ClWarlistPrefix, sizeof(g_Config.m_ClWarlistPrefix));
							s_PrefixMsg.SetEmptyText("alt4");
							if(DoButton_CheckBox(&g_Config.m_ClWarlistPrefixes, "Warlist Prefix", g_Config.m_ClWarlistPrefixes, &ChatSettings))
							{
								g_Config.m_ClWarlistPrefixes ^= 1;
							}
							Ui()->DoEditBox(&s_PrefixMsg, &Button, 14.0f);
						}
						ChatSettings.HSplitTop(55.0f, &Button, &ChatSettings);
						Ui()->DoLabel(&Button, Localize("Chat Preview"), FontSize + 3, TEXTALIGN_ML);
						ChatSettings.HSplitTop(-15.0f, &Button, &ChatSettings);
	
						RenderChatPreview(ChatSettings);
					}
				}
			}
			
			// ************** Misc Settings ************** //
			{
				MiscSettings.HSplitTop(10.0f, nullptr, &MiscSettings);
				MiscSettings.HSplitTop(175.0f, &MiscSettings, nullptr);
				if(s_ScrollRegion.AddRect(MiscSettings))
				{
					MiscSettings.Draw(ColorRGBA(1,1,1,0.25f), IGraphics::CORNER_ALL, 5.0f);
					MiscSettings.Margin(Margin, &MiscSettings);
	
					MiscSettings.HSplitTop(HeaderHeight, &Button, &MiscSettings);
					Ui()->DoLabel(&Button, Localize("Miscellaneous"), HeadlineFontSize, TEXTALIGN_ML);
	
					{
						static std::vector<const char *> s_FontDropDownNames = {};
						static CUi::SDropDownState s_FontDropDownState;
						static CScrollRegion s_FontDropDownScrollRegion;
						s_FontDropDownState.m_SelectionPopupContext.m_pScrollRegion = &s_FontDropDownScrollRegion;
						s_FontDropDownState.m_SelectionPopupContext.m_SpecialFontRenderMode = true;
						int FontSelectedOld = -1;
						for(size_t i = 0; i < TextRender()->GetCustomFaces()->size(); ++i)
						{
							if(s_FontDropDownNames.size() != TextRender()->GetCustomFaces()->size())
								s_FontDropDownNames.push_back(TextRender()->GetCustomFaces()->at(i).c_str());
		
							if(str_find_nocase(g_Config.m_ClCustomFont, TextRender()->GetCustomFaces()->at(i).c_str()))
								FontSelectedOld = i;
						}
						CUIRect FontDropDownRect, FontDirectory;
						MiscSettings.HSplitTop(LineSize, &FontDropDownRect, &MiscSettings);
		
						float Length = TextRender()->TextBoundingBox(FontSize, "Custom Font:").m_W + 3.5f;
		
						FontDropDownRect.VSplitLeft(Length, &Label, &FontDropDownRect);
						FontDropDownRect.VSplitRight(20.0f, &FontDropDownRect, &FontDirectory);
						FontDropDownRect.VSplitRight(MarginSmall, &FontDropDownRect, nullptr);
		
						Ui()->DoLabel(&Label, Localize("Custom Font:"), FontSize, TEXTALIGN_ML);
						const int FontSelectedNew = Ui()->DoDropDown(&FontDropDownRect, FontSelectedOld, s_FontDropDownNames.data(), s_FontDropDownNames.size(), s_FontDropDownState);
						if(FontSelectedOld != FontSelectedNew)
						{
							str_copy(g_Config.m_ClCustomFont, s_FontDropDownNames[FontSelectedNew]);
							FontSelectedOld = FontSelectedNew;
							TextRender()->SetCustomFace(g_Config.m_ClCustomFont);
		
							// Reload *hopefully* all Fonts
							TextRender()->OnPreWindowResize();
							GameClient()->OnWindowResize();
							GameClient()->Editor()->OnWindowResize();
							GameClient()->m_MapImages.SetTextureScale(101);
							GameClient()->m_MapImages.SetTextureScale(g_Config.m_ClTextEntitiesSize);
						}
		
						static CButtonContainer s_FontDirectoryId;
						if(DoButton_FontIcon(&s_FontDirectoryId, FONT_ICON_FOLDER, 0, &FontDirectory, IGraphics::CORNER_ALL))
						{
							Storage()->CreateFolder("data/fex", IStorage::TYPE_ABSOLUTE);
							Storage()->CreateFolder("data/fex/fonts", IStorage::TYPE_ABSOLUTE);
							Client()->ViewFile("data/fex/fonts");
						}
					}
					{
						MiscSettings.HSplitTop(35.0f, &Button, &MiscSettings);
						Ui()->DoLabel(&Button, Localize("Ad bots"), FontSize, TEXTALIGN_ML);
						DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClAutoAddOnNameChange, ("Auto add group entries after rename"), &g_Config.m_ClAutoAddOnNameChange, &MiscSettings, LineSize);
						MiscSettings.HSplitTop(2 * LineSize, &Button, &MiscSettings);
						Ui()->DoScrollbarOption(&g_Config.m_ClDismissAdBots, &g_Config.m_ClDismissAdBots, &Button, Localize("Config Value: 1-dismisses adbots, 2-adds votekick if you say yes in chat, 3-direct votekicks adbots"), 0, 3, &CUi::ms_LinearScrollbarScale, CUi::SCROLLBAR_OPTION_MULTILINE);
					}
				}
			}
		}
		s_ScrollRegion.End();
    }

	if(s_CurTab == FEX_TAB_VISUAL)
	{
		g_Config.m_ClMenuTab = 2;
        // FeX Visual Tab
        CUIRect TrailSettings, VisualSettings, OutlineSettings, PlayerIndicatorSettings, Label;
		
		static CScrollRegion s_ScrollRegion;
		vec2 ScrollOffset(0.0f, 0.0f);
		CScrollRegionParams ScrollParams;
		ScrollParams.m_ScrollUnit = 120.0f;
		s_ScrollRegion.Begin(&MainView, &ScrollOffset, &ScrollParams);
		MainView.y += ScrollOffset.y;

		MainView.VSplitMid(&TrailSettings, &VisualSettings);
		// left
		{
			static float Offset = 0.0f;
			TrailSettings.VMargin(5.0f, &TrailSettings);
			TrailSettings.HSplitTop(235.0f + Offset, &TrailSettings, &OutlineSettings);
			{
				if(s_ScrollRegion.AddRect(TrailSettings))
				{
					Offset = 0.0f;
					TrailSettings.Draw(ColorRGBA(1,1,1,0.25f), IGraphics::CORNER_ALL, 5.0f);
					TrailSettings.VMargin(Margin, &TrailSettings);

					// ***** Tee Trails ***** //
					TrailSettings.HSplitTop(HeaderHeight, &Label, &TrailSettings);
					Ui()->DoLabel(&Label, Localize("Tee Trails"), HeadlineFontSize, TEXTALIGN_ML);
					TrailSettings.HSplitTop(MarginSmall, nullptr, &TrailSettings);

					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClTeeTrail, Localize("Enable tee trails"), &g_Config.m_ClTeeTrail, &TrailSettings, LineSize);
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClTeeTrailOthers, Localize("Show other tees' trails"), &g_Config.m_ClTeeTrailOthers, &TrailSettings, LineSize);
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClTeeTrailFade, Localize("Fade trail alpha"), &g_Config.m_ClTeeTrailFade, &TrailSettings, LineSize);
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClTeeTrailTaper, Localize("Taper trail width"), &g_Config.m_ClTeeTrailTaper, &TrailSettings, LineSize);

					TrailSettings.HSplitTop(MarginExtraSmall, nullptr, &TrailSettings);
					std::vector<const char *> s_TrailDropDownNames;
					s_TrailDropDownNames = {Localize("Solid"), Localize("Tee"), Localize("Rainbow"), Localize("Speed")};
					static CUi::SDropDownState s_TrailDropDownState;
					static CScrollRegion s_TrailDropDownScrollRegion;
					s_TrailDropDownState.m_SelectionPopupContext.m_pScrollRegion = &s_TrailDropDownScrollRegion;
					int TrailSelectedOld = g_Config.m_ClTeeTrailColorMode - 1;
					CUIRect TrailDropDownRect;
					TrailSettings.HSplitTop(LineSize, &TrailDropDownRect, &TrailSettings);
					const int TrailSelectedNew = Ui()->DoDropDown(&TrailDropDownRect, TrailSelectedOld, s_TrailDropDownNames.data(), s_TrailDropDownNames.size(), s_TrailDropDownState);
					if(TrailSelectedOld != TrailSelectedNew)
					{
					g_Config.m_ClTeeTrailColorMode = TrailSelectedNew + 1;
					TrailSelectedOld = TrailSelectedNew;
					}
					TrailSettings.HSplitTop(MarginSmall, nullptr, &TrailSettings);

					static CButtonContainer s_TeeTrailColor;
					if(g_Config.m_ClTeeTrailColorMode == CTrails::COLORMODE_SOLID)
					{
						DoLine_ColorPicker(&s_TeeTrailColor, ColorPickerLineSize, ColorPickerLabelSize, ColorPickerLineSpacing, &TrailSettings, Localize("Tee trail color"), &g_Config.m_ClTeeTrailColor, ColorRGBA(1.0f, 1.0f, 1.0f), false);
					}
					else
						TrailSettings.HSplitTop(ColorPickerLineSize + ColorPickerLineSpacing, &Button, &TrailSettings);

					TrailSettings.HSplitTop(LineSize, &Button, &TrailSettings);
					Ui()->DoScrollbarOption(&g_Config.m_ClTeeTrailWidth, &g_Config.m_ClTeeTrailWidth, &Button, Localize("Trail width"), 0, 20);
					TrailSettings.HSplitTop(LineSize, &Button, &TrailSettings);
					Ui()->DoScrollbarOption(&g_Config.m_ClTeeTrailLength, &g_Config.m_ClTeeTrailLength, &Button, Localize("Trail length"), 0, 200);
					TrailSettings.HSplitTop(LineSize, &Button, &TrailSettings);
					Ui()->DoScrollbarOption(&g_Config.m_ClTeeTrailAlpha, &g_Config.m_ClTeeTrailAlpha, &Button, Localize("Trail alpha"), 0, 100);

					TrailSettings.HSplitTop(MarginSmall, nullptr, &TrailSettings);
				}
			}
			// Outline Settings
			OutlineSettings.HSplitTop(10.0f, nullptr, &OutlineSettings);
			OutlineSettings.HSplitTop(405.0f, &OutlineSettings, nullptr);
			if(s_ScrollRegion.AddRect(OutlineSettings))
			{
				OutlineSettings.Draw(ColorRGBA(1,1,1,0.25f), IGraphics::CORNER_ALL, 5.0f);
				OutlineSettings.Margin(Margin, &OutlineSettings);

				OutlineSettings.HSplitTop(HeaderHeight, &Button, &OutlineSettings);
				Ui()->DoLabel(&Button, Localize("Outlines"), HeadlineFontSize, TEXTALIGN_ML);
				{
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClOutline, Localize("Enable Outlines"), &g_Config.m_ClOutline, &OutlineSettings, LineMargin);
					OutlineSettings.HSplitTop(5.0f, &Button, &OutlineSettings);
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClOutlineEntities, Localize("Only show outlines in entities"), &g_Config.m_ClOutlineEntities, &OutlineSettings, LineMargin);
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClOutlineFreeze, Localize("Outline freeze & deep"), &g_Config.m_ClOutlineFreeze, &OutlineSettings, LineMargin);
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClOutlineSolid, Localize("Outline walls"), &g_Config.m_ClOutlineSolid, &OutlineSettings, LineMargin);
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClOutlineTele, Localize("Outline teleporter"), &g_Config.m_ClOutlineTele, &OutlineSettings, LineMargin);
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClOutlineUnFreeze, Localize("Outline unfreeze & undeep"), &g_Config.m_ClOutlineUnFreeze, &OutlineSettings, LineMargin);

					{
						OutlineSettings.HSplitTop(5.0f, &Button, &OutlineSettings);
						OutlineSettings.HSplitTop(20.0f, &Button, &OutlineSettings);
						Button.VSplitLeft(150.0f, &Label, &Button);
						char aBuf[64];
						str_format(aBuf, sizeof(aBuf), "%s: %i ", "Outline Width", g_Config.m_ClOutlineWidth);
						Ui()->DoLabel(&Label, aBuf, 14.0f, TEXTALIGN_LEFT);
						g_Config.m_ClOutlineWidth = (int)(Ui()->DoScrollbarH(&g_Config.m_ClOutlineWidth, &Button, (g_Config.m_ClOutlineWidth - 1) / 15.0f) * 15.0f) + 1;
					}
					{
						OutlineSettings.HSplitTop(5.0f, &Button, &OutlineSettings);
						OutlineSettings.HSplitTop(20.0f, &Button, &OutlineSettings);
						Button.VSplitLeft(150.0f, &Label, &Button);
						char aBuf[64];
						str_format(aBuf, sizeof(aBuf), "%s: %i ", "Outline Alpha", g_Config.m_ClOutlineAlpha);
						Ui()->DoLabel(&Label, aBuf, 14.0f, TEXTALIGN_LEFT);
						g_Config.m_ClOutlineAlpha = (int)(Ui()->DoScrollbarH(&g_Config.m_ClOutlineAlpha, &Button, (g_Config.m_ClOutlineAlpha) / 100.0f) * 100.0f);
					}
					{
						OutlineSettings.HSplitTop(5.0f, &Button, &OutlineSettings);
						OutlineSettings.HSplitTop(20.0f, &Button, &OutlineSettings);
						Button.VSplitLeft(185.0f, &Label, &Button);
						char aBuf[64];
						str_format(aBuf, sizeof(aBuf), "%s: %i ", "Outline Alpha (walls)", g_Config.m_ClOutlineAlphaSolid);
						Ui()->DoLabel(&Label, aBuf, 14.0f, TEXTALIGN_LEFT);
						g_Config.m_ClOutlineAlphaSolid = (int)(Ui()->DoScrollbarH(&g_Config.m_ClOutlineAlphaSolid, &Button, (g_Config.m_ClOutlineAlphaSolid) / 100.0f) * 100.0f);
					}
					static CButtonContainer OutlineColorFreezeID, OutlineColorSolidID, OutlineColorTeleID, OutlineColorUnfreezeID, OutlineColorKillID;

					OutlineSettings.HSplitTop(5.0f, 0x0, &OutlineSettings);
					OutlineSettings.VSplitLeft(-5.0f, 0x0, &OutlineSettings);

					OutlineSettings.HSplitTop(2.0f, &OutlineSettings, &OutlineSettings);
					DoLine_ColorPicker(&OutlineColorFreezeID, ColorPickerLineSize, ColorPickerLabelSize, ColorPickerLineSpacing, &OutlineSettings, Localize("Freeze Outline Color"), &g_Config.m_ClOutlineColorFreeze, ColorRGBA(0.0f, 0.0f, 0.0f, 1.0f), false);

					OutlineSettings.HSplitTop(2.0f, &OutlineSettings, &OutlineSettings);
					DoLine_ColorPicker(&OutlineColorSolidID, ColorPickerLineSize, ColorPickerLabelSize, ColorPickerLineSpacing, &OutlineSettings, Localize("Walls Outline Color"), &g_Config.m_ClOutlineColorSolid, ColorRGBA(0.0f, 0.0f, 0.0f, 1.0f), false);

					OutlineSettings.HSplitTop(2.0f, &OutlineSettings, &OutlineSettings);
					DoLine_ColorPicker(&OutlineColorTeleID, ColorPickerLineSize, ColorPickerLabelSize, ColorPickerLineSpacing, &OutlineSettings, Localize("Teleporter Outline Color"), &g_Config.m_ClOutlineColorTele, ColorRGBA(0.0f, 0.0f, 0.0f, 1.0f), false);

					OutlineSettings.HSplitTop(2.0f, &OutlineSettings, &OutlineSettings);
					DoLine_ColorPicker(&OutlineColorUnfreezeID, ColorPickerLineSize, ColorPickerLabelSize, ColorPickerLineSpacing, &OutlineSettings, Localize("Unfreeze Outline Color"), &g_Config.m_ClOutlineColorUnfreeze, ColorRGBA(0.0f, 0.0f, 0.0f, 1.0f), false);

					DoLine_ColorPicker(&OutlineColorKillID, ColorPickerLineSize, ColorPickerLabelSize, ColorPickerLineSpacing, &OutlineSettings, Localize("Kill outline color"), &g_Config.m_ClOutlineColorKill, ColorRGBA(0.0f, 0.0f, 0.0f), false);

				}
			}
		}

		// right
		{
			static float Offset = 0.0f;
			VisualSettings.VMargin(5.0f, &VisualSettings);
			VisualSettings.HSplitTop(100.0f + Offset, &VisualSettings, &PlayerIndicatorSettings);
			{
				if(s_ScrollRegion.AddRect(VisualSettings))
				{
					Offset = 0.0f;
					VisualSettings.Draw(ColorRGBA(1,1,1,0.25f), IGraphics::CORNER_ALL, 5.0f);
					VisualSettings.VMargin(Margin, &VisualSettings);
					
					VisualSettings.HSplitTop(HeaderHeight, &Label, &VisualSettings);
					Ui()->DoLabel(&Label, Localize("Visual"), HeadlineFontSize, TEXTALIGN_ML);
					VisualSettings.HSplitTop(MarginSmall, nullptr, &VisualSettings);

					//DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClVisualTees, Localize("Visual Tees"), &g_Config.m_ClRainbowTees, &Column, LineSize);
					//DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClRainbowWeapon, TCLocalize("Visual weapons"), &g_Config.m_ClRainbowWeapon, &Column, LineSize);
					//DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClRainbowHook, TCLocalize("Visual hook"), &g_Config.m_ClRainbowHook, &Column, LineSize);
					//DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClRainbowOthers, TCLocalize("Visual others"), &g_Config.m_ClRainbowOthers, &Column, LineSize);

					// Selection
					Offset = Offset + 22.5f;
					VisualSettings.HSplitTop(MarginExtraSmall, nullptr, &VisualSettings);
					static std::vector<const char *> s_ColorDropDownNames;
					s_ColorDropDownNames = {Localize("Weapon"), Localize("Hook"), Localize("Tees"), Localize("Cursor")};
					static CUi::SDropDownState s_ColorDropDownState;
					static CScrollRegion s_ColorDropDownScrollRegion;
					s_ColorDropDownState.m_SelectionPopupContext.m_pScrollRegion = &s_ColorDropDownScrollRegion;
					int ColorSelectedOld = g_Config.m_ClVisualMenuMode - 1;
					CUIRect ColorsDropDownRect;
					VisualSettings.HSplitTop(LineSize, &ColorsDropDownRect, &VisualSettings);
					const int ColorSelectedNew = Ui()->DoDropDown(&ColorsDropDownRect, ColorSelectedOld, s_ColorDropDownNames.data(), s_ColorDropDownNames.size(), s_ColorDropDownState);
					if(ColorSelectedOld != ColorSelectedNew)
					{
						g_Config.m_ClVisualMenuMode = ColorSelectedNew + 1;
						ColorSelectedOld = ColorSelectedNew;
						dbg_msg("FeX[visual]:", "menu mode changed to %d", g_Config.m_ClVisualMenuMode);
					}
					if(g_Config.m_ClVisualMenuMode == 1)
					{
						Offset = Offset + 75.0f;
						VisualSettings.HSplitTop(HeaderHeight, &Label, &VisualSettings);
						Ui()->DoLabel(&Label, Localize("Weapon"), HeadlineFontSize, TEXTALIGN_ML);
						VisualSettings.HSplitTop(MarginExtraSmall, nullptr, &VisualSettings);
						static std::vector<const char *> s_VisualDropDownNames;
						s_VisualDropDownNames = {Localize("Rainbow"), Localize("Pulse"), Localize("Custom Color"), Localize("Random")};
						static CUi::SDropDownState s_VisualDropDownState;
						static CScrollRegion s_VisualDropDownScrollRegion;
						s_VisualDropDownState.m_SelectionPopupContext.m_pScrollRegion = &s_VisualDropDownScrollRegion;
						int VisualSelectedOld = g_Config.m_ClVisualModeW - 1;
						CUIRect VisualDropDownRect;
						VisualSettings.HSplitTop(LineSize, &VisualDropDownRect, &VisualSettings);
						const int VisualSelectedNew = Ui()->DoDropDown(&VisualDropDownRect, VisualSelectedOld, s_VisualDropDownNames.data(), s_VisualDropDownNames.size(), s_VisualDropDownState);
						if(VisualSelectedOld != VisualSelectedNew)
						{
							g_Config.m_ClVisualModeW = VisualSelectedNew + 1;
							VisualSelectedOld = VisualSelectedNew;
							dbg_msg("FeX[visual]:", "visual mode[weapons] changed to %d", g_Config.m_ClVisualModeW);
						}
						DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClVisualWeapon, Localize("Visual Weapon"), &g_Config.m_ClVisualWeapon, &VisualSettings, LineSize);
						DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClVisualWeaponOthers, Localize("Visual Weapon Others"), &g_Config.m_ClVisualWeaponOthers, &VisualSettings, LineSize);

						if(g_Config.m_ClVisualModeW == 3)
						{
							Offset = Offset + 29.0f;
							VisualSettings.HSplitTop(MarginExtraSmall, nullptr, &VisualSettings);
							VisualSettings.HSplitTop(LineSize, &Button, &VisualSettings);
							static CButtonContainer CustomColor;

							DoLine_ColorPicker(&CustomColor, ColorPickerLineSize, ColorPickerLabelSize, ColorPickerLineSpacing, &VisualSettings, Localize("Weapon color"), &g_Config.m_ClVisualCusColor1, ColorRGBA(0.0f, 0.0f, 0.0f), false);
						}
					}
					else if(g_Config.m_ClVisualMenuMode == 2)
					{
						Offset = Offset + 75.0f;
						VisualSettings.HSplitTop(HeaderHeight, &Label, &VisualSettings);
						Ui()->DoLabel(&Label, Localize("Hook"), HeadlineFontSize, TEXTALIGN_ML);
						VisualSettings.HSplitTop(MarginExtraSmall, nullptr, &VisualSettings);
						static std::vector<const char *> s_VisualDropDownNames;
						s_VisualDropDownNames = {Localize("Rainbow"), Localize("Pulse"), Localize("Custom Color"), Localize("Random")};
						static CUi::SDropDownState s_VisualDropDownState;
						static CScrollRegion s_VisualDropDownScrollRegion;
						s_VisualDropDownState.m_SelectionPopupContext.m_pScrollRegion = &s_VisualDropDownScrollRegion;
						int VisualSelectedOld = g_Config.m_ClVisualModeH - 1;
						CUIRect VisualDropDownRect;
						VisualSettings.HSplitTop(LineSize, &VisualDropDownRect, &VisualSettings);
						const int VisualSelectedNew = Ui()->DoDropDown(&VisualDropDownRect, VisualSelectedOld, s_VisualDropDownNames.data(), s_VisualDropDownNames.size(), s_VisualDropDownState);
						if(VisualSelectedOld != VisualSelectedNew)
						{
							g_Config.m_ClVisualModeH = VisualSelectedNew + 1;
							VisualSelectedOld = VisualSelectedNew;
							dbg_msg("FeX[visual]:", "visual mode[hook] changed to %d", g_Config.m_ClVisualModeH);
						}
						DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClVisualHook, Localize("Visual Hook"), &g_Config.m_ClVisualHook, &VisualSettings, LineSize);
						DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClVisualHookOthers, Localize("Visual Hook Others"), &g_Config.m_ClVisualHookOthers, &VisualSettings, LineSize);
						if(g_Config.m_ClVisualModeH == 3)
						{
							Offset = Offset + 29.0f;
							VisualSettings.HSplitTop(MarginExtraSmall, nullptr, &VisualSettings);
							VisualSettings.HSplitTop(LineSize, &Button, &VisualSettings);
							static CButtonContainer CustomColor;

							DoLine_ColorPicker(&CustomColor, ColorPickerLineSize, ColorPickerLabelSize, ColorPickerLineSpacing, &VisualSettings, Localize("Hook color"), &g_Config.m_ClVisualCusColor2, ColorRGBA(0.0f, 0.0f, 0.0f), false);
						}
					}
					else if(g_Config.m_ClVisualMenuMode == 3)
					{
						Offset = Offset + 75.0f;
						VisualSettings.HSplitTop(HeaderHeight, &Label, &VisualSettings);
						Ui()->DoLabel(&Label, Localize("Tees"), HeadlineFontSize, TEXTALIGN_ML);
						VisualSettings.HSplitTop(MarginExtraSmall, nullptr, &VisualSettings);
						static std::vector<const char *> s_VisualDropDownNames;
						s_VisualDropDownNames = {Localize("Rainbow"), Localize("Pulse"), Localize("Custom Color"), Localize("Random")};
						static CUi::SDropDownState s_VisualDropDownState;
						static CScrollRegion s_VisualDropDownScrollRegion;
						s_VisualDropDownState.m_SelectionPopupContext.m_pScrollRegion = &s_VisualDropDownScrollRegion;
						int VisualSelectedOld = g_Config.m_ClVisualModeT - 1;
						CUIRect VisualDropDownRect;
						VisualSettings.HSplitTop(LineSize, &VisualDropDownRect, &VisualSettings);
						const int VisualSelectedNew = Ui()->DoDropDown(&VisualDropDownRect, VisualSelectedOld, s_VisualDropDownNames.data(), s_VisualDropDownNames.size(), s_VisualDropDownState);
						if(VisualSelectedOld != VisualSelectedNew)
						{
							g_Config.m_ClVisualModeT = VisualSelectedNew + 1;
							VisualSelectedOld = VisualSelectedNew;
							dbg_msg("FeX[visual]:", "visual mode[Tee] changed to %d", g_Config.m_ClVisualModeT);
						}
						DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClVisualTees, Localize("Visual Tees"), &g_Config.m_ClVisualTees, &VisualSettings, LineSize);
						DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClVisualTeesOthers, Localize("Visual Tees Others"), &g_Config.m_ClVisualTeesOthers, &VisualSettings, LineSize);
						if(g_Config.m_ClVisualModeT == 3)
						{
							Offset = Offset + 29.0f;
							VisualSettings.HSplitTop(MarginExtraSmall, nullptr, &VisualSettings);
							VisualSettings.HSplitTop(LineSize, &Button, &VisualSettings);
							static CButtonContainer CustomColor;

							DoLine_ColorPicker(&CustomColor, ColorPickerLineSize, ColorPickerLabelSize, ColorPickerLineSpacing, &VisualSettings, Localize("Tee color"), &g_Config.m_ClVisualCusColor3, ColorRGBA(0.0f, 0.0f, 0.0f), false);
						}
					}
					else if(g_Config.m_ClVisualMenuMode == 4)
					{
						Offset = Offset + 75.0f;
						VisualSettings.HSplitTop(HeaderHeight, &Label, &VisualSettings);
						Ui()->DoLabel(&Label, Localize("Cursor"), HeadlineFontSize, TEXTALIGN_ML);
						VisualSettings.HSplitTop(MarginExtraSmall, nullptr, &VisualSettings);
						static std::vector<const char *> s_VisualDropDownNames;
						s_VisualDropDownNames = {Localize("Rainbow"), Localize("Pulse"), Localize("Custom Color"), Localize("Random")};
						static CUi::SDropDownState s_VisualDropDownState;
						static CScrollRegion s_VisualDropDownScrollRegion;
						s_VisualDropDownState.m_SelectionPopupContext.m_pScrollRegion = &s_VisualDropDownScrollRegion;
						int VisualSelectedOld = g_Config.m_ClVisualModeC - 1;
						CUIRect VisualDropDownRect;
						VisualSettings.HSplitTop(LineSize, &VisualDropDownRect, &VisualSettings);
						const int VisualSelectedNew = Ui()->DoDropDown(&VisualDropDownRect, VisualSelectedOld, s_VisualDropDownNames.data(), s_VisualDropDownNames.size(), s_VisualDropDownState);
						if(VisualSelectedOld != VisualSelectedNew)
						{
							g_Config.m_ClVisualModeC = VisualSelectedNew + 1;
							VisualSelectedOld = VisualSelectedNew;
							dbg_msg("FeX[visual]:", "visual mode[Cursor] changed to %d", g_Config.m_ClVisualModeC);
						}
						DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClVisualCursor, Localize("Visual Cursor"), &g_Config.m_ClVisualCursor, &VisualSettings, LineSize);
						DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClVisualCursorSpec, Localize("Visual Cursor Spectators"), &g_Config.m_ClVisualCursorSpec, &VisualSettings, LineSize);
						if(g_Config.m_ClVisualModeC == 3)
						{
							Offset = Offset + 29.0f;
							VisualSettings.HSplitTop(LineSize, &Button, &VisualSettings);
							static CButtonContainer CustomColor;

							DoLine_ColorPicker(&CustomColor, ColorPickerLineSize, ColorPickerLabelSize, ColorPickerLineSpacing, &VisualSettings, Localize("Cursor color"), &g_Config.m_ClVisualCusColor2, ColorRGBA(0.0f, 0.0f, 0.0f), false);
						}
					}
					VisualSettings.HSplitTop(MarginExtraSmall, nullptr, &VisualSettings);
					VisualSettings.HSplitTop(LineSize, &Button, &VisualSettings);
					Ui()->DoScrollbarOption(&g_Config.m_ClVisualSpeed, &g_Config.m_ClVisualSpeed, &Button, Localize("Visual: Pulse, Rainbow, Random speed"), 0, 5000, &CUi::ms_LogarithmicScrollbarScale, 0, "%");
					VisualSettings.HSplitTop(MarginExtraSmall, nullptr, &VisualSettings);
					VisualSettings.HSplitTop(MarginSmall, nullptr, &VisualSettings);
				}
			}

			PlayerIndicatorSettings.HSplitTop(10.0f, nullptr, &PlayerIndicatorSettings);
			PlayerIndicatorSettings.HSplitTop(375.0f, &PlayerIndicatorSettings, nullptr);
			if(s_ScrollRegion.AddRect(PlayerIndicatorSettings))
			{
				PlayerIndicatorSettings.Draw(ColorRGBA(1,1,1,0.25f), IGraphics::CORNER_ALL, 5.0f);
				PlayerIndicatorSettings.Margin(Margin, &PlayerIndicatorSettings);

				PlayerIndicatorSettings.HSplitTop(HeaderHeight, &Button, &PlayerIndicatorSettings);
				Ui()->DoLabel(&Button, Localize("Player Indicator"), 20.0f, TEXTALIGN_ML);
				{
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClPlayerIndicator, ("Enable Player Indicators"), &g_Config.m_ClPlayerIndicator, &PlayerIndicatorSettings, LineSize);
					PlayerIndicatorSettings.HSplitTop(5.0f, &Button, &PlayerIndicatorSettings);
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClIndicatorHideOnScreen, Localize("Hide indicator for tees on your screen"), &g_Config.m_ClIndicatorHideOnScreen, &PlayerIndicatorSettings, LineSize);
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClPlayerIndicatorFreeze, Localize("Show only freeze Players"), &g_Config.m_ClPlayerIndicatorFreeze, &PlayerIndicatorSettings, LineSize);
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClIndicatorTeamOnly, Localize("Only show after joining a team"), &g_Config.m_ClIndicatorTeamOnly, &PlayerIndicatorSettings, LineSize);
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClIndicatorTees, Localize("Render tiny tees instead of circles"), &g_Config.m_ClIndicatorTees, &PlayerIndicatorSettings, LineSize);
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClWarListIndicator, Localize("Use warlist groups for indicator"), &g_Config.m_ClWarListIndicator, &PlayerIndicatorSettings, LineSize);
		
					PlayerIndicatorSettings.HSplitTop(LineSize, &Button, &PlayerIndicatorSettings);
					Ui()->DoScrollbarOption(&g_Config.m_ClIndicatorRadius, &g_Config.m_ClIndicatorRadius, &Button, Localize("Indicator size"), 1, 16);
					PlayerIndicatorSettings.HSplitTop(LineSize, &Button, &PlayerIndicatorSettings);
					Ui()->DoScrollbarOption(&g_Config.m_ClIndicatorOpacity, &g_Config.m_ClIndicatorOpacity, &Button, Localize("Indicator opacity"), 0, 100);
					DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClIndicatorVariableDistance, Localize("Change indicator offset based on distance to other tees"), &g_Config.m_ClIndicatorVariableDistance, &PlayerIndicatorSettings, LineSize);

					if(g_Config.m_ClIndicatorVariableDistance)
					{
						PlayerIndicatorSettings.HSplitTop(LineSize, &Button, &PlayerIndicatorSettings);
						Ui()->DoScrollbarOption(&g_Config.m_ClIndicatorOffset, &g_Config.m_ClIndicatorOffset, &Button, Localize("Indicator min offset"), 16, 200);
						PlayerIndicatorSettings.HSplitTop(LineSize, &Button, &PlayerIndicatorSettings);
						Ui()->DoScrollbarOption(&g_Config.m_ClIndicatorOffsetMax, &g_Config.m_ClIndicatorOffsetMax, &Button, Localize("Indicator max offset"), 16, 200);
						PlayerIndicatorSettings.HSplitTop(LineSize, &Button, &PlayerIndicatorSettings);
						Ui()->DoScrollbarOption(&g_Config.m_ClIndicatorMaxDistance, &g_Config.m_ClIndicatorMaxDistance, &Button, Localize("Indicator max distance"), 500, 7000);
					}
					else
					{
						PlayerIndicatorSettings.HSplitTop(LineSize, &Button, &PlayerIndicatorSettings);
						Ui()->DoScrollbarOption(&g_Config.m_ClIndicatorOffset, &g_Config.m_ClIndicatorOffset, &Button, Localize("Indicator offset"), 16, 200);
						PlayerIndicatorSettings.HSplitTop(LineSize * 2, nullptr, &PlayerIndicatorSettings);
					}
					if(g_Config.m_ClWarListIndicator)
					{
						char aBuf[128];
						DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClWarListIndicatorAll, Localize("Show all warlist groups"), &g_Config.m_ClWarListIndicatorAll, &PlayerIndicatorSettings, LineSize);
						str_format(aBuf, sizeof(aBuf), "Show %s group", GameClient()->m_WarList.m_WarTypes.at(1)->m_aWarName);
						DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClWarListIndicatorEnemy, aBuf, &g_Config.m_ClWarListIndicatorEnemy, &PlayerIndicatorSettings, LineSize);
						str_format(aBuf, sizeof(aBuf), "Show %s group", GameClient()->m_WarList.m_WarTypes.at(2)->m_aWarName);
						DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClWarListIndicatorTeam, aBuf, &g_Config.m_ClWarListIndicatorTeam, &PlayerIndicatorSettings, LineSize);
					}
					else
					{
						static CButtonContainer IndicatorAliveColorID, IndicatorDeadColorID, IndicatorSavedColorID;
						DoLine_ColorPicker(&IndicatorAliveColorID, ColorPickerLineSize, ColorPickerLabelSize, ColorPickerLineSpacing, &PlayerIndicatorSettings, Localize("Indicator alive color"), &g_Config.m_ClIndicatorAlive, ColorRGBA(0.0f, 0.0f, 0.0f), false);
						DoLine_ColorPicker(&IndicatorDeadColorID, ColorPickerLineSize, ColorPickerLabelSize, ColorPickerLineSpacing, &PlayerIndicatorSettings, Localize("Indicator in freeze color"), &g_Config.m_ClIndicatorFreeze, ColorRGBA(0.0f, 0.0f, 0.0f), false);
						DoLine_ColorPicker(&IndicatorSavedColorID, ColorPickerLineSize, ColorPickerLabelSize, ColorPickerLineSpacing, &PlayerIndicatorSettings, Localize("Indicator safe color"), &g_Config.m_ClIndicatorSaved, ColorRGBA(0.0f, 0.0f, 0.0f), false);
					}
				}
			}
		}

		s_ScrollRegion.End();
	}

	if(s_CurTab == FEX_TAB_WARLIST) // Wars Tab
	{
		g_Config.m_ClMenuTab = 3;
		RenderSettingsWarList(MainView);
	}

	if(s_CurTab == FEX_TAB_BINDWHEEL)
	{
		g_Config.m_ClMenuTab = 4;
		RenderSettingsBindWheel(MainView);
	}

	if(s_CurTab == FEX_TAB_STATUSBAR) // Status Bar tab
	{
		g_Config.m_ClMenuTab = 5;
		RenderSettingsStatusBar(MainView);
	}
	
}

void CMenus::RenderSettingsProfiles(CUIRect MainView)
{
	CUIRect Label, LabelMid, Section, LabelRight;
	static int s_SelectedProfile = -1;

	char *pSkinName = g_Config.m_ClPlayerSkin;
	int *pUseCustomColor = &g_Config.m_ClPlayerUseCustomColor;
	unsigned *pColorBody = &g_Config.m_ClPlayerColorBody;
	unsigned *pColorFeet = &g_Config.m_ClPlayerColorFeet;
	int CurrentFlag = m_Dummy ? g_Config.m_ClDummyCountry : g_Config.m_PlayerCountry;

	if(m_Dummy)
	{
		pSkinName = g_Config.m_ClDummySkin;
		pUseCustomColor = &g_Config.m_ClDummyUseCustomColor;
		pColorBody = &g_Config.m_ClDummyColorBody;
		pColorFeet = &g_Config.m_ClDummyColorFeet;
	}

	// skin info
	CTeeRenderInfo OwnSkinInfo;
	const CSkin *pSkin = m_pClient->m_Skins.Find(pSkinName);
	OwnSkinInfo.m_OriginalRenderSkin = pSkin->m_OriginalSkin;
	OwnSkinInfo.m_ColorableRenderSkin = pSkin->m_ColorableSkin;
	OwnSkinInfo.m_SkinMetrics = pSkin->m_Metrics;
	OwnSkinInfo.m_CustomColoredSkin = *pUseCustomColor;
	if(*pUseCustomColor)
	{
		OwnSkinInfo.m_ColorBody = color_cast<ColorRGBA>(ColorHSLA(*pColorBody).UnclampLighting(ColorHSLA::DARKEST_LGT));
		OwnSkinInfo.m_ColorFeet = color_cast<ColorRGBA>(ColorHSLA(*pColorFeet).UnclampLighting(ColorHSLA::DARKEST_LGT));
	}
	else
	{
		OwnSkinInfo.m_ColorBody = ColorRGBA(1.0f, 1.0f, 1.0f);
		OwnSkinInfo.m_ColorFeet = ColorRGBA(1.0f, 1.0f, 1.0f);
	}
	OwnSkinInfo.m_Size = 50.0f;

	//======YOUR PROFILE======
	char aTempBuf[256];
	str_format(aTempBuf, sizeof(aTempBuf), "%s:", Localize("Your profile"));
	MainView.HSplitTop(LineSize, &Label, &MainView);
	Ui()->DoLabel(&Label, aTempBuf, FontSize, TEXTALIGN_ML);
	MainView.HSplitTop(MarginSmall, nullptr, &MainView);

	MainView.HSplitTop(50.0f, &Label, &MainView);
	Label.VSplitLeft(250.0f, &Label, &LabelMid);
	const CAnimState *pIdleState = CAnimState::GetIdle();
	vec2 OffsetToMid;
	CRenderTools::GetRenderTeeOffsetToRenderedTee(pIdleState, &OwnSkinInfo, OffsetToMid);
	vec2 TeeRenderPos(Label.x + LineSize, Label.y + Label.h / 2.0f + OffsetToMid.y);
	int Emote = m_Dummy ? g_Config.m_ClDummyDefaultEyes : g_Config.m_ClPlayerDefaultEyes;
	RenderTools()->RenderTee(pIdleState, &OwnSkinInfo, Emote, vec2(1.0f, 0.0f), TeeRenderPos);

	char aName[64];
	char aClan[64];
	str_format(aName, sizeof(aName), "%s", m_Dummy ? g_Config.m_ClDummyName : g_Config.m_PlayerName);
	str_format(aClan, sizeof(aClan), "%s", m_Dummy ? g_Config.m_ClDummyClan : g_Config.m_PlayerClan);

	CUIRect FlagRect;
	Label.VSplitLeft(90.0f, &FlagRect, &Label);

	Label.HSplitTop(LineSize, &Section, &Label);
	str_format(aTempBuf, sizeof(aTempBuf), Localize("Name: %s"), aName);
	Ui()->DoLabel(&Section, aTempBuf, FontSize, TEXTALIGN_ML);

	Label.HSplitTop(LineSize, &Section, &Label);
	str_format(aTempBuf, sizeof(aTempBuf), Localize("Clan: %s"), aClan);
	Ui()->DoLabel(&Section, aTempBuf, FontSize, TEXTALIGN_ML);

	Label.HSplitTop(LineSize, &Section, &Label);
	str_format(aTempBuf, sizeof(aTempBuf), Localize("Skin: %s"), pSkinName);
	Ui()->DoLabel(&Section, aTempBuf, FontSize, TEXTALIGN_ML);

	FlagRect.VSplitRight(50.0f, nullptr, &FlagRect);
	FlagRect.HSplitBottom(25.0f, nullptr, &FlagRect);
	FlagRect.y -= 10.0f;
	ColorRGBA Color(1.0f, 1.0f, 1.0f, 1.0f);
	m_pClient->m_CountryFlags.Render(m_Dummy ? g_Config.m_ClDummyCountry : g_Config.m_PlayerCountry, Color, FlagRect.x, FlagRect.y, FlagRect.w, FlagRect.h);

	bool DoSkin = g_Config.m_ClApplyProfileSkin;
	bool DoColors = g_Config.m_ClApplyProfileColors;
	bool DoEmote = g_Config.m_ClApplyProfileEmote;
	bool DoName = g_Config.m_ClApplyProfileName;
	bool DoClan = g_Config.m_ClApplyProfileClan;
	bool DoFlag = g_Config.m_ClApplyProfileFlag;

	//======AFTER LOAD======
	if(s_SelectedProfile != -1 && s_SelectedProfile < (int)GameClient()->m_SkinProfiles.m_Profiles.size())
	{
		CProfile LoadProfile = GameClient()->m_SkinProfiles.m_Profiles[s_SelectedProfile];
		MainView.HSplitTop(LineSize, nullptr, &MainView);
		MainView.HSplitTop(10.0f, &Label, &MainView);
		str_format(aTempBuf, sizeof(aTempBuf), "%s:", Localize("After Load"));
		Ui()->DoLabel(&Label, aTempBuf, FontSize, TEXTALIGN_ML);

		MainView.HSplitTop(50.0f, &Label, &MainView);
		Label.VSplitLeft(250.0f, &Label, nullptr);

		if(DoSkin && strlen(LoadProfile.SkinName) != 0)
		{
			const CSkin *pLoadSkin = m_pClient->m_Skins.Find(LoadProfile.SkinName);
			OwnSkinInfo.m_OriginalRenderSkin = pLoadSkin->m_OriginalSkin;
			OwnSkinInfo.m_ColorableRenderSkin = pLoadSkin->m_ColorableSkin;
			OwnSkinInfo.m_SkinMetrics = pLoadSkin->m_Metrics;
		}
		if(*pUseCustomColor && DoColors && LoadProfile.BodyColor != -1 && LoadProfile.FeetColor != -1)
		{
			OwnSkinInfo.m_ColorBody = color_cast<ColorRGBA>(ColorHSLA(LoadProfile.BodyColor).UnclampLighting(ColorHSLA::DARKEST_LGT));
			OwnSkinInfo.m_ColorFeet = color_cast<ColorRGBA>(ColorHSLA(LoadProfile.FeetColor).UnclampLighting(ColorHSLA::DARKEST_LGT));
		}

		CRenderTools::GetRenderTeeOffsetToRenderedTee(pIdleState, &OwnSkinInfo, OffsetToMid);
		TeeRenderPos = vec2(Label.x + LineSize, Label.y + Label.h / 2.0f + OffsetToMid.y);
		int LoadEmote = Emote;
		if(DoEmote && LoadProfile.Emote != -1)
			LoadEmote = LoadProfile.Emote;
		RenderTools()->RenderTee(pIdleState, &OwnSkinInfo, LoadEmote, vec2(1.0f, 0.0f), TeeRenderPos);

		if(DoName && strlen(LoadProfile.Name) != 0)
			str_format(aName, sizeof(aName), "%s", LoadProfile.Name);
		if(DoClan && strlen(LoadProfile.Clan) != 0)
			str_format(aClan, sizeof(aClan), "%s", LoadProfile.Clan);

		Label.VSplitLeft(90.0f, &FlagRect, &Label);

		Label.HSplitTop(LineSize, &Section, &Label);
		str_format(aTempBuf, sizeof(aTempBuf), Localize("Name: %s"), aName);
		Ui()->DoLabel(&Section, aTempBuf, FontSize, TEXTALIGN_ML);

		Label.HSplitTop(LineSize, &Section, &Label);
		str_format(aTempBuf, sizeof(aTempBuf), Localize("Clan: %s"), aClan);
		Ui()->DoLabel(&Section, aTempBuf, FontSize, TEXTALIGN_ML);

		Label.HSplitTop(LineSize, &Section, &Label);
		str_format(aTempBuf, sizeof(aTempBuf), Localize("Skin: %s"), (DoSkin && strlen(LoadProfile.SkinName) != 0) ? LoadProfile.SkinName : pSkinName);
		Ui()->DoLabel(&Section, aTempBuf, FontSize, TEXTALIGN_ML);

		FlagRect.VSplitRight(50.0f, nullptr, &FlagRect);
		FlagRect.HSplitBottom(25.0f, nullptr, &FlagRect);
		FlagRect.y -= 10.0f;
		int RenderFlag = m_Dummy ? g_Config.m_ClDummyCountry : g_Config.m_PlayerCountry;
		if(DoFlag && LoadProfile.CountryFlag != -2)
			RenderFlag = LoadProfile.CountryFlag;
		m_pClient->m_CountryFlags.Render(RenderFlag, Color, FlagRect.x, FlagRect.y, FlagRect.w, FlagRect.h);

		str_format(aName, sizeof(aName), "%s", m_Dummy ? g_Config.m_ClDummyName : g_Config.m_PlayerName);
		str_format(aClan, sizeof(aClan), "%s", m_Dummy ? g_Config.m_ClDummyClan : g_Config.m_PlayerClan);
	}
	else
	{
		MainView.HSplitTop(80.0f, nullptr, &MainView);
	}

	//===BUTTONS AND CHECK BOX===
	CUIRect DummyCheck, CustomCheck;
	MainView.HSplitTop(30.0f, &DummyCheck, nullptr);
	DummyCheck.HSplitTop(13.0f, nullptr, &DummyCheck);

	DummyCheck.VSplitLeft(100.0f, &DummyCheck, &CustomCheck);
	CustomCheck.VSplitLeft(150.0f, &CustomCheck, nullptr);

	DoButton_CheckBoxAutoVMarginAndSet(&m_Dummy, Localize("Dummy"), (int *)&m_Dummy, &DummyCheck, LineSize);

	static int s_CustomColorID = 0;
	CustomCheck.HSplitTop(LineSize, &CustomCheck, nullptr);

	if(DoButton_CheckBox(&s_CustomColorID, Localize("Custom colors"), *pUseCustomColor, &CustomCheck))
	{
		*pUseCustomColor = *pUseCustomColor ? 0 : 1;
		SetNeedSendInfo();
	}

	LabelMid.VSplitLeft(20.0f, nullptr, &LabelMid);
	LabelMid.VSplitLeft(160.0f, &LabelMid, &LabelRight);

	DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClApplyProfileSkin, Localize("Save/Load Skin"), &g_Config.m_ClApplyProfileSkin, &LabelMid, LineSize);
	DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClApplyProfileColors, Localize("Save/Load Colors"), &g_Config.m_ClApplyProfileColors, &LabelMid, LineSize);
	DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClApplyProfileEmote, Localize("Save/Load Emote"), &g_Config.m_ClApplyProfileEmote, &LabelMid, LineSize);
	DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClApplyProfileName, Localize("Save/Load Name"), &g_Config.m_ClApplyProfileName, &LabelMid, LineSize);
	DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClApplyProfileClan, Localize("Save/Load Clan"), &g_Config.m_ClApplyProfileClan, &LabelMid, LineSize);
	DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClApplyProfileFlag, Localize("Save/Load Flag"), &g_Config.m_ClApplyProfileFlag, &LabelMid, LineSize);

	CUIRect Button;
	LabelRight.VSplitLeft(150.0f, &LabelRight, nullptr);

	LabelRight.HSplitTop(30.0f, &Button, &LabelRight);
	static CButtonContainer s_LoadButton;

	if(DoButton_Menu(&s_LoadButton, Localize("Load"), 0, &Button))
	{
		if(s_SelectedProfile != -1 && s_SelectedProfile < (int)GameClient()->m_SkinProfiles.m_Profiles.size())
		{
			CProfile LoadProfile = GameClient()->m_SkinProfiles.m_Profiles[s_SelectedProfile];
			if(!m_Dummy)
			{
				if(DoSkin && strlen(LoadProfile.SkinName) != 0)
					str_copy(g_Config.m_ClPlayerSkin, LoadProfile.SkinName, sizeof(g_Config.m_ClPlayerSkin));
				if(DoColors && LoadProfile.BodyColor != -1 && LoadProfile.FeetColor != -1)
				{
					g_Config.m_ClPlayerColorBody = LoadProfile.BodyColor;
					g_Config.m_ClPlayerColorFeet = LoadProfile.FeetColor;
				}
				if(DoEmote && LoadProfile.Emote != -1)
					g_Config.m_ClPlayerDefaultEyes = LoadProfile.Emote;
				if(DoName && strlen(LoadProfile.Name) != 0)
					str_copy(g_Config.m_PlayerName, LoadProfile.Name, sizeof(g_Config.m_PlayerName));
				if(DoClan && strlen(LoadProfile.Clan) != 0)
					str_copy(g_Config.m_PlayerClan, LoadProfile.Clan, sizeof(g_Config.m_PlayerClan));
				if(DoFlag && LoadProfile.CountryFlag != -2)
					g_Config.m_PlayerCountry = LoadProfile.CountryFlag;
			}
			else
			{
				if(DoSkin && strlen(LoadProfile.SkinName) != 0)
					str_copy(g_Config.m_ClDummySkin, LoadProfile.SkinName, sizeof(g_Config.m_ClDummySkin));
				if(DoColors && LoadProfile.BodyColor != -1 && LoadProfile.FeetColor != -1)
				{
					g_Config.m_ClDummyColorBody = LoadProfile.BodyColor;
					g_Config.m_ClDummyColorFeet = LoadProfile.FeetColor;
				}
				if(DoEmote && LoadProfile.Emote != -1)
					g_Config.m_ClDummyDefaultEyes = LoadProfile.Emote;
				if(DoName && strlen(LoadProfile.Name) != 0)
					str_copy(g_Config.m_ClDummyName, LoadProfile.Name, sizeof(g_Config.m_ClDummyName));
				if(DoClan && strlen(LoadProfile.Clan) != 0)
					str_copy(g_Config.m_ClDummyClan, LoadProfile.Clan, sizeof(g_Config.m_ClDummyClan));
				if(DoFlag && LoadProfile.CountryFlag != -2)
					g_Config.m_ClDummyCountry = LoadProfile.CountryFlag;
			}
		}
		SetNeedSendInfo();
	}
	LabelRight.HSplitTop(5.0f, nullptr, &LabelRight);

	LabelRight.HSplitTop(30.0f, &Button, &LabelRight);
	static CButtonContainer s_SaveButton;
	if(DoButton_Menu(&s_SaveButton, Localize("Save"), 0, &Button))
	{
		GameClient()->m_SkinProfiles.AddProfile(
			DoColors ? *pColorBody : -1,
			DoColors ? *pColorFeet : -1,
			DoFlag ? CurrentFlag : -2,
			DoEmote ? Emote : -1,
			DoSkin ? pSkinName : "",
			DoName ? aName : "",
			DoClan ? aClan : "");
		GameClient()->m_SkinProfiles.SaveProfiles();
	}
	LabelRight.HSplitTop(5.0f, nullptr, &LabelRight);

	static int s_AllowDelete;
	DoButton_CheckBoxAutoVMarginAndSet(&s_AllowDelete, Localizable("Enable Deleting"), &s_AllowDelete, &LabelRight, LineSize);
	LabelRight.HSplitTop(5.0f, nullptr, &LabelRight);

	if(s_AllowDelete)
	{
		LabelRight.HSplitTop(28.0f, &Button, &LabelRight);
		static CButtonContainer s_DeleteButton;
		if(DoButton_Menu(&s_DeleteButton, Localize("Delete"), 0, &Button))
		{
			if(s_SelectedProfile != -1 && s_SelectedProfile < (int)GameClient()->m_SkinProfiles.m_Profiles.size())
			{
				GameClient()->m_SkinProfiles.m_Profiles.erase(GameClient()->m_SkinProfiles.m_Profiles.begin() + s_SelectedProfile);
				GameClient()->m_SkinProfiles.SaveProfiles();
			}
		}
		LabelRight.HSplitTop(5.0f, nullptr, &LabelRight);

		LabelRight.HSplitTop(28.0f, &Button, &LabelRight);
		static CButtonContainer s_OverrideButton;
		if(DoButton_Menu(&s_OverrideButton, Localize("Override"), 0, &Button))
		{
			if(s_SelectedProfile != -1 && s_SelectedProfile < (int)GameClient()->m_SkinProfiles.m_Profiles.size())
			{
				GameClient()->m_SkinProfiles.m_Profiles[s_SelectedProfile] = CProfile(
					DoColors ? *pColorBody : -1,
					DoColors ? *pColorFeet : -1,
					DoFlag ? CurrentFlag : -2,
					DoEmote ? Emote : -1,
					DoSkin ? pSkinName : "",
					DoName ? aName : "",
					DoClan ? aClan : "");
				GameClient()->m_SkinProfiles.SaveProfiles();
			}
		}
	}

	//---RENDER THE SELECTOR---
	CUIRect FileButton;
	CUIRect SelectorRect;
	MainView.HSplitTop(50.0f, nullptr, &SelectorRect);
	SelectorRect.HSplitBottom(LineSize, &SelectorRect, &FileButton);
	SelectorRect.HSplitBottom(MarginSmall, &SelectorRect, nullptr);
	std::vector<CProfile> *pProfileList = &GameClient()->m_SkinProfiles.m_Profiles;

	static CListBox s_ListBox;
	s_ListBox.DoStart(50.0f, pProfileList->size(), 4, 3, s_SelectedProfile, &SelectorRect, true);

	static bool s_Indexs[1024];

	for(size_t i = 0; i < pProfileList->size(); ++i)
	{
		CProfile CurrentProfile = GameClient()->m_SkinProfiles.m_Profiles[i];

		char RenderSkin[24];
		if(strlen(CurrentProfile.SkinName) == 0)
			str_copy(RenderSkin, pSkinName, sizeof(RenderSkin));
		else
			str_copy(RenderSkin, CurrentProfile.SkinName, sizeof(RenderSkin));

		const CSkin *pSkinToBeDraw = m_pClient->m_Skins.Find(RenderSkin);

		CListboxItem Item = s_ListBox.DoNextItem(&s_Indexs[i], s_SelectedProfile >= 0 && (size_t)s_SelectedProfile == i);

		if(!Item.m_Visible)
			continue;

		if(Item.m_Visible)
		{
			CTeeRenderInfo Info;
			Info.m_ColorBody = color_cast<ColorRGBA>(ColorHSLA(CurrentProfile.BodyColor).UnclampLighting(ColorHSLA::DARKEST_LGT));
			Info.m_ColorFeet = color_cast<ColorRGBA>(ColorHSLA(CurrentProfile.FeetColor).UnclampLighting(ColorHSLA::DARKEST_LGT));
			Info.m_CustomColoredSkin = true;
			Info.m_OriginalRenderSkin = pSkinToBeDraw->m_OriginalSkin;
			Info.m_ColorableRenderSkin = pSkinToBeDraw->m_ColorableSkin;
			Info.m_SkinMetrics = pSkinToBeDraw->m_Metrics;
			Info.m_Size = 50.0f;
			if(CurrentProfile.BodyColor == -1 && CurrentProfile.FeetColor == -1)
			{
				Info.m_CustomColoredSkin = m_Dummy ? g_Config.m_ClDummyUseCustomColor : g_Config.m_ClPlayerUseCustomColor;
				Info.m_ColorBody = ColorRGBA(1.0f, 1.0f, 1.0f);
				Info.m_ColorFeet = ColorRGBA(1.0f, 1.0f, 1.0f);
			}

			CRenderTools::GetRenderTeeOffsetToRenderedTee(pIdleState, &Info, OffsetToMid);

			int RenderEmote = CurrentProfile.Emote == -1 ? Emote : CurrentProfile.Emote;
			TeeRenderPos = vec2(Item.m_Rect.x + 30.0f, Item.m_Rect.y + Item.m_Rect.h / 2.0f + OffsetToMid.y);

			Item.m_Rect.VSplitLeft(60.0f, nullptr, &Item.m_Rect);
			CUIRect PlayerRect, ClanRect, FeetColorSquare, BodyColorSquare;

			Item.m_Rect.VSplitLeft(60.0f, nullptr, &BodyColorSquare); // Delete this maybe

			Item.m_Rect.VSplitRight(60.0f, &BodyColorSquare, &FlagRect);
			BodyColorSquare.x -= 11.0f;
			BodyColorSquare.VSplitLeft(10.0f, &BodyColorSquare, nullptr);
			BodyColorSquare.HSplitMid(&BodyColorSquare, &FeetColorSquare);
			BodyColorSquare.HSplitMid(nullptr, &BodyColorSquare);
			FeetColorSquare.HSplitMid(&FeetColorSquare, nullptr);
			FlagRect.HSplitBottom(10.0f, &FlagRect, nullptr);
			FlagRect.HSplitTop(10.0f, nullptr, &FlagRect);

			Item.m_Rect.HSplitMid(&PlayerRect, &ClanRect);

			SLabelProperties Props;
			Props.m_MaxWidth = Item.m_Rect.w;
			if(CurrentProfile.CountryFlag != -2)
				m_pClient->m_CountryFlags.Render(CurrentProfile.CountryFlag, Color, FlagRect.x, FlagRect.y, FlagRect.w, FlagRect.h);

			if(CurrentProfile.BodyColor != -1 && CurrentProfile.FeetColor != -1)
			{
				ColorRGBA BodyColor = color_cast<ColorRGBA>(ColorHSLA(CurrentProfile.BodyColor).UnclampLighting(ColorHSLA::DARKEST_LGT));
				ColorRGBA FeetColor = color_cast<ColorRGBA>(ColorHSLA(CurrentProfile.FeetColor).UnclampLighting(ColorHSLA::DARKEST_LGT));

				Graphics()->TextureClear();
				Graphics()->QuadsBegin();
				Graphics()->SetColor(BodyColor.r, BodyColor.g, BodyColor.b, 1.0f);
				IGraphics::CQuadItem Quads[2];
				Quads[0] = IGraphics::CQuadItem(BodyColorSquare.x, BodyColorSquare.y, BodyColorSquare.w, BodyColorSquare.h);
				Graphics()->QuadsDrawTL(&Quads[0], 1);
				Graphics()->SetColor(FeetColor.r, FeetColor.g, FeetColor.b, 1.0f);
				Quads[1] = IGraphics::CQuadItem(FeetColorSquare.x, FeetColorSquare.y, FeetColorSquare.w, FeetColorSquare.h);
				Graphics()->QuadsDrawTL(&Quads[1], 1);
				Graphics()->QuadsEnd();
			}
			RenderTools()->RenderTee(pIdleState, &Info, RenderEmote, vec2(1.0f, 0.0f), TeeRenderPos);

			if(strlen(CurrentProfile.Name) == 0 && strlen(CurrentProfile.Clan) == 0)
			{
				PlayerRect = Item.m_Rect;
				PlayerRect.y += MarginSmall;
				Ui()->DoLabel(&PlayerRect, CurrentProfile.SkinName, FontSize, TEXTALIGN_ML, Props);
			}
			else
			{
				Ui()->DoLabel(&PlayerRect, CurrentProfile.Name, FontSize, TEXTALIGN_ML, Props);
				Item.m_Rect.HSplitTop(LineSize, nullptr, &Item.m_Rect);
				Props.m_MaxWidth = Item.m_Rect.w;
				Ui()->DoLabel(&ClanRect, CurrentProfile.Clan, FontSize, TEXTALIGN_ML, Props);
			}
		}
	}

	const int NewSelected = s_ListBox.DoEnd();
	if(s_SelectedProfile != NewSelected)
	{
		s_SelectedProfile = NewSelected;
	}
	static CButtonContainer s_ProfilesFile;
	FileButton.VSplitLeft(130.0f, &FileButton, nullptr);
	if(DoButton_Menu(&s_ProfilesFile, Localize("Profiles file"), 0, &FileButton))
	{
		Storage()->GetCompletePath(IStorage::TYPE_SAVE, PROFILES_FILE, aTempBuf, sizeof(aTempBuf));
		Client()->ViewFile(aTempBuf);
	}
}

void CMenus::RenderChatPreview(CUIRect MainView)
{
	CChat &Chat = GameClient()->m_Chat;

	ColorRGBA SystemColor = color_cast<ColorRGBA, ColorHSLA>(ColorHSLA(g_Config.m_ClMessageSystemColor));
	ColorRGBA HighlightedColor = color_cast<ColorRGBA, ColorHSLA>(ColorHSLA(g_Config.m_ClMessageHighlightColor));
	ColorRGBA TeamColor = color_cast<ColorRGBA, ColorHSLA>(ColorHSLA(g_Config.m_ClMessageTeamColor));
	ColorRGBA FriendColor = color_cast<ColorRGBA, ColorHSLA>(ColorHSLA(g_Config.m_ClMessageFriendColor));
	ColorRGBA SpecColor = color_cast<ColorRGBA, ColorHSLA>(ColorHSLA(g_Config.m_ClSpecColor));
	ColorRGBA EnemyColor = GameClient()->m_WarList.m_WarTypes[1]->m_Color;
	ColorRGBA HelperColor = GameClient()->m_WarList.m_WarTypes[3]->m_Color;
	ColorRGBA TeammateColor = GameClient()->m_WarList.m_WarTypes[2]->m_Color;
	ColorRGBA NormalColor = color_cast<ColorRGBA, ColorHSLA>(ColorHSLA(g_Config.m_ClMessageColor));
	ColorRGBA ClientColor = color_cast<ColorRGBA, ColorHSLA>(ColorHSLA(g_Config.m_ClMessageClientColor));
	ColorRGBA DefaultNameColor(0.8f, 0.8f, 0.8f, 1.0f);

	const float RealFontSize = 10.0f;
	const float RealMsgPaddingX = 12;
	const float RealMsgPaddingY = 4;
	const float RealMsgPaddingTee = 16;
	const float RealOffsetY = RealFontSize + RealMsgPaddingY;

	const float X = RealMsgPaddingX / 2.0f + MainView.x;
	float Y = MainView.y;
	float LineWidth = g_Config.m_ClChatWidth * 2 - (RealMsgPaddingX * 1.5f) - RealMsgPaddingTee;
	char aBuf[128];

	str_copy(aBuf, Client()->PlayerName());

	const CAnimState *pIdleState = CAnimState::GetIdle();
	const float RealTeeSize = 16;
	const float RealTeeSizeHalved = 8;
	constexpr float TWSkinUnreliableOffset = -0.25f;
	const float OffsetTeeY = RealTeeSizeHalved;
	const float FullHeightMinusTee = RealOffsetY - RealTeeSize;

	struct SPreviewLine
	{
		int m_ClShowIdsChat;
		bool m_Team;
		char m_aName[64];
		char m_aText[256];
		bool m_Spec;
		bool m_Enemy;
		bool m_Helper;
		bool m_Teammate;
		bool m_Friend;
		bool m_Player;
		bool m_Client;
		bool m_Highlighted;
		int m_TimesRepeated;

		CTeeRenderInfo m_RenderInfo;
	};

	static std::vector<SPreviewLine> s_vLines;

	enum ELineFlag
	{
		FLAG_TEAM = 1 << 0,
		FLAG_FRIEND = 1 << 1,
		FLAG_HIGHLIGHT = 1 << 2,
		FLAG_CLIENT = 1 << 3,
		FLAG_ENEMY = 1 << 4,
		FLAG_HELPER = 1 << 5,
		FLAG_TEAMMATE = 1 << 6,
		FLAG_SPEC = 1 << 7
	};
	enum
	{
		PREVIEW_SYS,
		PREVIEW_HIGHLIGHT,
		PREVIEW_TEAM,
		PREVIEW_FRIEND,
		PREVIEW_SPAMMER,
		PREVIEW_ENEMY,
		PREVIEW_HELPER,
		PREVIEW_TEAMMATE,
		PREVIEW_SPEC,
		PREVIEW_CLIENT
	};
	auto &&SetPreviewLine = [](int Index, int ClientId, const char *pName, const char *pText, int Flag, int Repeats) {
		SPreviewLine *pLine;
		if((int)s_vLines.size() <= Index)
		{
			s_vLines.emplace_back();
			pLine = &s_vLines.back();
		}
		else
		{
			pLine = &s_vLines[Index];
		}
		pLine->m_ClShowIdsChat = ClientId;
		pLine->m_Team = Flag & FLAG_TEAM;
		pLine->m_Friend = Flag & FLAG_FRIEND;
		pLine->m_Player = ClientId >= 0;
		pLine->m_Highlighted = Flag & FLAG_HIGHLIGHT;
		pLine->m_Client = Flag & FLAG_CLIENT;
		pLine->m_Spec = Flag & FLAG_SPEC;
		pLine->m_Enemy = Flag & FLAG_ENEMY;
		pLine->m_Helper = Flag & FLAG_HELPER;
		pLine->m_Teammate = Flag & FLAG_TEAMMATE;
		str_copy(pLine->m_aName, pName);
		str_copy(pLine->m_aText, pText);
	};
	auto &&SetLineSkin = [RealTeeSize](int Index, const CSkin *pSkin) {
		if(Index >= (int)s_vLines.size())
			return;
		s_vLines[Index].m_RenderInfo.m_Size = RealTeeSize;
		s_vLines[Index].m_RenderInfo.Apply(pSkin);
	};

	auto &&RenderPreview = [&](int LineIndex, int x, int y, bool Render = true) {
		if(LineIndex >= (int)s_vLines.size())
			return vec2(0, 0);
		CTextCursor LocalCursor;
		TextRender()->SetCursor(&LocalCursor, x, y, RealFontSize, Render ? TEXTFLAG_RENDER : 0);
		LocalCursor.m_LineWidth = LineWidth;
		const auto &Line = s_vLines[LineIndex];

		char aClientId[16] = "";

		char aCount[12];
		if(Line.m_ClShowIdsChat < 0)
			str_format(aCount, sizeof(aCount), "[%d] ", Line.m_TimesRepeated + 1);
		else
			str_format(aCount, sizeof(aCount), " [%d]", Line.m_TimesRepeated + 1);

		if(Line.m_Player)
		{
			LocalCursor.m_X += RealMsgPaddingTee;

			if(Line.m_Enemy && g_Config.m_ClWarlistPrefixes)
			{
				if(Render)
					TextRender()->TextColor(EnemyColor);
				TextRender()->TextEx(&LocalCursor, "♦ ", -1);
			}
			if(Line.m_Helper && g_Config.m_ClWarlistPrefixes)
			{
				if(Render)
					TextRender()->TextColor(HelperColor);
				TextRender()->TextEx(&LocalCursor, "♦ ", -1);
			}
			if(Line.m_Teammate && g_Config.m_ClWarlistPrefixes)
			{
				if(Render)
					TextRender()->TextColor(TeammateColor);
				TextRender()->TextEx(&LocalCursor, "♦ ", -1);
			}
			if(Line.m_Friend && g_Config.m_ClMessageFriend)
			{
				if(Render)
					TextRender()->TextColor(FriendColor);
				TextRender()->TextEx(&LocalCursor, g_Config.m_ClFriendPrefix, -1);
			}
			if(Line.m_Spec && g_Config.m_ClSpectatePrefix)
			{
				if(Render)
					TextRender()->TextColor(SpecColor);
				TextRender()->TextEx(&LocalCursor, g_Config.m_ClSpecPrefix, -1);
			}
		}

		ColorRGBA NameColor;
		if(Line.m_Friend && g_Config.m_ClDoFriendColors)
			NameColor = FriendColor;
		else if(Line.m_Team)
			NameColor = CalculateNameColor(color_cast<ColorHSLA>(TeamColor));
		else if(Line.m_Player)
			NameColor = DefaultNameColor;
		else if(Line.m_Client)
			NameColor = ClientColor;
		else
			NameColor = SystemColor;

		if(Render)
			TextRender()->TextColor(NameColor);

		TextRender()->TextEx(&LocalCursor, aClientId);
		TextRender()->TextEx(&LocalCursor, Line.m_aName);

		if(Line.m_TimesRepeated > 0)
		{
			if(Render)
				TextRender()->TextColor(1.0f, 1.0f, 1.0f, 0.3f);
			TextRender()->TextEx(&LocalCursor, aCount, -1);
		}

		if(Line.m_ClShowIdsChat >= 0 && Line.m_aName[0] != '\0')
		{
			if(Render)
				TextRender()->TextColor(NameColor);
			TextRender()->TextEx(&LocalCursor, ": ", -1);
		}

		CTextCursor AppendCursor = LocalCursor;
		AppendCursor.m_LongestLineWidth = 0.0f;
		if(!g_Config.m_ClChatOld)
		{
			AppendCursor.m_StartX = LocalCursor.m_X;
			AppendCursor.m_LineWidth -= LocalCursor.m_LongestLineWidth;
		}

		if(Render)
		{
			if(Line.m_Highlighted)
				TextRender()->TextColor(HighlightedColor);
			else if(Line.m_Team)
				TextRender()->TextColor(TeamColor);
			else if(Line.m_Player)
				TextRender()->TextColor(NormalColor);
		}

		TextRender()->TextEx(&AppendCursor, Line.m_aText, -1);
		if(Render)
			TextRender()->TextColor(TextRender()->DefaultTextColor());

		return vec2{LocalCursor.m_LongestLineWidth + AppendCursor.m_LongestLineWidth, AppendCursor.Height() + RealMsgPaddingY};
	};

	// Set preview lines
	{
		char aLineBuilder[128];

		str_format(aLineBuilder, sizeof(aLineBuilder), "'%s' entered and joined the game", aBuf);
		if(g_Config.m_ClChatServerPrefix)
			SetPreviewLine(PREVIEW_SYS, -1, g_Config.m_ClServerPrefix, aLineBuilder, 0, 0);
		else
			SetPreviewLine(PREVIEW_SYS, -1, "*** ", aLineBuilder, 0, 0);
		str_format(aLineBuilder, sizeof(aLineBuilder), "Hey, how are you %s?", aBuf);
		SetPreviewLine(PREVIEW_HIGHLIGHT, 7, "Random Tee", aLineBuilder, FLAG_HIGHLIGHT, 0);

		SetPreviewLine(PREVIEW_TEAM, 11, "Your Teammate", "Let's speedrun this!", FLAG_TEAM, 0);
		SetPreviewLine(PREVIEW_FRIEND, 8, "Friend", "Hello there", FLAG_FRIEND, 0);
		SetPreviewLine(PREVIEW_SPAMMER, 9, "Spammer", "Hey fools, I'm spamming here!", 0, 5);
		if(g_Config.m_ClChatClientPrefix)
			SetPreviewLine(PREVIEW_CLIENT, -1, g_Config.m_ClClientPrefix, "Echo command executed", FLAG_CLIENT, 0);
		else
			SetPreviewLine(PREVIEW_CLIENT, -1, "— ", "Echo command executed", FLAG_CLIENT, 0);
		SetPreviewLine(PREVIEW_ENEMY, 6, "Enemy", "Nobo", FLAG_ENEMY, 0);
		SetPreviewLine(PREVIEW_HELPER, 3, "Helper", "Ima Help this random :>", FLAG_HELPER, 0);
		SetPreviewLine(PREVIEW_TEAMMATE, 10, "Teammate", "Help me There's too many!", FLAG_TEAMMATE, 0);
		SetPreviewLine(PREVIEW_SPEC, 11, "Random Spectator", "Crazy Gameplay dude", FLAG_SPEC, 0);
	}

	SetLineSkin(1, GameClient()->m_Skins.Find("pinky"));
	SetLineSkin(2, GameClient()->m_Skins.Find("default_flower"));
	SetLineSkin(3, GameClient()->m_Skins.Find("cammostripes"));
	SetLineSkin(4, GameClient()->m_Skins.Find("beast"));
	SetLineSkin(5, GameClient()->m_Skins.Find("default"));
	SetLineSkin(6, GameClient()->m_Skins.Find("Robot"));
	SetLineSkin(7, GameClient()->m_Skins.Find("Catnoa"));
	SetLineSkin(8, GameClient()->m_Skins.Find("turtle"));

	// Backgrounds first
	if(!g_Config.m_ClChatOld)
	{
		Graphics()->TextureClear();
		Graphics()->QuadsBegin();
		Graphics()->SetColor(0, 0, 0, 0.12f);

		float TempY = Y;
		const float RealBackgroundRounding = Chat.MessageRounding() * 2.0f;

		auto &&RenderMessageBackground = [&](int LineIndex) {
			auto Size = RenderPreview(LineIndex, 0, 0, false);
			Graphics()->DrawRectExt(X - RealMsgPaddingX / 2.0f, TempY - RealMsgPaddingY / 2.0f, Size.x + RealMsgPaddingX * 1.5f, Size.y, RealBackgroundRounding, IGraphics::CORNER_ALL);
			return Size.y;
		};

		if(g_Config.m_ClShowChatSystem)
		{
			TempY += RenderMessageBackground(PREVIEW_SYS);
		}

		if(!g_Config.m_ClShowChatFriends)
		{
			if(!g_Config.m_ClShowChatTeamMembersOnly)
				TempY += RenderMessageBackground(PREVIEW_HIGHLIGHT);
			TempY += RenderMessageBackground(PREVIEW_TEAM);
		}

		if(!g_Config.m_ClShowChatTeamMembersOnly)
			TempY += RenderMessageBackground(PREVIEW_FRIEND);

		if(!g_Config.m_ClShowChatFriends && !g_Config.m_ClShowChatTeamMembersOnly)
		{
			TempY += RenderMessageBackground(PREVIEW_SPAMMER);
		}

		TempY += RenderMessageBackground(PREVIEW_ENEMY);
		TempY += RenderMessageBackground(PREVIEW_HELPER);
		TempY += RenderMessageBackground(PREVIEW_TEAMMATE);
		TempY += RenderMessageBackground(PREVIEW_SPEC);

		TempY += RenderMessageBackground(PREVIEW_CLIENT);

		Graphics()->QuadsEnd();
	}

	// System
	if(g_Config.m_ClShowChatSystem)
	{
		Y += RenderPreview(PREVIEW_SYS, X, Y).y;
	}

	if(!g_Config.m_ClShowChatFriends)
	{
		// Highlighted
		if(!g_Config.m_ClChatOld && !g_Config.m_ClShowChatTeamMembersOnly)
			RenderTools()->RenderTee(pIdleState, &s_vLines[PREVIEW_HIGHLIGHT].m_RenderInfo, EMOTE_NORMAL, vec2(1, 0.1f), vec2(X + RealTeeSizeHalved, Y + OffsetTeeY + FullHeightMinusTee / 2.0f + TWSkinUnreliableOffset));
		if(!g_Config.m_ClShowChatTeamMembersOnly)
			Y += RenderPreview(PREVIEW_HIGHLIGHT, X, Y).y;

		// Team
		if(!g_Config.m_ClChatOld)
			RenderTools()->RenderTee(pIdleState, &s_vLines[PREVIEW_TEAM].m_RenderInfo, EMOTE_NORMAL, vec2(1, 0.1f), vec2(X + RealTeeSizeHalved, Y + OffsetTeeY + FullHeightMinusTee / 2.0f + TWSkinUnreliableOffset));
		Y += RenderPreview(PREVIEW_TEAM, X, Y).y;
	}

	// Friend
	if(!g_Config.m_ClChatOld && !g_Config.m_ClShowChatTeamMembersOnly)
		RenderTools()->RenderTee(pIdleState, &s_vLines[PREVIEW_FRIEND].m_RenderInfo, EMOTE_NORMAL, vec2(1, 0.1f), vec2(X + RealTeeSizeHalved, Y + OffsetTeeY + FullHeightMinusTee / 2.0f + TWSkinUnreliableOffset));
	if(!g_Config.m_ClShowChatTeamMembersOnly)
		Y += RenderPreview(PREVIEW_FRIEND, X, Y).y;

	// Normal
	if(!g_Config.m_ClShowChatFriends && !g_Config.m_ClShowChatTeamMembersOnly)
	{
		if(!g_Config.m_ClChatOld)
			RenderTools()->RenderTee(pIdleState, &s_vLines[PREVIEW_SPAMMER].m_RenderInfo, EMOTE_NORMAL, vec2(1, 0.1f), vec2(X + RealTeeSizeHalved, Y + OffsetTeeY + FullHeightMinusTee / 2.0f + TWSkinUnreliableOffset));
		Y += RenderPreview(PREVIEW_SPAMMER, X, Y).y;
	}
	// Enemy
	RenderTools()->RenderTee(pIdleState, &s_vLines[PREVIEW_ENEMY].m_RenderInfo, EMOTE_ANGRY, vec2(1, 0.1f), vec2(X + RealTeeSizeHalved, Y + OffsetTeeY + FullHeightMinusTee / 2.0f + TWSkinUnreliableOffset));
	Y += RenderPreview(PREVIEW_ENEMY, X, Y).y;
	// Helper
	RenderTools()->RenderTee(pIdleState, &s_vLines[PREVIEW_HELPER].m_RenderInfo, EMOTE_NORMAL, vec2(1, 0.1f), vec2(X + RealTeeSizeHalved, Y + OffsetTeeY + FullHeightMinusTee / 2.0f + TWSkinUnreliableOffset));
	Y += RenderPreview(PREVIEW_HELPER, X, Y).y;
	// Teammate
	RenderTools()->RenderTee(pIdleState, &s_vLines[PREVIEW_TEAMMATE].m_RenderInfo, EMOTE_NORMAL, vec2(1, 0.1f), vec2(X + RealTeeSizeHalved, Y + OffsetTeeY + FullHeightMinusTee / 2.0f + TWSkinUnreliableOffset));
	Y += RenderPreview(PREVIEW_TEAMMATE, X, Y).y;
	// Spectating
	RenderTools()->RenderTee(pIdleState, &s_vLines[PREVIEW_SPEC].m_RenderInfo, EMOTE_NORMAL, vec2(1, 0.1f), vec2(X + RealTeeSizeHalved, Y + OffsetTeeY + FullHeightMinusTee / 2.0f + TWSkinUnreliableOffset));
	Y += RenderPreview(PREVIEW_SPEC, X, Y).y;
	// Client
	RenderPreview(PREVIEW_CLIENT, X, Y);

	TextRender()->TextColor(TextRender()->DefaultTextColor());
}

void CMenus::RenderSettingsWarList(CUIRect MainView)
{
	CUIRect RightView, LeftView, TrailSettings1, TrailSettings2, TrailSettings3, TrailSettings4, Button, ButtonL, ButtonR, Label;

	MainView.HSplitTop(MarginSmall, nullptr, &MainView);
	MainView.VSplitMid(&LeftView, &RightView, Margin);
	LeftView.VSplitLeft(MarginSmall, nullptr, &LeftView);
	RightView.VSplitRight(MarginSmall, &RightView, nullptr);

	// WAR LIST will have 4 TrailSettingss
	//  [War entries] - [Entry Editing] - [Group Types] - [Recent Players]
	//									 [Group Editing]

	// putting this here so it can be updated by the entry list
	static char s_aEntryName[MAX_NAME_LENGTH];
	static char s_aEntryClan[MAX_CLAN_LENGTH];
	static char s_aEntryReason[MAX_WARLIST_REASON_LENGTH];
	static int s_IsClan = 0;
	static int s_IsName = 1;

	LeftView.VSplitMid(&TrailSettings1, &TrailSettings2, Margin);
	RightView.VSplitMid(&TrailSettings3, &TrailSettings4, Margin);

	// ======WAR ENTRIES======
	TrailSettings1.HSplitTop(HeadlineHeight, &Label, &TrailSettings1);
	Label.VSplitRight(25.0f, &Label, &Button);
	Ui()->DoLabel(&Label, Localize("War Entries"), HeadlineFontSize, TEXTALIGN_ML);
	TrailSettings1.HSplitTop(MarginSmall, nullptr, &TrailSettings1);

	static CButtonContainer s_ReverseEntries;
	static bool s_Reversed = true;
	if(DoButton_FontIcon(&s_ReverseEntries, FONT_ICON_CHEVRON_DOWN, 0, &Button, IGraphics::CORNER_ALL))
	{
		s_Reversed = !s_Reversed;
	}

	CUIRect EntriesSearch;
	TrailSettings1.HSplitBottom(25.0f, &TrailSettings1, &EntriesSearch);
	EntriesSearch.HSplitTop(MarginSmall, nullptr, &EntriesSearch);

	static CWarEntry *pSelectedEntry = nullptr;
	static CWarType *pSelectedType = GameClient()->m_WarList.m_WarTypes[0];

	// Filter the list
	static CLineInputBuffered<128> s_EntriesFilterInput;
	std::vector<CWarEntry *> vpFilteredEntries;
	for(size_t i = 0; i < GameClient()->m_WarList.m_WarEntries.size(); ++i)
	{
		CWarEntry *pEntry = &GameClient()->m_WarList.m_WarEntries[i];
		bool Matches = false;
		if(str_find_nocase(pEntry->m_aName, s_EntriesFilterInput.GetString()))
			Matches = true;
		if(str_find_nocase(pEntry->m_aClan, s_EntriesFilterInput.GetString()))
			Matches = true;
		if(str_find_nocase(pEntry->m_pWarType->m_aWarName, s_EntriesFilterInput.GetString()))
			Matches = true;
		if(Matches)
			vpFilteredEntries.push_back(pEntry);
	}

	if(s_Reversed)
	{
		std::reverse(vpFilteredEntries.begin(), vpFilteredEntries.end());
	}
	int SelectedOldEntry = -1;
	static CListBox s_EntriesListBox;
	s_EntriesListBox.DoStart(35.0f, vpFilteredEntries.size(), 1, 2, SelectedOldEntry, &TrailSettings1);

	static std::vector<unsigned char> s_vItemIds;
	static std::vector<CButtonContainer> s_vDeleteButtons;

	const int MaxEntries = GameClient()->m_WarList.m_WarEntries.size();
	s_vItemIds.resize(MaxEntries);
	s_vDeleteButtons.resize(MaxEntries);

	for(size_t i = 0; i < vpFilteredEntries.size(); i++)
	{
		CWarEntry *pEntry = vpFilteredEntries[i];

		// idk why it wants this, it was complaining
		if(!pEntry)
			continue;

		if(pSelectedEntry && pEntry == pSelectedEntry)
			SelectedOldEntry = i;

		const CListboxItem Item = s_EntriesListBox.DoNextItem(&s_vItemIds[i], SelectedOldEntry >= 0 && (size_t)SelectedOldEntry == i);
		if(!Item.m_Visible)
			continue;

		CUIRect EntryRect, DeleteButton, EntryTypeRect, WarType, ToolTip;
		Item.m_Rect.Margin(0.0f, &EntryRect);
		EntryRect.VSplitLeft(26.0f, &DeleteButton, &EntryRect);
		DeleteButton.HMargin(7.5f, &DeleteButton);
		DeleteButton.VSplitLeft(MarginSmall, nullptr, &DeleteButton);
		DeleteButton.VSplitRight(MarginExtraSmall, &DeleteButton, nullptr);

		if(DoButton_FontIcon(&s_vDeleteButtons[i], FONT_ICON_TRASH, 0, &DeleteButton, IGraphics::CORNER_ALL))
			GameClient()->m_WarList.RemoveWarEntry(pEntry);

		bool IsClan = false;
		char aBuf[32];
		if(str_comp(pEntry->m_aClan, "") != 0)
		{
			str_copy(aBuf, pEntry->m_aClan);
			IsClan = true;
		}
		else
		{
			str_copy(aBuf, pEntry->m_aName);
		}
		EntryRect.VSplitLeft(35.0f, &EntryTypeRect, &EntryRect);

		if(IsClan)
		{
			RenderFontIcon(EntryTypeRect, FONT_ICON_USERS, 18.0f, TEXTALIGN_MC);
		}
		else
		{
			// TODO: stop misusing this function
			// TODO: render the real skin with skin remembering component (to be added)
			RenderDevSkin(EntryTypeRect.Center(), 35.0f, "default", "default", false, 0, 0, 0, false);
		}

		if(str_comp(pEntry->m_aReason, "") != 0)
		{
			EntryRect.VSplitRight(20.0f, &EntryRect, &ToolTip);
			RenderFontIcon(ToolTip, FONT_ICON_COMMENT, 18.0f, TEXTALIGN_MC);
			GameClient()->m_Tooltips.DoToolTip(&s_vItemIds[i], &ToolTip, pEntry->m_aReason);
			GameClient()->m_Tooltips.SetFadeTime(&s_vItemIds[i], 0.0f);
		}

		EntryRect.HMargin(MarginExtraSmall, &EntryRect);
		EntryRect.HSplitMid(&EntryRect, &WarType, MarginSmall);

		Ui()->DoLabel(&EntryRect, aBuf, StandardFontSize, TEXTALIGN_ML);
		TextRender()->TextColor(pEntry->m_pWarType->m_Color);
		Ui()->DoLabel(&WarType, pEntry->m_pWarType->m_aWarName, StandardFontSize, TEXTALIGN_ML);
		TextRender()->TextColor(TextRender()->DefaultTextColor());
	}
	const int NewSelectedEntry = s_EntriesListBox.DoEnd();
	if(SelectedOldEntry != NewSelectedEntry || (SelectedOldEntry >= 0 && Ui()->HotItem() == &s_vItemIds[NewSelectedEntry] && Ui()->MouseButtonClicked(0)))
	{
		pSelectedEntry = vpFilteredEntries[NewSelectedEntry];
		if(!Ui()->LastMouseButton(1) && !Ui()->LastMouseButton(2))
		{
			str_copy(s_aEntryName, pSelectedEntry->m_aName);
			str_copy(s_aEntryClan, pSelectedEntry->m_aClan);
			str_copy(s_aEntryReason, pSelectedEntry->m_aReason);
			if(str_comp(pSelectedEntry->m_aClan, "") != 0)
			{
				s_IsName = 0;
				s_IsClan = 1;
			}
			else
			{
				s_IsName = 1;
				s_IsClan = 0;
			}
			pSelectedType = pSelectedEntry->m_pWarType;
		}
	}

	Ui()->DoEditBox_Search(&s_EntriesFilterInput, &EntriesSearch, 14.0f, !Ui()->IsPopupOpen() && !m_pClient->m_GameConsole.IsActive());

	// ======WAR ENTRY EDITING======
	TrailSettings2.HSplitTop(HeadlineHeight, &Label, &TrailSettings2);
	Label.VSplitRight(25.0f, &Label, &Button);
	Ui()->DoLabel(&Label, Localize("Edit Entry"), HeadlineFontSize, TEXTALIGN_ML);
	TrailSettings2.HSplitTop(MarginSmall, nullptr, &TrailSettings2);
	TrailSettings2.HSplitTop(HeadlineFontSize, &Button, &TrailSettings2);

	Button.VSplitMid(&ButtonL, &ButtonR, MarginSmall);
	static CLineInput s_NameInput;
	s_NameInput.SetBuffer(s_aEntryName, sizeof(s_aEntryName));
	s_NameInput.SetEmptyText("Name");
	if(s_IsName)
		Ui()->DoEditBox(&s_NameInput, &ButtonL, 12.0f);
	else
	{
		ButtonL.Draw(ColorRGBA(1.0f, 1.0f, 1.0f, 0.25f), 15, 3.0f);
		Ui()->ClipEnable(&ButtonL);
		ButtonL.VMargin(2.0f, &ButtonL);
		s_NameInput.Render(&ButtonL, 12.0f, TEXTALIGN_ML, false, -1.0f, 0.0f);
		Ui()->ClipDisable();
	}

	static CLineInput s_ClanInput;
	s_ClanInput.SetBuffer(s_aEntryClan, sizeof(s_aEntryClan));
	s_ClanInput.SetEmptyText("Clan");
	if(s_IsClan)
		Ui()->DoEditBox(&s_ClanInput, &ButtonR, 12.0f);
	else
	{
		ButtonR.Draw(ColorRGBA(1.0f, 1.0f, 1.0f, 0.25f), 15, 3.0f);
		Ui()->ClipEnable(&ButtonR);
		ButtonR.VMargin(2.0f, &ButtonR);
		s_ClanInput.Render(&ButtonR, 12.0f, TEXTALIGN_ML, false, -1.0f, 0.0f);
		Ui()->ClipDisable();
	}

	TrailSettings2.HSplitTop(MarginSmall, nullptr, &TrailSettings2);
	TrailSettings2.HSplitTop(LineSize, &Button, &TrailSettings2);
	Button.VSplitMid(&ButtonL, &ButtonR, MarginSmall);
	static unsigned char s_NameRadio, s_ClanRadio;
	if(DoButton_CheckBox_Common(&s_NameRadio, "Name", s_IsName ? "X" : "", &ButtonL, BUTTONFLAG_ALL))
	{
		s_IsName = 1;
		s_IsClan = 0;
	}
	if(DoButton_CheckBox_Common(&s_ClanRadio, "Clan", s_IsClan ? "X" : "", &ButtonR, BUTTONFLAG_ALL))
	{
		s_IsName = 0;
		s_IsClan = 1;
	}
	if(!s_IsName)
		str_copy(s_aEntryName, "");
	if(!s_IsClan)
		str_copy(s_aEntryClan, "");

	TrailSettings2.HSplitTop(MarginSmall, nullptr, &TrailSettings2);
	TrailSettings2.HSplitTop(HeadlineFontSize, &Button, &TrailSettings2);
	static CLineInput s_ReasonInput;
	s_ReasonInput.SetBuffer(s_aEntryReason, sizeof(s_aEntryReason));
	s_ReasonInput.SetEmptyText("Reason");
	Ui()->DoEditBox(&s_ReasonInput, &Button, 12.0f);

	static CButtonContainer s_AddButton, s_OverrideButton;

	TrailSettings2.HSplitTop(MarginSmall, nullptr, &TrailSettings2);
	TrailSettings2.HSplitTop(LineSize * 2.0f, &Button, &TrailSettings2);
	Button.VSplitMid(&ButtonL, &ButtonR, MarginSmall);

	if(DoButtonLineSize_Menu(&s_OverrideButton, Localize("Override Entry"), 0, &ButtonL, LineSize) && pSelectedEntry)
	{
		if(pSelectedEntry && pSelectedType && (str_comp(s_aEntryName, "") != 0 || str_comp(s_aEntryClan, "") != 0))
		{
			str_copy(pSelectedEntry->m_aName, s_aEntryName);
			str_copy(pSelectedEntry->m_aClan, s_aEntryClan);
			str_copy(pSelectedEntry->m_aReason, s_aEntryReason);
			pSelectedEntry->m_pWarType = pSelectedType;
		}
	}
	if(DoButtonLineSize_Menu(&s_AddButton, Localize("Add Entry"), 0, &ButtonR, LineSize))
	{
		if(pSelectedType)
			GameClient()->m_WarList.AddWarEntry(s_aEntryName, s_aEntryClan, s_aEntryReason, pSelectedType->m_aWarName);
	}
	TrailSettings2.HSplitTop(MarginSmall, nullptr, &TrailSettings2);
	TrailSettings2.HSplitTop(HeadlineFontSize + MarginSmall, &Button, &TrailSettings2);
	if(pSelectedType)
	{
		float Shade = 0.0f;
		Button.Draw(ColorRGBA(Shade, Shade, Shade, 0.25f), 15, 3.0f);
		TextRender()->TextColor(pSelectedType->m_Color);
		Ui()->DoLabel(&Button, pSelectedType->m_aWarName, HeadlineFontSize, TEXTALIGN_MC);
		TextRender()->TextColor(TextRender()->DefaultTextColor());
	}

	TrailSettings2.HSplitBottom(150.0f, nullptr, &TrailSettings2);

	TrailSettings2.HSplitTop(HeadlineHeight, &Label, &TrailSettings2);
	Ui()->DoLabel(&Label, Localize("Settings"), HeadlineFontSize, TEXTALIGN_ML);
	TrailSettings2.HSplitTop(MarginSmall, nullptr, &TrailSettings2);

	DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClWarListAllowDuplicates, Localize("Allow Duplicate Entries"), &g_Config.m_ClWarListAllowDuplicates, &TrailSettings2, LineSize);
	DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClWarList, Localize("Enable warlist"), &g_Config.m_ClWarList, &TrailSettings2, LineSize);
	DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClWarListChat, Localize("Colors in chat"), &g_Config.m_ClWarListChat, &TrailSettings2, LineSize);
	DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClWarlistPrefixes, Localize("Warlist Prefixes"), &g_Config.m_ClWarlistPrefixes, &TrailSettings2, LineSize);
	DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClWarListScoreboard, Localize("Colors in scoreboard"), &g_Config.m_ClWarListScoreboard, &TrailSettings2, LineSize);
	DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClWarListShowClan, Localize("Show clan if war"), &g_Config.m_ClWarListShowClan, &TrailSettings2, LineSize);

	// ======WAR TYPE EDITING======

	TrailSettings3.HSplitTop(HeadlineHeight, &Label, &TrailSettings3);
	Ui()->DoLabel(&Label, Localize("War Groups"), HeadlineFontSize, TEXTALIGN_ML);
	TrailSettings3.HSplitTop(MarginSmall, nullptr, &TrailSettings3);

	static char s_aTypeName[MAX_WARLIST_TYPE_LENGTH];
	static ColorRGBA s_GroupColor = ColorRGBA(1, 1, 1, 1);

	CUIRect WarTypeList;
	TrailSettings3.HSplitBottom(180.0f, &WarTypeList, &TrailSettings3);
	m_pRemoveWarType = nullptr;
	int SelectedOldType = -1;
	static CListBox s_WarTypeListBox;
	s_WarTypeListBox.DoStart(25.0f, GameClient()->m_WarList.m_WarTypes.size(), 1, 2, SelectedOldType, &WarTypeList);

	static std::vector<unsigned char> s_vTypeItemIds;
	static std::vector<CButtonContainer> s_vTypeDeleteButtons;

	const int MaxTypes = GameClient()->m_WarList.m_WarTypes.size();
	s_vTypeItemIds.resize(MaxTypes);
	s_vTypeDeleteButtons.resize(MaxTypes);

	for(int i = 0; i < (int)GameClient()->m_WarList.m_WarTypes.size(); i++)
	{
		CWarType *pType = GameClient()->m_WarList.m_WarTypes[i];

		if(!pType)
			continue;

		if(pSelectedType && pType == pSelectedType)
			SelectedOldType = i;

		const CListboxItem Item = s_WarTypeListBox.DoNextItem(&s_vTypeItemIds[i], SelectedOldType >= 0 && SelectedOldType == i);
		if(!Item.m_Visible)
			continue;

		CUIRect TypeRect, DeleteButton;
		Item.m_Rect.Margin(0.0f, &TypeRect);

		if(pType->m_Removable)
		{
			TypeRect.VSplitRight(20.0f, &TypeRect, &DeleteButton);
			DeleteButton.HSplitTop(20.0f, &DeleteButton, nullptr);
			DeleteButton.Margin(2.0f, &DeleteButton);
			if(DoButtonNoRect_FontIcon(&s_vTypeDeleteButtons[i], FONT_ICON_TRASH, 0, &DeleteButton, IGraphics::CORNER_ALL))
				m_pRemoveWarType = pType;
		}
		TextRender()->TextColor(pType->m_Color);
		Ui()->DoLabel(&TypeRect, pType->m_aWarName, StandardFontSize, TEXTALIGN_ML);
		TextRender()->TextColor(TextRender()->DefaultTextColor());
	}
	const int NewSelectedType = s_WarTypeListBox.DoEnd();
	if((SelectedOldType != NewSelectedType && NewSelectedType >= 0) || (NewSelectedType >= 0 && Ui()->HotItem() == &s_vTypeItemIds[NewSelectedType] && Ui()->MouseButtonClicked(0)))
	{
		pSelectedType = GameClient()->m_WarList.m_WarTypes[NewSelectedType];
		if(!Ui()->LastMouseButton(1) && !Ui()->LastMouseButton(2))
		{
			str_copy(s_aTypeName, pSelectedType->m_aWarName);
			s_GroupColor = pSelectedType->m_Color;
		}
	}
	if(m_pRemoveWarType != nullptr)
	{
		char aMessage[256];
		str_format(aMessage, sizeof(aMessage),
			Localize("Are you sure that you want to remove '%s' from your war groups?"),
			m_pRemoveWarType->m_aWarName);
		PopupConfirm(Localize("Remove War Group"), aMessage, Localize("Yes"), Localize("No"), &CMenus::PopupConfirmRemoveWarType);
	}

	static CLineInput s_TypeNameInput;
	TrailSettings3.HSplitTop(MarginSmall, nullptr, &TrailSettings3);
	TrailSettings3.HSplitTop(HeadlineFontSize + MarginSmall, &Button, &TrailSettings3);
	s_TypeNameInput.SetBuffer(s_aTypeName, sizeof(s_aTypeName));
	s_TypeNameInput.SetEmptyText("Group Name");
	Ui()->DoEditBox(&s_TypeNameInput, &Button, 12.0f);
	static CButtonContainer s_AddGroupButton, s_OverrideGroupButton, s_GroupColorPicker;

	TrailSettings3.HSplitTop(MarginSmall, nullptr, &TrailSettings3);
	static unsigned int ColorValue = 0;
	ColorValue = color_cast<ColorHSLA>(s_GroupColor).Pack(false);
	ColorHSLA PickedColor = DoLine_ColorPicker(&s_GroupColorPicker, ColorPickerLineSize, ColorPickerLabelSize, ColorPickerLineSpacing, &TrailSettings3, Localize("Color"), &ColorValue, ColorRGBA(1.0f, 1.0f, 1.0f), true);
	s_GroupColor = color_cast<ColorRGBA>(PickedColor);

	TrailSettings3.HSplitTop(LineSize * 2.0f, &Button, &TrailSettings3);
	Button.VSplitMid(&ButtonL, &ButtonR, MarginSmall);
	bool OverrideDisabled = NewSelectedType == 0;
	if(DoButtonLineSize_Menu(&s_OverrideGroupButton, Localize("Override Group"), 0, &ButtonL, LineSize, OverrideDisabled) && pSelectedType)
	{
		if(pSelectedType && str_comp(s_aTypeName, "") != 0)
		{
			str_copy(pSelectedType->m_aWarName, s_aTypeName);
			pSelectedType->m_Color = s_GroupColor;
		}
	}
	bool AddDisabled = str_comp(GameClient()->m_WarList.FindWarType(s_aTypeName)->m_aWarName, "none") != 0 || str_comp(s_aTypeName, "none") == 0;
	if(DoButtonLineSize_Menu(&s_AddGroupButton, Localize("Add Group"), 0, &ButtonR, LineSize, AddDisabled))
	{
		GameClient()->m_WarList.AddWarType(s_aTypeName, s_GroupColor);
	}

	// ======ONLINE PLAYER LIST======

	TrailSettings4.HSplitTop(HeadlineHeight, &Label, &TrailSettings4);
	Ui()->DoLabel(&Label, Localize("Online Players"), HeadlineFontSize, TEXTALIGN_ML);
	TrailSettings4.HSplitTop(MarginSmall, nullptr, &TrailSettings4);

	CUIRect PlayerList;
	TrailSettings4.HSplitBottom(0.0f, &PlayerList, &TrailSettings4);
	static CListBox s_PlayerListBox;
	s_PlayerListBox.DoStart(30.0f, MAX_CLIENTS, 1, 2, -1, &PlayerList);

	static std::vector<unsigned char> s_vPlayerItemIds;
	static std::vector<CButtonContainer> s_vNameButtons;
	static std::vector<CButtonContainer> s_vClanButtons;

	s_vPlayerItemIds.resize(MAX_CLIENTS);
	s_vNameButtons.resize(MAX_CLIENTS);
	s_vClanButtons.resize(MAX_CLIENTS);

	for(int i = 0; i < MAX_CLIENTS; i++)
	{
		if(!m_pClient->m_Snap.m_apPlayerInfos[i])
			continue;

		CTeeRenderInfo TeeInfo = m_pClient->m_aClients[i].m_RenderInfo;

		const CListboxItem Item = s_PlayerListBox.DoNextItem(&s_vPlayerItemIds[i], false);
		if(!Item.m_Visible)
			continue;

		CUIRect PlayerRect, TeeRect, NameRect, ClanRect;
		Item.m_Rect.Margin(0.0f, &PlayerRect);
		PlayerRect.VSplitLeft(25.0f, &TeeRect, &PlayerRect);
		// RenderDevSkin(TeeRect.Center(), 35.0f, TeeInfo., "default", false, 0, 0, 0, false);

		PlayerRect.VSplitMid(&NameRect, &ClanRect, 0);
		PlayerRect = NameRect;
		PlayerRect.x = TeeRect.x;
		PlayerRect.w += TeeRect.w;
		TextRender()->TextColor(GameClient()->m_WarList.GetWarData(i).m_NameColor);
		ColorRGBA NameButtonColor = Ui()->CheckActiveItem(&s_vNameButtons[i]) ? ColorRGBA(1, 1, 1, 0.75f) :
											(Ui()->HotItem() == &s_vNameButtons[i] ? ColorRGBA(1, 1, 1, 0.33f) : ColorRGBA(1, 1, 1, 0.0f));
		PlayerRect.Draw(NameButtonColor, IGraphics::CORNER_L, 5.0f);
		Ui()->DoLabel(&NameRect, GameClient()->m_aClients[i].m_aName, StandardFontSize, TEXTALIGN_ML);
		if(Ui()->DoButtonLogic(&s_vNameButtons[i], false, &PlayerRect, BUTTONFLAG_ALL))
		{
			s_IsName = 1;
			s_IsClan = 0;
			str_copy(s_aEntryName, GameClient()->m_aClients[i].m_aName);
		}

		TextRender()->TextColor(GameClient()->m_WarList.GetWarData(i).m_ClanColor);
		ColorRGBA ClanButtonColor = Ui()->CheckActiveItem(&s_vClanButtons[i]) ? ColorRGBA(1, 1, 1, 0.75f) :
											(Ui()->HotItem() == &s_vClanButtons[i] ? ColorRGBA(1, 1, 1, 0.33f) : ColorRGBA(1, 1, 1, 0.0f));
		ClanRect.Draw(ClanButtonColor, IGraphics::CORNER_R, 5.0f);
		Ui()->DoLabel(&ClanRect, GameClient()->m_aClients[i].m_aClan, StandardFontSize, TEXTALIGN_ML);
		if(Ui()->DoButtonLogic(&s_vClanButtons[i], false, &ClanRect, BUTTONFLAG_ALL))
		{
			s_IsName = 0;
			s_IsClan = 1;
			str_copy(s_aEntryClan, GameClient()->m_aClients[i].m_aClan);
		}
		TextRender()->TextColor(TextRender()->DefaultTextColor());

		TeeInfo.m_Size = 25.0f;
		RenderTools()->RenderTee(CAnimState::GetIdle(), &TeeInfo, 0, vec2(1.0f, 0.0f), TeeRect.Center() + vec2(-1.0f, 2.5f));
	}
	s_PlayerListBox.DoEnd();
}


void CMenus::PopupConfirmRemoveWarType()
{
	GameClient()->m_WarList.RemoveWarType(m_pRemoveWarType->m_aWarName);
	m_pRemoveWarType = nullptr;
}

int CMenus::DoButtonLineSize_Menu(CButtonContainer *pButtonContainer, const char *pText, int Checked, const CUIRect *pRect, float Line_Size, bool Fake, const char *pImageName, int Corners, float Rounding, float FontFactor, ColorRGBA Color)
{
	CUIRect Text = *pRect;

	if(Checked)
		Color = ColorRGBA(0.6f, 0.6f, 0.6f, 0.5f);
	Color.a *= Ui()->ButtonColorMul(pButtonContainer);

	if(Fake)
		Color.a *= 0.5f;

	pRect->Draw(Color, Corners, Rounding);

	Text.HMargin(Line_Size / 2.0f, &Text);
	Text.HMargin(pRect->h >= 20.0f ? 2.0f : 1.0f, &Text);
	Text.HMargin((Text.h * FontFactor) / 2.0f, &Text);
	Ui()->DoLabel(&Text, pText, Text.h * CUi::ms_FontmodHeight, TEXTALIGN_MC);

	if(Fake)
		return 0;

	return Ui()->DoButtonLogic(pButtonContainer, Checked, pRect, BUTTONFLAG_ALL);
}

void CMenus::RenderDevSkin(vec2 RenderPos, float Size, const char *pSkinName, const char *pBackupSkin, bool CustomColors, int FeetColor, int BodyColor, int Emote, bool Rainbow, ColorRGBA ColorFeet, ColorRGBA ColorBody)
{
	float DefTick = std::fmod(s_Time, 1.0f);

	CTeeRenderInfo SkinInfo;
	const CSkin *pSkin = m_pClient->m_Skins.Find(pSkinName);
	if(str_comp(pSkin->GetName(), pSkinName) != 0)
		pSkin = m_pClient->m_Skins.Find(pBackupSkin);

	SkinInfo.m_OriginalRenderSkin = pSkin->m_OriginalSkin;
	SkinInfo.m_ColorableRenderSkin = pSkin->m_ColorableSkin;
	SkinInfo.m_SkinMetrics = pSkin->m_Metrics;
	SkinInfo.m_CustomColoredSkin = CustomColors;
	if(SkinInfo.m_CustomColoredSkin)
	{
		SkinInfo.m_ColorBody = color_cast<ColorRGBA>(ColorHSLA(BodyColor).UnclampLighting(ColorHSLA::DARKEST_LGT));
		SkinInfo.m_ColorFeet = color_cast<ColorRGBA>(ColorHSLA(FeetColor).UnclampLighting(ColorHSLA::DARKEST_LGT));
		if(ColorFeet.a != 0.0f)
		{
			SkinInfo.m_ColorBody = ColorBody;
			SkinInfo.m_ColorFeet = ColorFeet;
		}
	}
	else
	{
		SkinInfo.m_ColorBody = ColorRGBA(1.0f, 1.0f, 1.0f);
		SkinInfo.m_ColorFeet = ColorRGBA(1.0f, 1.0f, 1.0f);
	}
	if(Rainbow)
	{
		ColorRGBA Col = color_cast<ColorRGBA>(ColorHSLA(DefTick, 1.0f, 0.5f));
		SkinInfo.m_ColorBody = Col;
		SkinInfo.m_ColorFeet = Col;
	}
	SkinInfo.m_Size = Size;
	const CAnimState *pIdleState = CAnimState::GetIdle();
	vec2 OffsetToMid;
	CRenderTools::GetRenderTeeOffsetToRenderedTee(pIdleState, &SkinInfo, OffsetToMid);
	vec2 TeeRenderPos(RenderPos.x, RenderPos.y + OffsetToMid.y);
	RenderTools()->RenderTee(pIdleState, &SkinInfo, Emote, vec2(1.0f, 0.0f), TeeRenderPos);
}

void CMenus::RenderFontIcon(const CUIRect Rect, const char *pText, float Size, int Align)
{
	TextRender()->SetFontPreset(EFontPreset::ICON_FONT);
	TextRender()->SetRenderFlags(ETextRenderFlags::TEXT_RENDER_FLAG_ONLY_ADVANCE_WIDTH | ETextRenderFlags::TEXT_RENDER_FLAG_NO_X_BEARING | ETextRenderFlags::TEXT_RENDER_FLAG_NO_Y_BEARING);
	Ui()->DoLabel(&Rect, pText, Size, Align);
	TextRender()->SetRenderFlags(0);
	TextRender()->SetFontPreset(EFontPreset::DEFAULT_FONT);
}

int CMenus::DoButtonNoRect_FontIcon(CButtonContainer *pButtonContainer, const char *pText, int Checked, const CUIRect *pRect, int Corners)
{
	TextRender()->SetFontPreset(EFontPreset::ICON_FONT);
	TextRender()->SetRenderFlags(ETextRenderFlags::TEXT_RENDER_FLAG_ONLY_ADVANCE_WIDTH | ETextRenderFlags::TEXT_RENDER_FLAG_NO_X_BEARING | ETextRenderFlags::TEXT_RENDER_FLAG_NO_Y_BEARING);
	TextRender()->TextOutlineColor(TextRender()->DefaultTextOutlineColor());
	TextRender()->TextColor(TextRender()->DefaultTextSelectionColor());
	if(Ui()->HotItem() == pButtonContainer)
	{
		TextRender()->TextColor(TextRender()->DefaultTextColor());
	}
	CUIRect Temp;
	pRect->HMargin(0.0f, &Temp);
	Ui()->DoLabel(&Temp, pText, Temp.h * CUi::ms_FontmodHeight, TEXTALIGN_MC);
	TextRender()->SetRenderFlags(0);
	TextRender()->SetFontPreset(EFontPreset::DEFAULT_FONT);

	return Ui()->DoButtonLogic(pButtonContainer, Checked, pRect, BUTTONFLAG_ALL);
}

bool CMenus::DoSliderWithScaledValue(const void *pId, int *pOption, const CUIRect *pRect, const char *pStr, int Min, int Max, int Scale, const IScrollbarScale *pScale, unsigned Flags, const char *pSuffix)
{
	const bool NoClampValue = Flags & CUi::SCROLLBAR_OPTION_NOCLAMPVALUE;

	int Value = *pOption;
	Min /= Scale;
	Max /= Scale;
	// Allow adjustment of slider options when ctrl is pressed (to avoid scrolling, or accidently adjusting the value)
	int Increment = std::max(1, (Max - Min) / 35);
	if(Input()->ModifierIsPressed() && Input()->KeyPress(KEY_MOUSE_WHEEL_UP) && Ui()->MouseInside(pRect))
	{
		Value += Increment;
		Value = clamp(Value, Min, Max);
	}
	if(Input()->ModifierIsPressed() && Input()->KeyPress(KEY_MOUSE_WHEEL_DOWN) && Ui()->MouseInside(pRect))
	{
		Value -= Increment;
		Value = clamp(Value, Min, Max);
	}

	char aBuf[256];
	str_format(aBuf, sizeof(aBuf), "%s: %i%s", pStr, Value * Scale, pSuffix);

	if(NoClampValue)
	{
		// clamp the value internally for the scrollbar
		Value = clamp(Value, Min, Max);
	}

	CUIRect Label, ScrollBar;
	pRect->VSplitMid(&Label, &ScrollBar, minimum(10.0f, pRect->w * 0.05f));

	const float LabelFontSize = Label.h * CUi::ms_FontmodHeight * 0.8f;
	Ui()->DoLabel(&Label, aBuf, LabelFontSize, TEXTALIGN_ML);

	Value = pScale->ToAbsolute(Ui()->DoScrollbarH(pId, &ScrollBar, pScale->ToRelative(Value, Min, Max)), Min, Max);
	if(NoClampValue && ((Value == Min && *pOption < Min) || (Value == Max && *pOption > Max)))
	{
		Value = *pOption;
	}

	if(*pOption != Value)
	{
		*pOption = Value;
		return true;
	}
	return false;
}

void CMenus::RenderSettingsStatusBar(CUIRect MainView)
{
	CUIRect LeftView, RightView, Button, Label, StatusBar;
	MainView.HSplitTop(MarginSmall, nullptr, &MainView);

	MainView.HSplitBottom(100.0f, &MainView, &StatusBar);

	MainView.VSplitMid(&LeftView, &RightView, MarginBetweenViews);
	LeftView.VSplitLeft(MarginSmall, nullptr, &LeftView);
	RightView.VSplitRight(MarginSmall, &RightView, nullptr);

	LeftView.HSplitTop(HeadlineHeight, &Label, &LeftView);
	Ui()->DoLabel(&Label, Localize("Status Bar"), HeadlineFontSize, TEXTALIGN_ML);
	LeftView.HSplitTop(MarginSmall, nullptr, &LeftView);

	DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClStatusBar, Localize("Show status bar"), &g_Config.m_ClStatusBar, &LeftView, LineSize);
	DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClStatusBarLabels, Localize("Show labels on status bar items"), &g_Config.m_ClStatusBarLabels, &LeftView, LineSize);
	LeftView.HSplitTop(LineSize, &Button, &LeftView);
	Ui()->DoScrollbarOption(&g_Config.m_ClStatusBarHeight, &g_Config.m_ClStatusBarHeight, &Button, Localize("Status bar height"), 1, 16);

	LeftView.HSplitTop(HeadlineHeight, &Label, &LeftView);

	LeftView.HSplitTop(HeadlineHeight, &Label, &LeftView);
	Ui()->DoLabel(&Label, Localize("Local Time"), HeadlineFontSize, TEXTALIGN_ML);
	LeftView.HSplitTop(MarginSmall, nullptr, &LeftView);
	DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClStatusBar12HourClock, Localize("Use 12 hour clock"), &g_Config.m_ClStatusBar12HourClock, &LeftView, LineSize);
	DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClStatusBarLocalTimeSeocnds, Localize("Show seconds on clock"), &g_Config.m_ClStatusBarLocalTimeSeocnds, &LeftView, LineSize);
	LeftView.HSplitTop(HeadlineHeight, &Label, &LeftView);

	LeftView.HSplitTop(HeadlineHeight, &Label, &LeftView);
	Ui()->DoLabel(&Label, Localize("Colors"), HeadlineFontSize, TEXTALIGN_ML);
	LeftView.HSplitTop(MarginSmall, nullptr, &LeftView);
	static CButtonContainer s_StatusbarColor, s_StatusbarTextColor;

	DoLine_ColorPicker(&s_StatusbarColor, ColorPickerLineSize, ColorPickerLabelSize, ColorPickerLineSpacing, &LeftView, Localize("Status bar color"), &g_Config.m_ClStatusBarColor, ColorRGBA(0.0f, 0.0f, 0.0f), false);
	DoLine_ColorPicker(&s_StatusbarTextColor, ColorPickerLineSize, ColorPickerLabelSize, ColorPickerLineSpacing, &LeftView, Localize("Text color"), &g_Config.m_ClStatusBarTextColor, ColorRGBA(1.0f, 1.0f, 1.0f), false);
	LeftView.HSplitTop(LineSize, &Button, &LeftView);
	Ui()->DoScrollbarOption(&g_Config.m_ClStatusBarAlpha, &g_Config.m_ClStatusBarAlpha, &Button, Localize("Status bar alpha"), 0, 100);
	LeftView.HSplitTop(LineSize, &Button, &LeftView);
	Ui()->DoScrollbarOption(&g_Config.m_ClStatusBarTextAlpha, &g_Config.m_ClStatusBarTextAlpha, &Button, Localize("Text alpha"), 0, 100);

	RightView.HSplitTop(HeadlineHeight, &Label, &RightView);
	Ui()->DoLabel(&Label, Localize("Status Bar Codes:"), HeadlineFontSize, TEXTALIGN_ML);
	RightView.HSplitTop(MarginSmall, nullptr, &RightView);
	RightView.HSplitTop(LineSize, &Label, &RightView);
	Ui()->DoLabel(&Label, Localize("a = Angle"), FontSize, TEXTALIGN_ML);
	RightView.HSplitTop(LineSize, &Label, &RightView);
	Ui()->DoLabel(&Label, Localize("p = Ping"), FontSize, TEXTALIGN_ML);
	RightView.HSplitTop(LineSize, &Label, &RightView);
	Ui()->DoLabel(&Label, Localize("d = Prediction"), FontSize, TEXTALIGN_ML);
	RightView.HSplitTop(LineSize, &Label, &RightView);
	Ui()->DoLabel(&Label, Localize("c = Position"), FontSize, TEXTALIGN_ML);
	RightView.HSplitTop(LineSize, &Label, &RightView);
	Ui()->DoLabel(&Label, Localize("l = Local Time"), FontSize, TEXTALIGN_ML);
	RightView.HSplitTop(LineSize, &Label, &RightView);
	Ui()->DoLabel(&Label, Localize("r = Race Time"), FontSize, TEXTALIGN_ML);
	RightView.HSplitTop(LineSize, &Label, &RightView);
	Ui()->DoLabel(&Label, Localize("f = FPS"), FontSize, TEXTALIGN_ML);
	RightView.HSplitTop(LineSize, &Label, &RightView);
	Ui()->DoLabel(&Label, Localize("v = Velocity"), FontSize, TEXTALIGN_ML);
	RightView.HSplitTop(LineSize, &Label, &RightView);
	Ui()->DoLabel(&Label, Localize("z = Zoom"), FontSize, TEXTALIGN_ML);
	RightView.HSplitTop(LineSize, &Label, &RightView);
	Ui()->DoLabel(&Label, Localize("_ or \' \' = Space"), FontSize, TEXTALIGN_ML);
	static int s_SelectedItem = -1;
	static int s_TypeSelectedOld = -1;

	CUIRect StatusScheme, StatusButtons, ItemLabel;
	static CButtonContainer s_ApplyButton, s_AddButton, s_RemoveButton;
	StatusBar.HSplitBottom(LineSize + MarginSmall, &StatusBar, &StatusScheme);
	StatusBar.HSplitTop(LineSize + MarginSmall, &ItemLabel, &StatusBar);
	StatusScheme.HSplitTop(MarginSmall, nullptr, &StatusScheme);

	if(s_TypeSelectedOld >= 0)
		Ui()->DoLabel(&ItemLabel, GameClient()->m_StatusBar.m_StatusItemTypes[s_TypeSelectedOld].m_aDesc, FontSize, TEXTALIGN_ML);

	StatusScheme.VSplitMid(&StatusButtons, &StatusScheme, MarginSmall);
	StatusScheme.VSplitMid(&Label, &StatusScheme, MarginSmall);
	StatusScheme.VSplitMid(&StatusScheme, &Button, MarginSmall);
	if(DoButton_Menu(&s_ApplyButton, Localize("Apply"), 0, &Button))
	{
		GameClient()->m_StatusBar.ApplyStatusBarScheme(g_Config.m_ClStatusBarScheme);
		GameClient()->m_StatusBar.UpdateStatusBarScheme(g_Config.m_ClStatusBarScheme);
		s_SelectedItem = -1;
	}
	Ui()->DoLabel(&Label, Localize("Status Scheme:"), FontSize, TEXTALIGN_MR);
	static CLineInput s_StatusScheme(g_Config.m_ClStatusBarScheme, sizeof(g_Config.m_ClStatusBarScheme));
	s_StatusScheme.SetEmptyText("");
	Ui()->DoEditBox(&s_StatusScheme, &StatusScheme, EditBoxFontSize);

	static std::vector<const char *> s_DropDownNames = {};
	for(int i = 0; i < (int)GameClient()->m_StatusBar.m_StatusItemTypes.size(); ++i)
		if(s_DropDownNames.size() != GameClient()->m_StatusBar.m_StatusItemTypes.size())
			s_DropDownNames.push_back(GameClient()->m_StatusBar.m_StatusItemTypes[i].m_aName);

	static CUi::SDropDownState s_DropDownState;
	static CScrollRegion s_DropDownScrollRegion;
	s_DropDownState.m_SelectionPopupContext.m_pScrollRegion = &s_DropDownScrollRegion;
	CUIRect DropDownRect;

	StatusButtons.VSplitMid(&DropDownRect, &StatusButtons, MarginSmall);
	const int TypeSelectedNew = Ui()->DoDropDown(&DropDownRect, s_TypeSelectedOld, s_DropDownNames.data(), s_DropDownNames.size(), s_DropDownState);
	if(s_TypeSelectedOld != TypeSelectedNew)
	{
		s_TypeSelectedOld = TypeSelectedNew;
		if(s_SelectedItem >= 0)
		{
			GameClient()->m_StatusBar.m_StatusBarItems[s_SelectedItem] = &GameClient()->m_StatusBar.m_StatusItemTypes[s_TypeSelectedOld];
			GameClient()->m_StatusBar.UpdateStatusBarScheme(g_Config.m_ClStatusBarScheme);
		}
	}
	CUIRect ButtonL, ButtonR;
	StatusButtons.VSplitMid(&ButtonL, &ButtonR, MarginSmall);
	if(DoButton_Menu(&s_AddButton, Localize("Add Item"), 0, &ButtonL) && s_TypeSelectedOld >= 0)
	{
		GameClient()->m_StatusBar.m_StatusBarItems.push_back(&GameClient()->m_StatusBar.m_StatusItemTypes[s_TypeSelectedOld]);
		GameClient()->m_StatusBar.UpdateStatusBarScheme(g_Config.m_ClStatusBarScheme);
		s_SelectedItem = (int)GameClient()->m_StatusBar.m_StatusBarItems.size() - 1;
	}
	if(DoButton_Menu(&s_RemoveButton, Localize("Remove Item"), 0, &ButtonR) && s_SelectedItem >= 0)
	{
		GameClient()->m_StatusBar.m_StatusBarItems.erase(GameClient()->m_StatusBar.m_StatusBarItems.begin() + s_SelectedItem);
		GameClient()->m_StatusBar.UpdateStatusBarScheme(g_Config.m_ClStatusBarScheme);
		s_SelectedItem = -1;
	}

	// color_cast<ColorRGBA>(ColorHSLA(g_Config.m_ClStatusBarColor)).WithAlpha(0.5f)
	StatusBar.Draw(ColorRGBA(0, 0, 0, 0.5f), IGraphics::CORNER_ALL, 5.0f);
	int ItemCount = GameClient()->m_StatusBar.m_StatusBarItems.size();
	float AvailableWidth = StatusBar.w;
	// AvailableWidth -= (ItemCount - 1) * MarginSmall;
	AvailableWidth -= MarginSmall;
	StatusBar.VSplitLeft(MarginExtraSmall, nullptr, &StatusBar);
	float ItemWidth = AvailableWidth / (float)ItemCount;
	CUIRect StatusItemButton;
	static std::vector<CButtonContainer *> s_pItemButtons;
	static std::vector<CButtonContainer> s_ItemButtons;
	static vec2 s_ActivePos = vec2(0, 0);
	struct SSwapItem
	{
		vec2 InitialPosition = vec2(0, 0);
		float Duration = 0.0f;
	};

	static std::vector<SSwapItem> s_ItemSwaps;

	if((int)s_ItemButtons.size() != ItemCount)
	{
		s_ItemSwaps.resize(ItemCount);
		s_pItemButtons.resize(ItemCount);
		s_ItemButtons.resize(ItemCount);
		for(int i = 0; i < ItemCount; ++i)
		{
			s_pItemButtons[i] = &s_ItemButtons[i];
		}
	}
	bool StatusItemActive = false;
	int HotStatusIndex = 0;
	for(int i = 0; i < ItemCount; ++i)
	{
		if(Ui()->ActiveItem() == s_pItemButtons[i])
		{
			StatusItemActive = true;
			HotStatusIndex = i;
		}
	}

	for(int i = 0; i < ItemCount; ++i)
	{
		// if(i > 0)
		//	StatusBar.VSplitLeft(MarginSmall, nullptr, &StatusBar);
		StatusBar.VSplitLeft(ItemWidth, &StatusItemButton, &StatusBar);
		StatusItemButton.HMargin(MarginSmall, &StatusItemButton);
		StatusItemButton.VMargin(MarginExtraSmall, &StatusItemButton);
		CStatusItem *StatusItem = GameClient()->m_StatusBar.m_StatusBarItems[i];
		ColorRGBA Col = ColorRGBA(1.0f, 1.0f, 1.0f, 0.5f);
		if(s_SelectedItem == i)
			Col = ColorRGBA(1.0f, 0.35f, 0.35f, 0.75f);
		CUIRect TempItemButton = StatusItemButton;
		TempItemButton.y = 0, TempItemButton.h = 10000.0f;
		if(StatusItemActive && Ui()->ActiveItem() != s_pItemButtons[i] && Ui()->MouseInside(&TempItemButton))
		{
			std::swap(s_pItemButtons[i], s_pItemButtons[HotStatusIndex]);
			std::swap(GameClient()->m_StatusBar.m_StatusBarItems[i], GameClient()->m_StatusBar.m_StatusBarItems[HotStatusIndex]);
			s_SelectedItem = -2;
			s_ItemSwaps[HotStatusIndex].InitialPosition = vec2(StatusItemButton.x, StatusItemButton.y);
			s_ItemSwaps[HotStatusIndex].Duration = 0.15f;
			s_ItemSwaps[i].InitialPosition = vec2(s_ActivePos.x, s_ActivePos.y);
			s_ItemSwaps[i].Duration = 0.15f;
			GameClient()->m_StatusBar.UpdateStatusBarScheme(g_Config.m_ClStatusBarScheme);
		}
		TempItemButton = StatusItemButton;
		s_ItemSwaps[i].Duration = std::max(0.0f, s_ItemSwaps[i].Duration - Client()->RenderFrameTime());
		if(s_ItemSwaps[i].Duration > 0.0f)
		{
			float Progress = std::pow(2.0, -5.0 * (1.0 - s_ItemSwaps[i].Duration / 0.15f));
			TempItemButton.x = mix(TempItemButton.x, s_ItemSwaps[i].InitialPosition.x, Progress);
		}
		if(DoButtonLineSize_Menu(s_pItemButtons[i], StatusItem->m_aDisplayName, 0, &TempItemButton, LineSize, false, 0, IGraphics::CORNER_ALL, 5.0f, 0.0f, Col))
		{
			if(s_SelectedItem == -2)
				s_SelectedItem++;
			else if(s_SelectedItem != i)
			{
				s_SelectedItem = i;
				for(int t = 0; t < (int)GameClient()->m_StatusBar.m_StatusItemTypes.size(); ++t)
					if(str_comp(GameClient()->m_StatusBar.m_StatusItemTypes[t].m_aName, StatusItem->m_aName) == 0)
						s_TypeSelectedOld = t;
			}
			else
			{
				s_SelectedItem = -1;
				s_TypeSelectedOld = -1;
			}
		}
		if(Ui()->ActiveItem() == s_pItemButtons[i])
			s_ActivePos = vec2(StatusItemButton.x, StatusItemButton.y);
	}
	if(!StatusItemActive)
		s_SelectedItem = std::max(-1, s_SelectedItem);
}

void CMenus::RenderSettingsBindWheel(CUIRect MainView)
{
	CUIRect LeftView, RightView, Button, Label;

	MainView.HSplitTop(MarginBetweenSections, nullptr, &MainView);
	MainView.VSplitLeft(MainView.w / 2.1f, &LeftView, &RightView);

	const float Radius = minimum(RightView.w, RightView.h) / 2.0f;
	vec2 Pos{RightView.x + RightView.w / 2.0f, RightView.y + RightView.h / 2.0f};
	// Draw Circle
	Graphics()->TextureClear();
	Graphics()->QuadsBegin();
	Graphics()->SetColor(0.0f, 0.0f, 0.0f, 0.3f);
	Graphics()->DrawCircle(Pos.x, Pos.y, Radius, 64);
	Graphics()->QuadsEnd();

	static char s_aBindName[BINDWHEEL_MAX_NAME];
	static char s_aBindCommand[BINDWHEEL_MAX_CMD];

	static int s_SelectedBindIndex = -1;
	int HoveringIndex = -1;

	float MouseDist = distance(Pos, Ui()->MousePos());
	if(GameClient()->m_Bindwheel.m_vBinds.empty()) // A-Client -> Fixes a Crash
	{
		TextRender()->Text(Pos.x - 30.0f, Pos.y - 10.0f, 20.0f, "Empty");
	}
	else if(MouseDist < Radius && MouseDist > Radius * 0.25f)
	{
		int SegmentCount = GameClient()->m_Bindwheel.m_vBinds.size();
		float SegmentAngle = 2 * pi / SegmentCount;

		float HoveringAngle = angle(Ui()->MousePos() - Pos) + SegmentAngle / 2;
		if(HoveringAngle < 0.0f)
			HoveringAngle += 2.0f * pi;

		HoveringIndex = (int)(HoveringAngle / (2 * pi) * SegmentCount);
		if(Ui()->MouseButtonClicked(0))
		{
			s_SelectedBindIndex = HoveringIndex;
			str_copy(s_aBindName, GameClient()->m_Bindwheel.m_vBinds[HoveringIndex].m_aName);
			str_copy(s_aBindCommand, GameClient()->m_Bindwheel.m_vBinds[HoveringIndex].m_aCommand);
		}
		else if(Ui()->MouseButtonClicked(1) && s_SelectedBindIndex >= 0 && HoveringIndex >= 0 && HoveringIndex != s_SelectedBindIndex)
		{
			CBindWheel::SBind BindA = GameClient()->m_Bindwheel.m_vBinds[s_SelectedBindIndex];
			CBindWheel::SBind BindB = GameClient()->m_Bindwheel.m_vBinds[HoveringIndex];
			str_copy(GameClient()->m_Bindwheel.m_vBinds[s_SelectedBindIndex].m_aName, BindB.m_aName);
			str_copy(GameClient()->m_Bindwheel.m_vBinds[s_SelectedBindIndex].m_aCommand, BindB.m_aCommand);
			str_copy(GameClient()->m_Bindwheel.m_vBinds[HoveringIndex].m_aName, BindA.m_aName);
			str_copy(GameClient()->m_Bindwheel.m_vBinds[HoveringIndex].m_aCommand, BindA.m_aCommand);
		}
		else if(Ui()->MouseButtonClicked(2))
		{
			s_SelectedBindIndex = HoveringIndex;
		}
	}
	else if(MouseDist < Radius && Ui()->MouseButtonClicked(0))
	{
		s_SelectedBindIndex = -1;
		str_copy(s_aBindName, "");
		str_copy(s_aBindCommand, "");
	}

	const float Theta = pi * 2.0f / GameClient()->m_Bindwheel.m_vBinds.size();
	for(int i = 0; i < static_cast<int>(GameClient()->m_Bindwheel.m_vBinds.size()); i++)
	{
		float FontSizes = 12.0f;
		if(i == s_SelectedBindIndex)
		{
			FontSizes = 20.0f;
			TextRender()->TextColor(ColorRGBA(0.5f, 1.0f, 0.75f, 1.0f));
		}
		else if(i == HoveringIndex)
			FontSizes = 14.0f;

		const CBindWheel::SBind Bind = GameClient()->m_Bindwheel.m_vBinds[i];
		const float Angle = Theta * i;
		vec2 TextPos = direction(Angle);
		TextPos *= Radius * 0.75f;

		float Width = TextRender()->TextWidth(FontSizes, Bind.m_aName);
		TextPos += Pos;
		TextPos.x -= Width / 2.0f;
		TextRender()->Text(TextPos.x, TextPos.y, FontSizes, Bind.m_aName);
		TextRender()->TextColor(TextRender()->DefaultTextColor());
	}

	LeftView.HSplitTop(LineSize, &Button, &LeftView);
	Button.VSplitLeft(100.0f, &Label, &Button);
	Ui()->DoLabel(&Label, Localize("Name:"), 14.0f, TEXTALIGN_ML);
	static CLineInput s_NameInput;
	s_NameInput.SetBuffer(s_aBindName, sizeof(s_aBindName));
	s_NameInput.SetEmptyText("Name");
	Ui()->DoEditBox(&s_NameInput, &Button, 12.0f);

	LeftView.HSplitTop(MarginSmall, nullptr, &LeftView);
	LeftView.HSplitTop(LineSize, &Button, &LeftView);
	Button.VSplitLeft(100.0f, &Label, &Button);
	Ui()->DoLabel(&Label, Localize("Command:"), 14.0f, TEXTALIGN_ML);
	static CLineInput s_BindInput;
	s_BindInput.SetBuffer(s_aBindCommand, sizeof(s_aBindCommand));
	s_BindInput.SetEmptyText(Localize("Command"));
	Ui()->DoEditBox(&s_BindInput, &Button, 12.0f);

	static CButtonContainer s_AddButton, s_RemoveButton, s_OverrideButton;

	LeftView.HSplitTop(MarginSmall, nullptr, &LeftView);
	LeftView.HSplitTop(LineSize, &Button, &LeftView);
	if(DoButton_Menu(&s_OverrideButton, Localize("Override Selected"), 0, &Button) && s_SelectedBindIndex >= 0)
	{
		CBindWheel::SBind TempBind;
		if(str_length(s_aBindName) == 0)
			str_copy(TempBind.m_aName, "*");
		else
			str_copy(TempBind.m_aName, s_aBindName);

		str_copy(GameClient()->m_Bindwheel.m_vBinds[s_SelectedBindIndex].m_aName, TempBind.m_aName);
		str_copy(GameClient()->m_Bindwheel.m_vBinds[s_SelectedBindIndex].m_aCommand, s_aBindCommand);
	}
	LeftView.HSplitTop(MarginSmall, nullptr, &LeftView);
	LeftView.HSplitTop(LineSize, &Button, &LeftView);
	CUIRect ButtonAdd, ButtonRemove;
	Button.VSplitMid(&ButtonRemove, &ButtonAdd, MarginSmall);
	if(DoButton_Menu(&s_AddButton, Localize("Add Bind"), 0, &ButtonAdd))
	{
		CBindWheel::SBind TempBind;
		if(str_length(s_aBindName) == 0)
			str_copy(TempBind.m_aName, "*");
		else
			str_copy(TempBind.m_aName, s_aBindName);

		GameClient()->m_Bindwheel.AddBind(TempBind.m_aName, s_aBindCommand);
		s_SelectedBindIndex = static_cast<int>(GameClient()->m_Bindwheel.m_vBinds.size()) - 1;
	}
	if(DoButton_Menu(&s_RemoveButton, Localize("Remove Bind"), 0, &ButtonRemove) && s_SelectedBindIndex >= 0)
	{
		GameClient()->m_Bindwheel.RemoveBind(s_SelectedBindIndex);
		s_SelectedBindIndex = -1;
	}

	LeftView.HSplitTop(MarginSmall, nullptr, &LeftView);
	LeftView.HSplitTop(LineSize, &Label, &LeftView);
	Ui()->DoLabel(&Label, Localize("Use left mouse to select"), 14.0f, TEXTALIGN_ML);
	LeftView.HSplitTop(LineSize, &Label, &LeftView);
	Ui()->DoLabel(&Label, Localize("Use right mouse to swap with selected"), 14.0f, TEXTALIGN_ML);
	LeftView.HSplitTop(LineSize, &Label, &LeftView);
	Ui()->DoLabel(&Label, Localize("Use middle mouse select without copy"), 14.0f, TEXTALIGN_ML);

	// Do Settings Key
	CKeyInfo Key = CKeyInfo{"Bind Wheel Key", "+bindwheel", 0, 0};
	for(int Mod = 0; Mod < CBinds::MODIFIER_COMBINATION_COUNT; Mod++)
	{
		for(int KeyId = 0; KeyId < KEY_LAST; KeyId++)
		{
			const char *pBind = m_pClient->m_Binds.Get(KeyId, Mod);
			if(!pBind[0])
				continue;

			if(str_comp(pBind, Key.m_pCommand) == 0)
			{
				Key.m_KeyId = KeyId;
				Key.m_ModifierCombination = Mod;
				break;
			}
		}
	}

	CUIRect KeyLabel;
	LeftView.HSplitBottom(LineSize, &LeftView, &Button);
	Button.VSplitLeft(120.0f, &KeyLabel, &Button);
	Button.VSplitLeft(100.0f, &Button, nullptr);
	char aBuf[64];
	str_format(aBuf, sizeof(aBuf), "%s:", Localize((const char *)Key.m_pName));

	Ui()->DoLabel(&KeyLabel, aBuf, 14.0f, TEXTALIGN_ML);
	int OldId = Key.m_KeyId, OldModifierCombination = Key.m_ModifierCombination, NewModifierCombination;
	int NewId = DoKeyReader((void *)&Key.m_pName, &Button, OldId, OldModifierCombination, &NewModifierCombination);
	if(NewId != OldId || NewModifierCombination != OldModifierCombination)
	{
		if(OldId != 0 || NewId == 0)
			m_pClient->m_Binds.Bind(OldId, "", false, OldModifierCombination);
		if(NewId != 0)
			m_pClient->m_Binds.Bind(NewId, Key.m_pCommand, false, NewModifierCombination);
	}
	LeftView.HSplitBottom(LineSize, &LeftView, &Button);

	DoButton_CheckBoxAutoVMarginAndSet(&g_Config.m_ClResetBindWheelMouse, Localize("Reset position of mouse when opening bindwheel"), &g_Config.m_ClResetBindWheelMouse, &Button, LineSize);

	CUIRect CopyRight;
	MainView.HSplitBottom(20.0f, 0, &CopyRight);
	CopyRight.VSplitLeft(225.0f, &CopyRight, &CopyRight);
	Ui()->DoLabel(&CopyRight, "© Tater", 14.0f, TEXTALIGN_ML);
}