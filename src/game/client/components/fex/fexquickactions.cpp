#include "fexquickactions.h"

#include <game/client/gameclient.h>
#include <game/generated/client_data.h>
#include <game/generated/protocol.h>

void CActions::LoadQuickActionsFromFile()
{
	m_pStorage = Kernel()->RequestInterface<IStorage>();
	IOHANDLE File = m_pStorage->OpenFile(ACTIONS_FILE, IOFLAG_READ, IStorage::TYPE_ALL);
	if(File)
	{
		io_close(File);
		Console()->ExecuteFile(ACTIONS_FILE);
	}
}

void CActions::OnReset()
{
    m_SpectatorActionMenuActive = false;
    m_SpectatorActionPage = 0;
    m_SpectatorActionMenuAlpha = 0.0f;
    m_SpectatorActionMenuShowTime = 0;
}

void CActions::OnConsoleInit()
{
    IConfigManager *pConfigManager = Kernel()->RequestInterface<IConfigManager>();
    if(pConfigManager)
        pConfigManager->RegisterFXCallback(ConfigSaveCallback, this);

    Console()->Register("add_action_page", "s[page_name]", CFGFLAG_CLIENT, ConAddPage, this, "Adds a new quick actions page");
    Console()->Register("remove_action_page", "i[page_index]", CFGFLAG_CLIENT, ConRemovePage, this, "Removes a quick actions page");
    Console()->Register("add_action", "i[page_index] s[action_name] s[action_command]", CFGFLAG_CLIENT, ConAddActionToPage, this, "Adds an action to a quick actions page");
    Console()->Register("remove_action", "i[page_index] i[action_index]", CFGFLAG_CLIENT, ConRemoveActionFromPage, this, "Removes an action from a quick actions page");

    LoadQuickActionsFromFile();
    OnReset();
}

void CActions::InitDefaultPages()
{
    const char* defaultPages[3] = {"Player", "Clan", "General"};
    const char* defaultActions[3][3] = {
        {"War", "Team", "Helper"},
        {"ClanWar", "ClanTeam", "ClanHelper"},
        {"Vote", "Friend", "Mute"}
    };
    const char* defaultCommands[3][3] = {
        {"spec_war {specid}", "spec_team {specid}", "spec_helper {specid}"},
        {"spec_clanwar {specid}", "spec_clanteam {specid}", "spec_clanhelper {specid}"},
        {"spec_vote {specid}", "spec_friend {specid}", "spec_mute {specid}"}
    };

    for(int i = 0; i < 3; i++)
    {
        str_copy(m_aPages[i].m_aName, defaultPages[i]);
        m_aPages[i].m_NumActions = 3;

        for(int j = 0; j < 3; j++)
        {
            str_copy(m_aPages[i].m_aActions[j].m_aName, defaultActions[i][j]);
            str_copy(m_aPages[i].m_aActions[j].m_aCommand, defaultCommands[i][j]);
        }
    }

    m_NumPages = 3;
}

bool CActions::AddPage(const char *pPageName)
{
    if(m_NumPages < 3)
        m_NumPages = 3;

    if(m_NumPages >= MAX_PAGES || !pPageName || str_length(pPageName) == 0)
        return false;

    SPage &NewPage = m_aPages[m_NumPages];
    str_copy(NewPage.m_aName, pPageName);
    NewPage.m_NumActions = 0;

    m_NumPages++;
    return true;
}

bool CActions::RemovePage(int PageIndex)
{
    if(PageIndex < 3 || PageIndex >= m_NumPages)
        return false;

    for(int i = PageIndex; i < m_NumPages - 1; i++)
    {
        m_aPages[i] = m_aPages[i + 1];
    }
    m_NumPages--;
    return true;
}

bool CActions::AddActionToPage(int PageIndex, const char *pActionName, const char *pActionCommand)
{
    if(PageIndex < 3 || PageIndex >= m_NumPages || m_aPages[PageIndex].m_NumActions >= MAX_ACTIONS_PER_PAGE)
        return false;

    SAction &Action = m_aPages[PageIndex].m_aActions[m_aPages[PageIndex].m_NumActions];
    str_copy(Action.m_aName, pActionName);
    str_copy(Action.m_aCommand, pActionCommand);

    m_aPages[PageIndex].m_NumActions++;
    return true;
}

