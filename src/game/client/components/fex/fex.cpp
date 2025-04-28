#include <engine/client.h>
#include <engine/shared/config.h>
#include <engine/shared/protocol.h>
#include <engine/textrender.h>
#include <game/gamecore.h>
#include <game/client/components/chat.h>
#include <game/client/components/controls.h>
#include <game/client/gameclient.h>
#include <game/generated/protocol.h>
#include "fex.h"
#include <base/system.h>
#include <base/math.h>
#include <cmath>
#include <engine/serverbrowser.h>


void CFex::OnNewSnapshot()
{
	UpdateTempPlayers();
}

int CFex::IdWithName(const char *pName)
{
	int ClientId;

	for(ClientId = 0; ClientId < MAX_CLIENTS; ClientId++)
	{
		if(str_comp(pName, GameClient()->m_aClients[ClientId].m_aName) == 0)
		{
			return ClientId;
		}
	}
	return -1;
}

void CFex::TempWar(const char *pName)
{
	CTempEntry Entry(pName, "", "");
	str_copy(Entry.m_aTempWar, pName);

	char aBuf[128];
	str_format(aBuf, sizeof(aBuf), "Added \"%s\" to the Temp War List", pName);
	GameClient()->aMessage(aBuf);

	m_TempEntries.push_back(Entry);
	UnTempHelper(pName, true);
}

void CFex::UnTempWar(const char *pName, bool Silent)
{
	if(str_comp(pName, "") == 0)
		return;

	char aBuf[128];
	str_format(aBuf, sizeof(aBuf), "couldn't find \"%s\" on the Temp War List", pName);
	CTempEntry Entry("", "", pName);

	auto it = std::find(m_TempEntries.begin(), m_TempEntries.end(), Entry);
	if(it != m_TempEntries.end())
	{
		for(auto it2 = m_TempEntries.begin(); it2 != m_TempEntries.end();)
		{
			bool IsDuplicate = !str_comp(it2->m_aTempWar, pName);

			if(IsDuplicate)
				it2 = m_TempEntries.erase(it2);
			else
				++it2;

			if(!str_comp(it2->m_aTempWar, pName))
				str_format(aBuf, sizeof(aBuf), "Removed \"%s\" from the Temp War List", pName);
		}
	}
	if(!Silent)
		GameClient()->aMessage(aBuf);
}

void CFex::TempHelper(const char *pName)
{
	CTempEntry Entry("", pName, "");
	str_copy(Entry.m_aTempHelper, pName);

	char aBuf[128];
	str_format(aBuf, sizeof(aBuf), "Added \"%s\" to the Temp Helper List", pName);
	GameClient()->aMessage(aBuf);
	m_TempEntries.push_back(Entry);
	UnTempWar(pName, true);
}

void CFex::UnTempHelper(const char *pName, bool Silent)
{
	if(str_comp(pName, "") == 0)
		return;

	char aBuf[128];
	str_format(aBuf, sizeof(aBuf), "couldn't find \"%s\" on the Temp Helper List", pName);
	CTempEntry Entry("", "", pName);

	auto it = std::find(m_TempEntries.begin(), m_TempEntries.end(), Entry);
	if(it != m_TempEntries.end())
	{
		for(auto it2 = m_TempEntries.begin(); it2 != m_TempEntries.end();)
		{
			bool IsDuplicate = !str_comp(it2->m_aTempHelper, pName);

			if(IsDuplicate)
				it2 = m_TempEntries.erase(it2);
			else
				++it2;

			if(!str_comp(it2->m_aTempHelper, pName))
				str_format(aBuf, sizeof(aBuf), "Removed \"%s\" from the Temp Helper List", pName);
		}
	}
	if(!Silent)
		GameClient()->aMessage(aBuf);
}

void CFex::TempMute(const char *pName)
{
	CTempEntry Entry("", "", pName);
	str_copy(Entry.m_aTempMute, pName);

	char aBuf[128];
	str_format(aBuf, sizeof(aBuf), "Added \"%s\" to the Temp Mute List", pName);
	GameClient()->aMessage(aBuf);
	m_TempEntries.push_back(Entry);
}

