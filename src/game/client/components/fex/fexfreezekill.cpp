#include <engine/shared/config.h>
#include <engine/client.h>
#include <engine/shared/protocol.h>
#include <engine/textrender.h>

#include <game/gamecore.h>
#include <game/client/components/chat.h>
#include <game/client/gameclient.h>

#include <base/vmath.h>
#include <base/system.h>

#include "fexfreezekill.h"

void CFreezeKill::OnRender()
{
	int Local = m_pClient->m_Snap.m_LocalClientId;
	
	float Time = g_Config.m_ClFreezeKillMs / 1000.0f;

	float TimeReset = time_get() + time_freq() * Time;

	// if freeze kill isnt turned on, stop

	if(!g_Config.m_ClFreezeKill)
	{
		m_LastFreeze = TimeReset;
		return;
	}

	// if player hasnt started the race, stop

	if(!GameClient()->CurrentRaceTime())
	{
		m_SentFreezeKill = false;
		m_LastFreeze = TimeReset + 3;
		return;
	}

	// if map name isnt "Multeasymap", stop

	if(g_Config.m_ClFreezeKillMultOnly)
		if(str_comp(Client()->GetCurrentMap(), "Multeasymap") != 0)
			return;

	// debug

	if(g_Config.m_ClFreezeKillDebug)
	{
		float a = (m_LastFreeze - time_get()) / 1000000000.0f;

		char aBuf[512];
		str_format(aBuf, sizeof(aBuf), "until kill: %f", a);
		GameClient()->TextRender()->Text(50, 100, 10, aBuf);
	}

	for(int i = 0; i < MAX_CLIENTS; i++)
	{
		// stuff


		CCharacterCore *pCharacter = &m_pClient->m_aClients[Local].m_Predicted;


		// if tried to kill, stop

		if(m_SentFreezeKill == true)
			return;

		// stop when spectating

		if(m_pClient->m_aClients[Local].m_Paused || m_pClient->m_aClients[Local].m_Spec)
			m_LastFreeze = TimeReset;

		// wait x amount of seconds before killing

		if(g_Config.m_ClFreezeKillWaitMs)
		{
			// kill if frozen (without deep and live freeze)

			if(m_pClient->m_aClients[Local].m_FreezeEnd < 3 && !g_Config.m_ClFreezeKillOnlyFullFrozen && !pCharacter->m_IsInFreeze)
				m_LastFreeze = TimeReset;

			// only kill if player is in a freeze tile

			if(g_Config.m_ClFreezeKillOnlyFullFrozen)
			{
				if(!pCharacter->m_IsInFreeze)
					m_LastFreeze = TimeReset;
            }

			// default kill protection timer
			if(m_LastFreeze <= time_get())
			{
				if(GameClient()->CurrentRaceTime() > 60 * g_Config.m_SvKillProtection && g_Config.m_ClFreezeKillIgnoreKillProt)
				{
					m_pClient->m_Chat.SendChat(0, "/kill");
					m_SentFreezeKill = true;
					m_LastFreeze = time_get() + time_freq() * 5;
					return;
				}
				else if((pCharacter->m_IsInFreeze || m_pClient->m_aClients[Local].m_FreezeEnd > 0))
				{
					GameClient()->SendKill();
					m_SentFreezeKill = true;
					return;
				}
			}
		}

		// if not wating for x amount of seconds

		else if(pCharacter->m_IsInFreeze)
		{
			if(GameClient()->CurrentRaceTime() > 60 * g_Config.m_SvKillProtection && g_Config.m_ClFreezeKillIgnoreKillProt)
			{
				m_pClient->m_Chat.SendChat(0, "/kill");
				m_SentFreezeKill = true;
				m_LastFreeze = time_get() + time_freq() * 5;
			}
			else
			{
				GameClient()->SendKill();
				m_SentFreezeKill = true;
			}
			return;
		}
	}
}