bool CActions::RemoveActionFromPage(int PageIndex, int ActionIndex)
{
    if(PageIndex < 3 || PageIndex >= m_NumPages || ActionIndex < 0 || ActionIndex >= m_aPages[PageIndex].m_NumActions)
        return false;

    for(int i = ActionIndex; i < m_aPages[PageIndex].m_NumActions - 1; i++)
    {
        m_aPages[PageIndex].m_aActions[i] = m_aPages[PageIndex].m_aActions[i + 1];
    }
    m_aPages[PageIndex].m_NumActions--;
    return true;
}


void CActions::ConAddPage(IConsole::IResult *pResult, void *pUserData)
{
    CActions *pThis = static_cast<CActions *>(pUserData);
    const char *pPageName = pResult->GetString(0);
    pThis->AddPage(pPageName);
}

void CActions::ConRemovePage(IConsole::IResult *pResult, void *pUserData)
{
    CActions *pThis = static_cast<CActions *>(pUserData);
    int PageIndex = pResult->GetInteger(0);
    pThis->RemovePage(PageIndex);
}

void CActions::ConAddActionToPage(IConsole::IResult *pResult, void *pUserData)
{
    CActions *pThis = static_cast<CActions *>(pUserData);
    int PageIndex = pResult->GetInteger(0);
    const char *pActionName = pResult->GetString(1);
    const char *pActionCommand = pResult->GetString(2);
    pThis->AddActionToPage(PageIndex, pActionName, pActionCommand);
}

void CActions::ConRemoveActionFromPage(IConsole::IResult *pResult, void *pUserData)
{
    CActions *pThis = static_cast<CActions *>(pUserData);
    int PageIndex = pResult->GetInteger(0);
    int ActionIndex = pResult->GetInteger(1);
    pThis->RemoveActionFromPage(PageIndex, ActionIndex);
}