void CFex::UnTempMute(const char *pName, bool Silent)
{
	if(str_comp(pName, "") == 0)
		return;

	char aBuf[128];
	str_format(aBuf, sizeof(aBuf), "couldn't find \"%s\" on the Temp Mute List", pName);
	CTempEntry Entry("", "", pName);

	auto it = std::find(m_TempEntries.begin(), m_TempEntries.end(), Entry);
	if(it != m_TempEntries.end())
	{
		for(auto it2 = m_TempEntries.begin(); it2 != m_TempEntries.end();)
		{
			bool IsDuplicate = !str_comp(it2->m_aTempMute, pName);

			if(IsDuplicate)
				it2 = m_TempEntries.erase(it2);
			else
				++it2;

			if(!str_comp(it2->m_aTempMute, pName))
				str_format(aBuf, sizeof(aBuf), "Removed \"%s\" from the Temp Mute List", pName);
		}
	}
	if(!Silent)
		GameClient()->aMessage(aBuf);
}

void CFex::RemoveWarEntryDuplicates(const char *pName)
{
	if(!str_comp(pName, ""))
		return;

	for(auto it = m_TempEntries.begin(); it != m_TempEntries.end();)
	{
		bool IsDuplicate = !str_comp(it->m_aTempWar, pName) || !str_comp(it->m_aTempHelper, pName) || !str_comp(it->m_aTempMute, pName);

		if(IsDuplicate)
		{
			it = m_TempEntries.erase(it);
		}
		else
			++it;
	}
}

void CFex::RemoveWarEntry(const char *pNameW, const char *pNameH, const char *pNameM)
{
	CTempEntry Entry(pNameW, pNameH, pNameM);
	auto it = std::find(m_TempEntries.begin(), m_TempEntries.end(), Entry);
	if(it != m_TempEntries.end())
		m_TempEntries.erase(it);
}

void CFex::UpdateTempPlayers()
{
	for(int i = 0; i < MAX_CLIENTS; ++i)
	{
		if(!GameClient()->m_aClients[i].m_Active)
			continue;

		m_TempPlayers[i].IsTempWar = false;
		m_TempPlayers[i].IsTempHelper = false;
		m_TempPlayers[i].IsTempMute = false;

		for(CTempEntry &Entry : m_TempEntries)
		{
			if(str_comp(GameClient()->m_aClients[i].m_aName, Entry.m_aTempWar) == 0 && str_comp(Entry.m_aTempWar, "") != 0)
				m_TempPlayers[i].IsTempWar = true;
			if(str_comp(GameClient()->m_aClients[i].m_aName, Entry.m_aTempHelper) == 0 && str_comp(Entry.m_aTempHelper, "") != 0)
				m_TempPlayers[i].IsTempHelper = true;
			if(str_comp(GameClient()->m_aClients[i].m_aName, Entry.m_aTempMute) == 0 && str_comp(Entry.m_aTempMute, "") != 0)
				m_TempPlayers[i].IsTempMute = true;
		}
	}
}

void CFex::ConOnlineInfo(IConsole::IResult *pResult, void *pUserData)
{
	CFex *pSelf = (CFex *)pUserData;
	pSelf->OnlineInfo();
}

void CFex::ConPlayerInfo(IConsole::IResult *pResult, void *pUserData)
{
	CFex *pSelf = (CFex *)pUserData;
	pSelf->PlayerInfo(pResult->GetString(0));
}

void CFex::OnlineInfo(bool Integrate)
{
	char aBuf[512];
	char active[512];

	int NumberWars = 0;
	int NumberWarsAfk = 0;
	for(auto &Client : GameClient()->m_aClients)
	{
		bool War = GameClient()->m_WarList.GetWarData(IdWithName(Client.m_aName)).m_WarGroupMatches[1];
		bool TempWar = m_TempPlayers[IdWithName(Client.m_aName)].IsTempWar;

		if(!Client.m_Active && GameClient()->m_Teams.Team(Client.m_Id) == 0)
			continue;

		if(Client.m_Id == m_pClient->m_Snap.m_LocalClientId)
			continue;

		if((War && !TempWar) || (!War && TempWar))
		{
			NumberWars++;
			if(Client.m_Afk)
				NumberWarsAfk++;
		}
	}

	int NumberTeams = 0;
	int NumberTeamsAfk = 0;
	for(auto &Client : GameClient()->m_aClients)
	{
		bool Team = GameClient()->m_WarList.GetWarData(IdWithName(Client.m_aName)).m_WarGroupMatches[2];

		if(!Client.m_Active && GameClient()->m_Teams.Team(Client.m_Id) == 0)
			continue;

		if(Client.m_Id == m_pClient->m_Snap.m_LocalClientId)
			continue;

		if(Team)
		{
			NumberTeams++;
			if(Client.m_Afk)
				NumberTeamsAfk++;
		}
	}

	int NumberHelpers = 0;
	int NumberHelpersAfk = 0;
	for(auto &Client : GameClient()->m_aClients)
	{
		bool Helper = GameClient()->m_WarList.GetWarData(IdWithName(Client.m_aName)).m_WarGroupMatches[3];
		bool TempHelper = m_TempPlayers[IdWithName(Client.m_aName)].IsTempHelper;

		if(!Client.m_Active && GameClient()->m_Teams.Team(Client.m_Id) == 0)
			continue;

		if(Client.m_Id == m_pClient->m_Snap.m_LocalClientId)
			continue;

		if((Helper && !TempHelper) || (!Helper && TempHelper))
		{
			NumberHelpers++;
			if(Client.m_Afk)
				NumberHelpersAfk++;
		}
	}

	int NumberMutes = 0;
	int NumberMutesAfk = 0;
	for(auto &Client : GameClient()->m_aClients)
	{
		bool Mute = GameClient()->m_WarList.m_WarPlayers[Client.m_Id].IsMuted;
		bool TempMute = m_TempPlayers[IdWithName(Client.m_aName)].IsTempMute;

		if(!Client.m_Active)
			continue;

		if(Client.m_Id == m_pClient->m_Snap.m_LocalClientId)
			continue;

		if((Mute && !TempMute) || (!Mute && TempMute))
		{
			NumberMutes++;
			if(Client.m_Afk)
				NumberMutesAfk++;
		}
	}

	str_format(aBuf, sizeof(aBuf), "│ [online] %d Teams | %d Wars | %d Helpers | %d Mutes", NumberTeams, NumberWars, NumberHelpers, NumberMutes);
	str_format(active, sizeof(active), "│ [active] %d Teams | %d Wars | %d Helpers | %d Mutes", NumberTeams - NumberTeamsAfk, NumberWars - NumberWarsAfk, NumberHelpers - NumberHelpersAfk, NumberMutes - NumberMutesAfk);
	if(!Integrate)
	{
		GameClient()->aMessage("╭──                  FeX Info");
		GameClient()->aMessage("│");
	}
	GameClient()->aMessage(aBuf);
	GameClient()->aMessage(active);
	if(!Integrate)
	{
		GameClient()->aMessage("│");
		GameClient()->aMessage("╰───────────────────────");
	}
}