void CActions::RenderSpectatorActionMenu()
{
    if(!g_Config.m_ClSpectatorActionHud || !m_pClient->m_Snap.m_SpecInfo.m_Active || m_pClient->m_Snap.m_SpecInfo.m_SpectatorId == SPEC_FREEVIEW)
        return;

    const int SpectatorId = m_pClient->m_Snap.m_SpecInfo.m_SpectatorId;
    const char *pName = m_pClient->m_aClients[SpectatorId].m_aName;
    const char *pClan = m_pClient->m_aClients[SpectatorId].m_aClan;

    if(m_SpectatorActionPage < 0 || m_SpectatorActionPage >= m_NumPages)
        m_SpectatorActionPage = 0;

    if(m_SpectatorActionPage == 1 && (!pClan || pClan[0] == '\0'))
        m_SpectatorActionPage = 0;

    static float AnimationProgress = 1.0f;
    static float ScaleFactor = 1.0f;
    static float AlphaFactor = 1.0f;

    float TimeSinceTransition = (time_get() - m_SpectatorActionMenuShowTime) / (float)time_freq();
    float TimeSinceNoTransition = (time_get() - m_SpectatorActionMenuNotShowTime) / (float)time_freq();

    if(m_SpectatorActionMenuActive)
        AnimationProgress = clamp(TimeSinceTransition / 0.5f, 0.0f, 1.0f);
    else if(AnimationProgress > 0.0f)
        AnimationProgress = clamp(1.0f - TimeSinceNoTransition / 0.5f, 0.0f, 1.0f);

    if(m_SpectatorActionMenuClosing)
    {
        AnimationProgress = clamp(1.0f - TimeSinceNoTransition / 0.5f, 0.0f, 1.0f);
        if(AnimationProgress <= 0.0f)
        {
            m_SpectatorActionMenuActive = false;
            m_SpectatorActionMenuClosing = false;
        }
    }

    ScaleFactor = (g_Config.m_ClSpectatorActionAnimation == 2) ? AnimationProgress : 1.0f;
    AlphaFactor = (g_Config.m_ClSpectatorActionAnimation == 1) ? AnimationProgress : 1.0f;

    if(m_SpectatorActionMenuActive)
    {
        const float ButtonSize = 40.0f;
        float x = m_pClient->m_Hud.m_Width / 2 - ButtonSize / 2;
        float y = m_pClient->m_Hud.m_Height / 2 - ButtonSize / 2;
        vec2 Center = vec2(x + ButtonSize / 2, y + ButtonSize / 2);

        IGraphics::CTextureHandle Circle;
        Graphics()->TextureSet(Circle);
        Graphics()->BlendNormal();
        Graphics()->QuadsBegin();
        Graphics()->SetColor(0.0f, 0.0f, 0.0f, 0.3f * AlphaFactor);
        Graphics()->DrawCircle(Center.x, Center.y, 80.0f * ScaleFactor, 32);
        Graphics()->QuadsEnd();

        SPage *pPage = &m_aPages[m_SpectatorActionPage];
        int NumActions = pPage->m_NumActions;
        if(NumActions <= 0)
            NumActions = 3;

        const float Radius = 80.0f;
        const float InnerRadius = 30.0f;
        for(int i = 0; i < NumActions; i++)
        {
            float Angle = (i * 2.0f * pi / NumActions) - pi / 2;
            float NextAngle = ((i + 1) * 2.0f * pi / NumActions) - pi / 2;

            vec2 Pos1 = Center + vec2(cos(Angle) * InnerRadius * ScaleFactor, sin(Angle) * InnerRadius * ScaleFactor);
            vec2 Pos2 = Center + vec2(cos(Angle) * Radius * ScaleFactor, sin(Angle) * Radius * ScaleFactor);
            vec2 Pos3 = Center + vec2(cos(NextAngle) * Radius * ScaleFactor, sin(NextAngle) * Radius * ScaleFactor);
            vec2 Pos4 = Center + vec2(cos(NextAngle) * InnerRadius * ScaleFactor, sin(NextAngle) * InnerRadius * ScaleFactor);

            ColorRGBA Color;
            if(m_SpectatorActionPage == 0)
            {
                switch(i)
                {
                    case 0: Color = GameClient()->m_WarList.m_WarTypes[1]->m_Color; break;
                    case 1: Color = GameClient()->m_WarList.m_WarTypes[2]->m_Color; break;
                    case 2: Color = GameClient()->m_WarList.m_WarTypes[3]->m_Color; break;
                    default: Color = ColorRGBA(0.5f, 0.5f, 0.5f, 0.5f); break;
                }
            }
            else if(m_SpectatorActionPage == 1)
            {
                if(i == 0)
                    Color = ColorRGBA(0.0f, 0.7f, 1.0f, 0.5f);
                else if(i == 1)
                    Color = ColorRGBA(0.0f, 1.0f, 0.5f, 0.5f);
                else if(i == 2)
                    Color = ColorRGBA(1.0f, 0.5f, 0.0f, 0.5f);
                else
                    Color = ColorRGBA(0.5f, 0.5f, 0.5f, 0.5f);
            }
            else
            {
                Color = ColorRGBA(((i + 0) % 3) / 3.0f + 0.3f,
                                  ((i + 1) % 3) / 3.0f + 0.3f,
                                  ((i + 2) % 3) / 3.0f + 0.3f, 0.5f);
            }
            Color.a = 0.5f;

            IGraphics::CTextureHandle Sector;
            Graphics()->TextureSet(Sector);
            Graphics()->QuadsBegin();
            Graphics()->SetColor(Color.r, Color.g, Color.b, Color.a * AlphaFactor);
            IGraphics::CFreeformItem Freeform(
                Pos1.x, Pos1.y,
                Pos2.x, Pos2.y,
                Pos3.x, Pos3.y,
                Pos4.x, Pos4.y);
            Graphics()->QuadsDrawFreeform(&Freeform, 1);
            Graphics()->QuadsEnd();

            vec2 IconPos = Center + vec2(
                cos(Angle + (pi / NumActions)) * ((Radius + InnerRadius) / 2 * ScaleFactor),
                sin(Angle + (pi / NumActions)) * ((Radius + InnerRadius) / 2 * ScaleFactor)
            );

            const char *pActionText = pPage->m_aActions[i].m_aName;
            if(!pActionText || pActionText[0] == '\0')
            {
                if(m_SpectatorActionPage == 0)
                    pActionText = i == 0 ? "War" : i == 1 ? "Team" : "Helper";
                else if(m_SpectatorActionPage == 1)
                    pActionText = i == 0 ? "ClanWar" : i == 1 ? "ClanTeam" : "ClanHelper";
                else if(m_SpectatorActionPage == 2)
                    pActionText = i == 0 ? "Vote" : i == 1 ? (GameClient()->Friends()->IsFriend(pName, pClan, true) ? "Remove Friend" : "Friend") : (m_pClient->m_aClients[SpectatorId].m_IsMute ? "Remove Mute" : "Mute");
                else
                    pActionText = "";
            }

            if(g_Config.m_ClSpectatorActionIcons && strlen(pActionText) == 1)
            {
                IGraphics::CTextureHandle IconTexture;
                if(m_SpectatorActionPage == 0)
                {
                    switch(i)
                    {
                        case 0: IconTexture = g_pData->m_aImages[IMAGE_SWORD_ICON].m_Id; break;
                        case 1: IconTexture = g_pData->m_aImages[IMAGE_TEAM_ICON].m_Id; break;
                        case 2: IconTexture = g_pData->m_aImages[IMAGE_SWORD_ICON].m_Id; break;
                        default: IconTexture = g_pData->m_aImages[IMAGE_SWORD_ICON].m_Id; break;
                    }
                    Graphics()->TextureSet(IconTexture);
                    Graphics()->QuadsBegin();
                    Graphics()->SetColor(1.0f, 1.0f, 1.0f, 1.0f * AlphaFactor);
                    IGraphics::CQuadItem IconQuad(IconPos.x - 8, IconPos.y - 8, 16, 16);
                    Graphics()->QuadsDrawTL(&IconQuad, 1);
                    Graphics()->QuadsEnd();
                }
                else
                {
                    float TextWidth = TextRender()->TextWidth(12.0f, pActionText, -1, -1.0f);
                    TextRender()->TextColor(1.f, 1.f, 1.f, 1.f * AlphaFactor);
                    TextRender()->Text(IconPos.x - TextWidth / 2, IconPos.y - 6, 12.0f, pActionText, -1.0f);
                    TextRender()->TextColor(TextRender()->DefaultTextColor());
                }
            }
            else
            {
                float FontSize = 8.0f;
                float TextWidth = TextRender()->TextWidth(FontSize, pActionText, -1, -1.0f);
                TextRender()->TextColor(1.f, 1.f, 1.f, 1.f * AlphaFactor);
                TextRender()->Text(IconPos.x - TextWidth / 2, IconPos.y - 6, FontSize, pActionText, -1.0f);
                TextRender()->TextColor(TextRender()->DefaultTextColor());
            }
        }
        for(int i = 0; i < NumActions; i++)
        {
            float Angle = (i * 2.0f * pi / NumActions) - pi / 2;
            vec2 KeyPos = Center + vec2(cos(Angle) * (Radius + 10.0f), sin(Angle) * (Radius + 10.0f));

            ColorRGBA Color = ColorRGBA(0.0f, 0.0f, 0.0f, 0.2f * AlphaFactor);
            Graphics()->DrawRect(KeyPos.x - 8, KeyPos.y - 8, 16, 16, Color, IGraphics::CORNER_ALL, 5.f);

            const char *aKeys[] = {"F", "D", "A"};
            const char *pKeyText = aKeys[i % (sizeof(aKeys) / sizeof(aKeys[0]))];

            float KeyWidth = TextRender()->TextWidth(8.0f, pKeyText, -1, -1.0f);
            TextRender()->TextColor(1.f, 1.f, 1.f, 1.f * AlphaFactor);
            TextRender()->Text(KeyPos.x - KeyWidth / 2, KeyPos.y - 4, 8.0f, pKeyText, -1.0f);
            TextRender()->TextColor(TextRender()->DefaultTextColor());
        }

        const char *pCenterText = nullptr;

        if(m_SpectatorActionPage >= 0 && m_SpectatorActionPage < m_NumPages)
        {
            pCenterText = m_aPages[m_SpectatorActionPage].m_aName;
        }

        if(!pCenterText || pCenterText[0] == '\0')
        {
            pCenterText = (m_SpectatorActionPage == 0) ? "Player" : (m_SpectatorActionPage == 1) ? "Clan" : (m_SpectatorActionPage == 2) ? "General" : "Actions";
        }

        // Render the text
        float CenterTextWidth = TextRender()->TextWidth(10.0f * ScaleFactor, pCenterText, -1, -1.0f);
        TextRender()->TextColor(1.f, 1.f, 1.f, 1.f * AlphaFactor);
        TextRender()->Text(Center.x - CenterTextWidth / 2, Center.y - 6 * ScaleFactor, 10.0f * ScaleFactor, pCenterText, -1.0f);
        TextRender()->TextColor(TextRender()->DefaultTextColor());
    }
}