void CFex::PlayerInfo(const char *pName)
{
	char aBuf[1024];
	str_format(aBuf, sizeof(aBuf), "Couldnt Find a Player With The Name \"%s\"", pName);
	if(IdWithName(pName) != -1)
	{
		int Id = IdWithName(pName);
		GameClient()->aMessage("╭──                  Player Info");
		GameClient()->aMessage("│");

		str_format(aBuf, sizeof(aBuf), "│ Name: %s", pName);
		GameClient()->aMessage(aBuf);
		str_format(aBuf, sizeof(aBuf), "│ Clan: %s", GameClient()->m_aClients[Id].m_aClan);
		GameClient()->aMessage(aBuf);
		GameClient()->aMessage("│");
		if(!GameClient()->m_aClients[Id].m_UseCustomColor)
		{
			str_format(aBuf, sizeof(aBuf), "│ Custom Color: %s", "No");
			GameClient()->aMessage(aBuf);
			GameClient()->aMessage("│");
		}
		else
		{
			str_format(aBuf, sizeof(aBuf), "│ Custom Color: %s", "Yes");
			GameClient()->aMessage(aBuf);
			str_format(aBuf, sizeof(aBuf), "│ Body Color: %d", GameClient()->m_aClients[Id].m_ColorBody);
			GameClient()->aMessage(aBuf);
			str_format(aBuf, sizeof(aBuf), "│ Feet Color: %d", GameClient()->m_aClients[Id].m_ColorFeet);
			GameClient()->aMessage(aBuf);
			GameClient()->aMessage("│");
		}
		str_format(aBuf, sizeof(aBuf), "│ Skin Name: %s", GameClient()->m_aClients[Id].m_aSkinName);
		GameClient()->aMessage(aBuf);
		GameClient()->aMessage("│");

		if(GameClient()->m_aClients[Id].m_AuthLevel > 0)
			str_format(aBuf, sizeof(aBuf), "│ Authed: Yes, Auth Level %s", GameClient()->m_aClients[Id].m_AuthLevel);
		else
		str_format(aBuf, sizeof(aBuf), "│ Authed: No", GameClient()->m_aClients[Id].m_AuthLevel);
		GameClient()->aMessage(aBuf);


		GameClient()->aMessage("│");
		GameClient()->aMessage("╰───────────────────────");
	}
	else
		GameClient()->aMessage(aBuf);
}

void CFex::ConTempWar(IConsole::IResult *pResult, void *pUserData)
{
	CFex *pSelf = (CFex *)pUserData;
	pSelf->TempWar(pResult->GetString(0));
}
void CFex::ConUnTempWar(IConsole::IResult *pResult, void *pUserData)
{
	CFex *pSelf = (CFex *)pUserData;
	pSelf->UnTempWar(pResult->GetString(0));
}

void CFex::ConTempHelper(IConsole::IResult *pResult, void *pUserData)
{
	CFex *pSelf = (CFex *)pUserData;
	pSelf->TempHelper(pResult->GetString(0));
}
void CFex::ConUnTempHelper(IConsole::IResult *pResult, void *pUserData)
{
	CFex *pSelf = (CFex *)pUserData;
	pSelf->UnTempHelper(pResult->GetString(0) );
}

void CFex::ConTempMute(IConsole::IResult *pResult, void *pUserData)
{
	CFex *pSelf = (CFex *)pUserData;
	pSelf->TempMute(pResult->GetString(0));
}
void CFex::ConUnTempMute(IConsole::IResult *pResult, void *pUserData)
{
	CFex *pSelf = (CFex *)pUserData;
	pSelf->UnTempMute(pResult->GetString(0));
}

// void CFex::RandomizeName()
// {
//     static const char CHARS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
//     char aName[16];
    
//     for(int i = 0; i < 15; i++)
//     {
//         int randIndex = rand() % (sizeof(CHARS) - 1);
//         aName[i] = CHARS[randIndex];
//     }
//     aName[15] = '\0';

//     char aCommand[128];
//     str_format(aCommand, sizeof(aCommand), "player_name \"%s\"", aName);
//     Console()->ExecuteLine(aCommand);
// }

// void CFex::RestoreOriginalName()
// {
//     char aCommand[128];
//     str_format(aCommand, sizeof(aCommand), "player_name \"%s\"", m_OriginalName);
//     Console()->ExecuteLine(aCommand);
// }

// void CFex::SendAutoMessage()
// {
//     if(!m_AutoMessageEnabled)
//         return;

//     // Check cooldown
//     if(time_get() < m_LastMessageTick + time_freq() * 6.5)
//         return;

//     // Check antimute protection
//     if(m_MessageCount >= 5)
//     {
//         if(time_get() > m_MessageResetTick)
//         {
//             m_MessageCount = 0;
//             m_MessageResetTick = time_get() + time_freq() * 10;
//         }
//         else
//             return;
//     }

//     // Now handle message sending
//     if(m_MessageTargets.empty())
//         RefreshTargetList();

//     if(!m_MessageTargets.empty())
//     {
//         if(str_comp(m_SingleTarget, "*all") == 0 && !m_IsWhisper)
//         {
//             char aBuf[512];
//             char aNames[256] = "";
            
//             for(size_t i = 0; i < m_MessageTargets.size(); i++)
//             {
//                 const char* pName = GameClient()->m_aClients[m_MessageTargets[i]].m_aName;
//                 if(i > 0)
//                     str_append(aNames, ", ", sizeof(aNames));
//                 str_append(aNames, pName, sizeof(aNames));
//             }
            
//             str_format(aBuf, sizeof(aBuf), "%s || %s", aNames, m_CurrentMessage);
//             GameClient()->m_Chat.SendChat(0, aBuf);
//             RefreshTargetList();
//         }
//         else
//         {
//             char aBuf[512];
//             const char* pTargetName = GameClient()->m_aClients[m_MessageTargets[m_CurrentTargetIndex]].m_aName;

//             if(m_IsWhisper)
//                 str_format(aBuf, sizeof(aBuf), "/w \"%s\" %s", pTargetName, m_CurrentMessage);
//             else
//                 str_format(aBuf, sizeof(aBuf), "%s: %s", pTargetName, m_CurrentMessage);

//             GameClient()->m_Chat.SendChat(0, aBuf);
//             m_CurrentTargetIndex = (m_CurrentTargetIndex + 1) % m_MessageTargets.size();
//         }

//         m_LastMessageTick = time_get();
//         m_MessageCount++;
//     }

// 	if(m_IsRandomName)
// 	{
// 		if(!m_NameJustChanged)
// 		{
// 			RandomizeName();
// 			m_LastNameChangeTick = time_get();
// 			m_NameJustChanged = true;
// 			return;
// 		}

// 		// Wait for name change to take effect
// 		if(time_get() < m_LastNameChangeTick + time_freq() / 4) // Reduced to 0.25 second delay
// 			return;

// 		m_NameJustChanged = false;
// 	}

// }

// void CFex::RefreshTargetList()
// {
//     m_MessageTargets.clear();

//     // Single target mode
//     if(str_comp(m_SingleTarget, "") != 0 && str_comp(m_SingleTarget, "*all") != 0)
//     {
//         int TargetID = IdWithName(m_SingleTarget);
//         if(TargetID >= 0)
//             m_MessageTargets.push_back(TargetID);
//         return;
//     }

//     // Collect valid targets
//     std::vector<int> validClients;
//     for(int i = 0; i < MAX_CLIENTS; i++)
//     {
//         if(IsValidTarget(i))
//             validClients.push_back(i);
//     }

//     // Random selection for *all mode with 15 targets
//     if(str_comp(m_SingleTarget, "*all") == 0 && !m_IsWhisper)
//     {
//         while(m_MessageTargets.size() < std::min(15, (int)validClients.size()))
//         {
//             int randIndex = rand() % validClients.size();
//             int clientId = validClients[randIndex];
            
//             if(std::find(m_MessageTargets.begin(), m_MessageTargets.end(), clientId) == m_MessageTargets.end())
//                 m_MessageTargets.push_back(clientId);
//         }
//     }
//     else
//     {
//         // Full list for whisper mode
//         m_MessageTargets = validClients;
//     }
// }

// bool CFex::IsValidTarget(int ClientID)
// {
//     if(!GameClient()->m_aClients[ClientID].m_Active)
//         return false;

//     if(ClientID == m_pClient->m_Snap.m_LocalClientId || ClientID == GameClient()->m_aLocalIds[1])
//         return false;

//     return true;
// }