void CActions::HandleSpectatorActionInput(int Key) 
{
    if(!m_SpectatorActionMenuActive)
        return;

    const int SpectatorId = m_pClient->m_Snap.m_SpecInfo.m_SpectatorId;
    if(SpectatorId < 0 || SpectatorId >= MAX_CLIENTS)
        return;

    const char *pName = m_pClient->m_aClients[SpectatorId].m_aName;
    const char *pClan = m_pClient->m_aClients[SpectatorId].m_aClan;

    const char *pActionType = "";
    ColorRGBA Color;
    bool IsAdd = true;

    if(Key == KEY_S)
    {
        if(m_SpectatorActionPage == 0 && !pClan[0]) m_SpectatorActionPage = 2;
        else
        {
            m_SpectatorActionPage = (m_SpectatorActionPage + 1) % m_NumPages;
            char abuf[6];
            str_format(abuf, sizeof(abuf), "%d", m_SpectatorActionPage);
            dbg_msg("changed page to", abuf);
        }
        return;
    }

    const int aSpectatorKeys[] = { KEY_F, KEY_D, KEY_A };

    if(m_SpectatorActionPage >= 2 && m_SpectatorActionPage < m_NumPages)
    {
        SPage &Page = m_aPages[m_SpectatorActionPage]; 
        for(int i = 0; i < Page.m_NumActions; ++i)
        {
            if(Key == aSpectatorKeys[i])
            {
                Console()->ExecuteLine(Page.m_aActions[i].m_aCommand);
            }
        }
    }

    else 
    {
        // Player actions page
        if(m_SpectatorActionPage == 0)
        {
            const char *pWarType = "";
            switch(Key)
            {
            case KEY_F: pWarType = "enemy"; break;
            case KEY_A: pWarType = "team"; break;
            case KEY_D: pWarType = "helper"; break;
            }

            if(GameClient()->m_WarList.IsInList(pName, "", pWarType))
            {
                GameClient()->m_WarList.RemoveWarEntry(pName, "");
                IsAdd = false;
            }
            else if(Key == KEY_F || Key == KEY_A || Key == KEY_D)
            {
                GameClient()->m_WarList.AddWarEntry(pName, "", "", pWarType);
            }
        }
        // Clan actions page 
        else if(m_SpectatorActionPage == 1 && pClan[0])
        {
            const char *pWarType = "";
            switch(Key)
            {
            case KEY_F: pWarType = "enemy"; break;
            case KEY_A: pWarType = "team"; break;
            case KEY_D: pWarType = "helper"; break;
            }

            if(GameClient()->m_WarList.IsInList("", pClan, pWarType))
            {
                GameClient()->m_WarList.RemoveWarEntry("", pClan);
                IsAdd = false;
            }
            else if(Key == KEY_F || Key == KEY_A || Key == KEY_D)
            {
                GameClient()->m_WarList.AddWarEntry("", pClan, "", pWarType);
            }
        }
        // Player management page
        else if(m_SpectatorActionPage == 2)
        {
            switch(Key)
            {
                case KEY_F:
                    if(GameClient()->Friends()->IsFriend(pName, pClan, true))
                    {
                        char Id[8];
                        str_format(Id, sizeof(Id), "%d", SpectatorId);
                        GameClient()->m_Voting.Callvote("kick", Id, g_Config.m_ClSpectatorActionVoteReason);;
                        pActionType = "Vote started";
                        Color = ColorRGBA(0.9f, 0.2f, 0.2f, 1.0f);
                    }
                    break;
                case KEY_D:
                    if(GameClient()->Friends()->IsFriend(pName, pClan, true))
                    {
                        GameClient()->Friends()->RemoveFriend(pName, pClan);
                        pActionType = "Removed Friend";
                        Color = ColorRGBA(0.9f, 0.2f, 0.2f, 1.0f);
                    }
                    else
                    {
                        GameClient()->Friends()->AddFriend(pName, pClan);
                        pActionType = "Friend";
                        Color = ColorRGBA(0.2f, 0.9f, 0.2f, 1.0f);
                    }
                    break;

                case KEY_A:
                {
                    const char *pMuteName = m_pClient->m_Fex.NameFromId(SpectatorId);
                    if(m_pClient->m_aClients[SpectatorId].m_IsMute)
                    {
                        m_pClient->m_WarList.DelMute(pMuteName);
                        pActionType = "Removed Mute";
                        Color = ColorRGBA(0.9f, 0.2f, 0.2f, 1.0f);
                    }
                    else
                    {
                        m_pClient->m_WarList.AddMute(pMuteName);
                        pActionType = "Mute";
                        Color = ColorRGBA(0.7f, 0.7f, 0.2f, 1.0f);
                    }
                    break;
                }
            }
        }

        // Show notification
        if(Key == KEY_F || Key == KEY_A || Key == KEY_D)
        {
            char aBuf[256];
            if(m_SpectatorActionPage == 0)
            {
                switch(Key)
                {
                case KEY_F: 
                    pActionType = "War";
                    Color = GameClient()->m_WarList.m_WarTypes[1]->m_Color;
                    break;
                case KEY_A:
                    pActionType = "Team";
                    Color = GameClient()->m_WarList.m_WarTypes[2]->m_Color;
                    break;
                case KEY_D:
                    pActionType = "Helper";
                    Color = GameClient()->m_WarList.m_WarTypes[3]->m_Color;
                    break;
                }
                str_format(aBuf, sizeof(aBuf), "%s %s %s list", IsAdd ? "Added" : "Removed", pName, pActionType);
            }
            else if(m_SpectatorActionPage == 1)
            {
                switch(Key)
                {
                case KEY_F:
                    pActionType = "ClanWar";
                    Color = GameClient()->m_WarList.m_WarTypes[1]->m_Color;
                    break;
                case KEY_A:
                    pActionType = "ClanTeam";
                    Color = GameClient()->m_WarList.m_WarTypes[2]->m_Color;
                    break;
                case KEY_D:
                    pActionType = "ClanHelper";
                    Color = GameClient()->m_WarList.m_WarTypes[3]->m_Color;
                    break;
                }
                str_format(aBuf, sizeof(aBuf), "%s clan '%s' %s list", IsAdd ? "Added" : "Removed", pClan, pActionType);
            }
            else
            {
                str_format(aBuf, sizeof(aBuf), "%s %s", pActionType, pName);
            }

            Color.a = 0.4f;
            m_pClient->m_Hud.ShowNotification(aBuf, 3.0f, 1.0f, Color, ColorRGBA(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }

	if(Key != KEY_S)
	{
    	m_SpectatorActionMenuActive = false;
		if(g_Config.m_ClSpectatorActionAnimation == 0)
		{
			return;
		}
		else
		{
			m_SpectatorActionMenuNotShowTime = time_get();
		}
	}
}

bool CActions::OnInput(const IInput::CEvent &Event)
{
    if(!g_Config.m_ClSpectatorActionHud || !m_pClient->m_Snap.m_SpecInfo.m_Active || m_pClient->m_Snap.m_SpecInfo.m_SpectatorId == SPEC_FREEVIEW)
    {
        return false;
    }

    if(Event.m_Flags & IInput::FLAG_PRESS)
    {
        if(Event.m_Key == KEY_W)
        {
            if(!m_SpectatorActionMenuActive)
            {
                m_SpectatorActionMenuActive = true;
                m_SpectatorActionMenuClosing = false;
                m_SpectatorActionMenuShowTime = time_get();
            }
            else
            {
                m_SpectatorActionMenuClosing = true;
				if(g_Config.m_ClSpectatorActionAnimation == 0)
				{
					return false;
				}
				else
				{
					m_SpectatorActionMenuNotShowTime = time_get();
				}
            }

            return true;
        }
        else if(m_SpectatorActionMenuActive && !m_SpectatorActionMenuClosing)
        {
            HandleSpectatorActionInput(Event.m_Key);
            return true;
        }
    }

    return false;
}


vec2 CActions::WorldToScreen(vec2 WorldPos)
{
    float aPoints[4];
    RenderTools()->MapScreenToWorld(
        m_pClient->m_Camera.m_Center.x,
        m_pClient->m_Camera.m_Center.y,
        100.0f,
        100.0f,
        100.0f,
        0,
        0,
        Graphics()->ScreenAspect(),
        1.0f,
        aPoints
    );
    Graphics()->MapScreen(aPoints[0], aPoints[1], aPoints[2], aPoints[3]);
    vec2 ScreenPos = WorldPos;
    Graphics()->MapScreen(0, 0, m_pClient->m_Hud.m_Width, m_pClient->m_Hud.m_Height);
    return ScreenPos;
}

void CActions::WriteLine(const char *pLine)
{
	if(!m_ActionsFile || io_write(m_ActionsFile, pLine, str_length(pLine)) != static_cast<unsigned>(str_length(pLine)) || !io_write_newline(m_ActionsFile))
		return;
}

void CActions::ConfigSaveCallback(IConfigManager *pConfigManager, void *pUserData)
{
    CActions *pThis = (CActions *)pUserData;
    bool Failed = false;
    pThis->m_ActionsFile = pThis->m_pStorage->OpenFile(ACTIONS_FILE, IOFLAG_WRITE, IStorage::TYPE_SAVE);
    
    if(!pThis->m_ActionsFile)
    {
        dbg_msg("config", "ERROR: opening %s failed", ACTIONS_FILE);
        return;
    }

    for(int i = 0; i < pThis->m_NumPages; ++i)
    {
        const SPage &Page = pThis->m_aPages[i];

        char aPageBuf[256];
        str_format(aPageBuf, sizeof(aPageBuf), "add_action_page \"%s\"", Page.m_aName);
        pThis->WriteLine(aPageBuf);

        for(int j = 0; j < Page.m_NumActions; ++j)
        {
            const SAction &Action = Page.m_aActions[j];

            char aActionBuf[1024];
            str_format(aActionBuf, sizeof(aActionBuf), "add_action \"%s\" \"%s\" \"%s\"",
                Page.m_aName, Action.m_aName, Action.m_aCommand);
            
            pThis->WriteLine(aActionBuf);
        }
    }

    if(io_sync(pThis->m_ActionsFile) != 0) Failed = true;
    if(io_close(pThis->m_ActionsFile) != 0) Failed = true;
    pThis->m_ActionsFile = {};

    if(Failed)
        dbg_msg("config", "ERROR: writing to %s failed", ACTIONS_FILE);
}