// void CFex::ConAutoMessage(IConsole::IResult *pResult, void *pUserData)
// {
//     CFex *pSelf = (CFex *)pUserData;
    
//     // Toggle automessage
//     pSelf->m_AutoMessageEnabled = !pSelf->m_AutoMessageEnabled;
    
//     if(pSelf->m_AutoMessageEnabled)
//     {
// 		str_copy(pSelf->m_OriginalName, 
// 			pSelf->GameClient()->m_aClients[pSelf->m_pClient->m_Snap.m_LocalClientId].m_aName, 
// 			sizeof(pSelf->m_OriginalName));
//         str_copy(pSelf->m_SingleTarget, pResult->GetString(0), sizeof(pSelf->m_SingleTarget));
//         str_copy(pSelf->m_CurrentMessage, pResult->GetString(1), sizeof(pSelf->m_CurrentMessage));
//         pSelf->m_IsWhisper = pResult->GetInteger(2) == 1;
// 		pSelf->m_IsRandomName = pResult->GetInteger(3) == 1;
        
//         pSelf->m_LastMessageTick = 0;
//         pSelf->m_MessageCount = 0;
//         pSelf->m_MessageResetTick = 0;
//         pSelf->m_CurrentTargetIndex = 0;
        
//         pSelf->RefreshTargetList();
        
//         pSelf->GameClient()->aMessage("Auto message enabled");
//     }
//     else
//     {
// 		pSelf->RestoreOriginalName();
//         pSelf->GameClient()->aMessage("Auto message disabled");
//     }
// }

// void CFex::CheckAuthorizedPlayers()
// {
//     // Check only once per second
//     if(time_get() < m_LastAuthCheck + time_freq())
//         return;

//     m_LastAuthCheck = time_get();

//     // Check each client for auth level
//     for(int i = 0; i < MAX_CLIENTS; i++)
//     {
//         if(!GameClient()->m_aClients[i].m_Active)
//             continue;

//         if(GameClient()->m_aClients[i].m_AuthLevel > 0)
//         {
//             // Found authorized player - disable auto message
//             if(m_AutoMessageEnabled)
//             {
//                 m_AutoMessageEnabled = false;
// 				RestoreOriginalName();
//                 char aBuf[128];
//                 str_format(aBuf, sizeof(aBuf), "Auto message disabled - Authorized player %s detected", 
//                     GameClient()->m_aClients[i].m_aName);
//                 GameClient()->aMessage(aBuf);
//             }
//             return;
//         }
//     }
// }

void CFex::OnRender()
{
    // // Handle auto join team
    // if(g_Config.m_ClAutoJoinTeam > 0 && !m_AutoJoinTeamAttempted && Client()->State() == IClient::STATE_ONLINE)
    // {
	// 	// Check if already in a team
	// 	bool AlreadyInTeam = false;
	// 	for(int i = 0; i < MAX_CLIENTS; i++)
	// 	{
	// 		if(i == m_pClient->m_Snap.m_LocalClientId && m_pClient->m_aClients[i].m_Team != 0)
	// 		{
	// 			AlreadyInTeam = true;
	// 			return;
	// 		}
	// 	}

	// 	if(!AlreadyInTeam)
	// 	{
	// 		if(m_AutoJoinTeamTick == 0)
	// 		{
	// 			m_AutoJoinTeamTick = time_get() + time_freq() * g_Config.m_ClAutoJoinTeamDelay;
	// 		}
	// 		else if(time_get() > m_AutoJoinTeamTick)
	// 		{
	// 			// Try to join team, if full try next team
	// 			int TargetTeam = g_Config.m_ClAutoJoinTeam;
	// 			bool TeamFull = false;
				
	// 			// Check if team is full by counting players
	// 			if(TargetTeam > 0) // Don't check for team 0 (freemode)
	// 			{
	// 				int PlayersInTeam = 0;
	// 				for(int i = 0; i < MAX_CLIENTS; i++)
	// 				{
	// 					if(m_pClient->m_aClients[i].m_Active && !m_pClient->m_aClients[i].m_Spec && m_pClient->m_Teams.Team(i) == TargetTeam)
	// 						PlayersInTeam++;
	// 				}
					
	// 				// If team has too many players, try next team
	// 				if(PlayersInTeam >= 1) // Assuming max team size is 16
	// 				{
	// 					TeamFull = true;
	// 					TargetTeam = (TargetTeam % 63) + 1; // Try next team (1-63)
	// 				}
	// 			}
				
	// 			// Send team change command
	// 			char teamswitch[128];
	// 			str_format(teamswitch, sizeof(teamswitch), "/team %d", TargetTeam);
	// 			m_pClient->m_Chat.SendChat(0, teamswitch);
				
	// 			m_AutoJoinTeamAttempted = true;
	// 			m_AutoJoinTeamTick = 0;
				
	// 			// Log the action
	// 			char aBuf[128];
	// 			str_format(aBuf, sizeof(aBuf), "Auto joined team %d %s", 
	// 				TargetTeam, 
	// 				TeamFull ? " (original team was full)" : "");
	// 			Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "FeX(Autojoin)->", aBuf);
	
	// 			if(g_Config.m_ClAutoJoinTeamLock)
	// 			{
	// 				char teamlock[128];
	// 				str_format(teamlock, sizeof(teamlock), "/lock");
	// 				m_pClient->m_Chat.SendChat(0, teamlock);
	// 				char aBuf[128];
	// 				str_format(aBuf, sizeof(aBuf), "joined team %d with locking the team", TargetTeam); 
	// 				Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "FeX(Autojoin)->", aBuf);
	// 			}
	
	// 			// Reset attempt flag after delay instead of setting it permanently
	// 			m_AutoJoinTeamTick = time_get() + time_freq() * g_Config.m_ClAutoJoinTeamDelay; // 3 second cooldown before next attempt
	// 			m_AutoJoinTeamAttempted = false; // Reset the attempt flag to allow another try
						
	// 		}
	// 	}
    // }

	// Handle auto join dummy
	if(g_Config.m_ClAutoJoinDummy && Client()->State() == IClient::STATE_ONLINE)
	{
		// If already connected, reset flags and stop
		if(Client()->DummyConnected())
		{
			if(g_Config.m_ClAutoJoinDummySwitch && g_Config.m_ClDummy == 1 && !m_HasSwitchedBack)
			{
				g_Config.m_ClDummy = 0;
				m_HasSwitchedBack = true; // Mark that we've switched back
				Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "autojoin", "Switched back to main player");
			}
			m_OnAttemptingDummyJoin = false;
			m_AutoJoinDummyAttempted = false;
			m_AutoJoinDummyTick = 0;
			m_FirstTimerExpired = false;
			return;
		}

		// Initialize timer if not set
		if(m_AutoJoinDummyTick == 0)
		{
			m_AutoJoinDummyTick = time_get() + time_freq() * g_Config.m_ClAutoJoinDummyDelay;
			m_OnAttemptingDummyJoin = true;
			Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "autojoin", "Waiting %d seconds to attempt dummy join...", g_Config.m_ClAutoJoinDummyDelay);
		}

		// Only check for player leaves after first timer has expired
		if(m_FirstTimerExpired && m_OnAttemptingDummyJoin)
		{
			CheckPlayerLeave();
			m_AutoJoinDummyTick = time_get() + time_freq() * g_Config.m_ClAutoJoinDummyDelay;
		}

		// Try joining when timer expires
		if(time_get() > m_AutoJoinDummyTick && m_OnAttemptingDummyJoin)
		{
			m_FirstTimerExpired = true; // Mark that initial timer has expired
			Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "autojoin", "Attempting to join with dummy");
			
			// Connect dummy and force switch back to main player
			Console()->ExecuteLine("dummy_connect");
			if(g_Config.m_ClAutoJoinDummySwitch)
			{
				g_Config.m_ClDummy = 0;
			}

			// Reset flags after attempt
			m_OnAttemptingDummyJoin = false;
			m_AutoJoinDummyTick = time_get() + time_freq() * g_Config.m_ClAutoJoinDummyDelay;
		}
	}
    
    // Reset auto join flags when disconnected
    if(Client()->State() != IClient::STATE_ONLINE)
    {
		// m_AutoMessageEnabled = false;
        // m_AutoJoinTeamAttempted = false;
        m_AutoJoinDummyAttempted = false;
        // m_AutoJoinTeamTick = 0;
        m_AutoJoinDummyTick = 0;
        m_ServerJustJoined = false;
		m_OnAttemptingDummyJoin = false;
		m_HasSwitchedBack = false;
		// m_IsRandomName = false;
    }
}

void CFex::CheckPlayerLeave()
{
    int CurrentPlayers = 0;
    for(int i = 0; i < MAX_CLIENTS; i++)
    {
        if(m_pClient->m_aClients[i].m_Active)
            CurrentPlayers++;
    }

	m_LastPlayerCount = CurrentPlayers;

    // If player count decreased, try joining immediately
    if(CurrentPlayers < m_LastPlayerCount)
    {
        m_AutoJoinDummyTick = 0; // Reset tick to try joining immediately
		Console()->ExecuteLine("dummy_connect");
        Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "autojoin", "Player left, attempting to join");
    }
}
void CFex::OnConsoleInit()
{
	Console()->Register("onlineinfo", "", CFGFLAG_CLIENT, ConOnlineInfo, this, "Shows you how many people of default lists are on the current server");
	Console()->Register("playerinfo", "s[name]", CFGFLAG_CLIENT, ConPlayerInfo, this, "Get Info of a Player");

	// Temporary Lists
	Console()->Register("addtempwar", "s[name] ?r[reason]", CFGFLAG_CLIENT, ConTempWar, this, "temporary War");
	Console()->Register("deltempwar", "s[name]", CFGFLAG_CLIENT, ConUnTempWar, this, "remove temporary War");

	Console()->Register("addtemphelper", "s[name] ?r[reason]", CFGFLAG_CLIENT, ConTempHelper, this, "temporary Helper");
	Console()->Register("deltemphelper", "s[name]", CFGFLAG_CLIENT, ConUnTempHelper, this, "remove temporary Helper");

	Console()->Register("addtempmute", "s[name] ?r[reason]", CFGFLAG_CLIENT, ConTempMute, this, "temporary Mute");
	Console()->Register("deltempmute", "s[name]", CFGFLAG_CLIENT, ConUnTempMute, this, "remove temporary Mute");

	// Console()->Register("amsg", "s[name] s[msg] i[whisper] i[randomize name]", CFGFLAG_CLIENT, ConAutoMessage, this, "Auto message to players *all for everyone");
}
void CFex::OnInit()
{
	// On client load
	TextRender()->SetCustomFace(g_Config.m_ClCustomFont);

	// Auto	join variables
	// m_AutoJoinTeamTick = 0;
	m_AutoJoinDummyTick = 0;
	m_LastPlayerCount = 0;
	// m_AutoJoinTeamAttempted = false;
	m_AutoJoinDummyAttempted = false;
	m_ServerJustJoined = false;
	m_OnAttemptingDummyJoin = false;
	m_LastPlayerCount = 0;
	m_FirstTimerExpired = false;
	m_HasSwitchedBack = false;
	// m_LastNameChangeTick = 0;
    // m_NameJustChanged = false;
	// m_IsRandomName = false;
}

void CFex::OnStateChange(int NewState, int OldState)
{
	if(NewState == IClient::STATE_ONLINE && OldState != IClient::STATE_ONLINE)
    {
        // m_AutoJoinTeamAttempted = false;
        m_AutoJoinDummyAttempted = false;
		if(g_Config.m_ClAutoJoinDummy)
			m_OnAttemptingDummyJoin = true;
        m_ServerJustJoined = true;
    }
}

bool CFex::IsSpecialClan(const char* pClanName) {
    return str_comp(pClanName, SPECIAL_CLAN) == 0;
}



