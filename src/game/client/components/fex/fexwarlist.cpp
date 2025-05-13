#include <engine/graphics.h>
#include <engine/shared/config.h>

#include <game/client/animstate.h>
#include <game/client/render.h>
#include <game/generated/client_data.h>
#include <game/generated/protocol.h>

#include <game/client/gameclient.h>

#include "fexwarlist.h"
#include "fex.h"

void CWarList::OnNewSnapshot()
{
	UpdateWarPlayers();
}

void CWarList::OnConsoleInit()
{
	IConfigManager *pConfigManager = Kernel()->RequestInterface<IConfigManager>();
	if(pConfigManager)
		pConfigManager->RegisterFXCallback(ConfigSaveCallback, this);

	Console()->Register("update_war_group", "i[group_index] s[name] i[color]", CFGFLAG_CLIENT, ConUpsertWarType, this, "Update or add a specific war group");
	Console()->Register("add_war_entry", "s[group] s[name] s[clan] r[reason]", CFGFLAG_CLIENT, ConAddWarEntry, this, "Adds a specific war entry");
	Console()->Register("add_mute", "s[name]", CFGFLAG_CLIENT, ConAddMuteEntry, this, "Remove a clan war entry"); // E-Client [Mutes]

	Console()->Register("war_name", "s[group] s[name] ?r[reason]", CFGFLAG_CLIENT, ConName, this, "Add a name war entry");
	Console()->Register("war_clan", "s[group] s[clan] ?r[reason]", CFGFLAG_CLIENT, ConClan, this, "Add a clan war entry");
	Console()->Register("remove_war_name", "s[group] s[name]", CFGFLAG_CLIENT, ConRemoveName, this, "Remove a name war entry");
	Console()->Register("remove_war_clan", "s[group] s[clan]", CFGFLAG_CLIENT, ConRemoveClan, this, "Remove a clan war entry");

	// In-game commands
	Console()->Register("war_name_index", "i[group_index] s[name] ?r[reason]", CFGFLAG_CLIENT, ConNameIndex, this, "Remove a clan war entry");
	Console()->Register("war_clan_index", "s[group_index] s[name] ?r[reason]", CFGFLAG_CLIENT, ConClanIndex, this, "Remove a clan war entry");
	Console()->Register("remove_war_name_index", "i[group_index] s[name]", CFGFLAG_CLIENT, ConRemoveNameIndex, this, "Remove a clan war entry");
	Console()->Register("remove_war_clan_index", "s[group_index] s[name]", CFGFLAG_CLIENT, ConRemoveClanIndex, this, "Remove a clan war entry");

	// E-Client [Mutes]
	Console()->Register("addmute", "s[name]", CFGFLAG_CLIENT, ConAddMute, this, "Remove a clan war entry");
	Console()->Register("delmute", "s[name]", CFGFLAG_CLIENT, ConDelMute, this, "Removes a Muted Name");

	m_pStorage = Kernel()->RequestInterface<IStorage>();
	IOHANDLE File = m_pStorage->OpenFile(WARLIST_FILE, IOFLAG_READ, IStorage::TYPE_ALL);
	if(File)
	{
		io_close(File);
		Console()->ExecuteFile(WARLIST_FILE);
	}

    ParseWebhookUrls();
}

// In-game war Commands
void CWarList::ConNameIndex(IConsole::IResult *pResult, void *pUserData)
{
	int Index = pResult->GetInteger(0);
	const char *pName = pResult->GetString(1);
	const char *pReason = pResult->GetString(2);
	CWarList *pThis = static_cast<CWarList *>(pUserData);
	pThis->AddWarEntryInGame(Index, pName, pReason, false);
}
void CWarList::ConClanIndex(IConsole::IResult *pResult, void *pUserData)
{
	int Index = pResult->GetInteger(0);
	const char *pName = pResult->GetString(1);
	const char *pReason = pResult->GetString(2);
	CWarList *pThis = static_cast<CWarList *>(pUserData);
	pThis->AddWarEntryInGame(Index, pName, pReason, true);
}
void CWarList::ConRemoveNameIndex(IConsole::IResult *pResult, void *pUserData)
{
	int Index = pResult->GetInteger(0);
	const char *pName = pResult->GetString(1);
	CWarList *pThis = static_cast<CWarList *>(pUserData);
	pThis->RemoveWarEntryInGame(Index, pName, false);
}
void CWarList::ConRemoveClanIndex(IConsole::IResult *pResult, void *pUserData)
{
	int Index = pResult->GetInteger(0);
	const char *pName = pResult->GetString(1);
	CWarList *pThis = static_cast<CWarList *>(pUserData);
	pThis->RemoveWarEntryInGame(Index, pName, true);
}

void CWarList::ConRemoveNameWar(IConsole::IResult *pResult, void *pUserData) {}
void CWarList::ConRemoveClanWar(IConsole::IResult *pResult, void *pUserData) {}
void CWarList::ConNameTeam(IConsole::IResult *pResult, void *pUserData) {}
void CWarList::ConClanTeam(IConsole::IResult *pResult, void *pUserData) {}
void CWarList::ConRemoveNameTeam(IConsole::IResult *pResult, void *pUserData) {}
void CWarList::ConRemoveClanTeam(IConsole::IResult *pResult, void *pUserData) {}

// Generic Commands
void CWarList::ConName(IConsole::IResult *pResult, void *pUserData)
{
	const char *pType = pResult->GetString(0);
	const char *pName = pResult->GetString(1);
	const char *pReason = pResult->GetString(2);
	CWarList *pThis = static_cast<CWarList *>(pUserData);
	pThis->AddWarEntry(pName, "", pReason, pType);
}
void CWarList::ConClan(IConsole::IResult *pResult, void *pUserData)
{
	const char *pType = pResult->GetString(0);
	const char *pClan = pResult->GetString(1);
	const char *pReason = pResult->GetString(2);
	CWarList *pThis = static_cast<CWarList *>(pUserData);
	pThis->AddWarEntry("", pClan, pReason, pType);
}
void CWarList::ConRemoveName(IConsole::IResult *pResult, void *pUserData)
{
	const char *pType = pResult->GetString(0);
	const char *pName = pResult->GetString(1);
	CWarList *pThis = static_cast<CWarList *>(pUserData);
	pThis->RemoveWarEntry(pName, "", pType);
}
void CWarList::ConRemoveClan(IConsole::IResult *pResult, void *pUserData)
{
	const char *pType = pResult->GetString(0);
	const char *pClan = pResult->GetString(1);
	CWarList *pThis = static_cast<CWarList *>(pUserData);
	pThis->RemoveWarEntry("", pClan, pType);
}

// Backend Commands for config file
void CWarList::ConAddWarEntry(IConsole::IResult *pResult, void *pUserData)
{
	const char *pType = pResult->GetString(0);
	const char *pName = pResult->GetString(1);
	const char *pClan = pResult->GetString(2);
	const char *pReason = pResult->GetString(3);
	CWarList *pThis = static_cast<CWarList *>(pUserData);
	pThis->AddWarEntry(pName, pClan, pReason, pType);
}
void CWarList::ConUpsertWarType(IConsole::IResult *pResult, void *pUserData)
{
	int Index = pResult->GetInteger(0);
	const char *pType = pResult->GetString(1);
	unsigned int ColorInt = pResult->GetInteger(2);
	ColorRGBA Color = color_cast<ColorRGBA>(ColorHSLA(ColorInt));
	CWarList *pThis = static_cast<CWarList *>(pUserData);
	pThis->UpsertWarType(Index, pType, Color);
}

// E-Client [Mutes]
void CWarList::ConAddMuteEntry(IConsole::IResult *pResult, void *pUserData)
{
	const char *pName = pResult->GetString(0);
	CWarList *pThis = static_cast<CWarList *>(pUserData);
	pThis->AddMuteEntry(pName);
}
void CWarList::ConAddMute(IConsole::IResult *pResult, void *pUserData)
{
	const char *pName = pResult->GetString(0);
	CWarList *pThis = static_cast<CWarList *>(pUserData);
	pThis->AddMute(pName);
}
void CWarList::ConDelMute(IConsole::IResult *pResult, void *pUserData)
{
	const char *pName = pResult->GetString(0);
	CWarList *pThis = static_cast<CWarList *>(pUserData);
	pThis->DelMute(pName);
}

void CWarList::AddWarEntryInGame(int WarType, const char *pName, const char *pReason, bool IsClan)
{
    if(str_comp(pName, "") == 0)
        return;
    if(WarType >= (int)m_WarTypes.size())
        return;

    CWarType *pWarType = m_WarTypes[WarType];
    CWarEntry Entry(pWarType);
    str_copy(Entry.m_aReason, pReason);
    char aBuf[128];

    if(IsClan)
    {
        for(int i = 0; i < MAX_CLIENTS; ++i)
        {
            if(!GameClient()->m_aClients[i].m_Active)
                continue;
            // Found user
            if(str_comp(GameClient()->m_aClients[i].m_aName, pName) == 0)
            {
                if(str_comp(GameClient()->m_aClients[i].m_aClan, "") != 0)
                {
                    str_format(aBuf, sizeof(aBuf), "added \"%s's\" clan to '%s' list", pName, pWarType->m_aWarName);
                    str_copy(Entry.m_aClan, GameClient()->m_aClients[i].m_aClan);
                }
                else
                {
                    str_format(aBuf, sizeof(aBuf), "No clan found for user \"%s\"", pName);
                    break;
                }
            }
        }
    }
    else
    {
        str_copy(Entry.m_aName, pName);
        str_format(aBuf, sizeof(aBuf), "added \"%s\" to '%s' list", pName, pWarType->m_aWarName);

        GameClient()->m_Fex.UnTempWar(pName, true);
        GameClient()->m_Fex.UnTempHelper(pName, true);
    }
    if(!g_Config.m_ClWarListAllowDuplicates)
        RemoveWarEntryDuplicates(Entry.m_aName, Entry.m_aClan);

    GameClient()->aMessage(aBuf);
    AddWarEntry(Entry.m_aName, Entry.m_aClan, Entry.m_aReason, Entry.m_pWarType->m_aWarName);

    if(IsClan)
    {
        SendDiscordLogAsync(Client()->PlayerName(), Entry.m_pWarType->m_aWarName, "", Entry.m_aClan);
    }
    else
    {
        SendDiscordLogAsync(Client()->PlayerName(), Entry.m_pWarType->m_aWarName, pName, "");
    }
}

void CWarList::RemoveWarEntryInGame(int WarType, const char *pName, bool IsClan)
{
    if(!str_comp(pName, ""))
        return;
    if(WarType >= (int)m_WarTypes.size())
        return;

    CWarType *pWarType = m_WarTypes[WarType];
    CWarEntry Entry(pWarType);
    char aBuf[128];

    if(IsClan)
    {
        for(int i = 0; i < MAX_CLIENTS; ++i)
        {
            if(!GameClient()->m_aClients[i].m_Active)
                continue;
            // Found user
            if(str_comp(GameClient()->m_aClients[i].m_aName, pName) == 0)
            {
                if(str_comp(GameClient()->m_aClients[i].m_aClan, "") != 0)
                {
                    str_format(aBuf, sizeof(aBuf), "removed \"%s's\" clan from the %s list", pName, pWarType->m_aWarName);
                    str_copy(Entry.m_aClan, GameClient()->m_aClients[i].m_aClan);
                    break;
                }
                else
                {
                    str_format(aBuf, sizeof(aBuf), "No clan found for user \"%s\"", pName);
                    break;
                }
            }
        }
    }
    else
    {
        str_copy(Entry.m_aName, pName);
        str_format(aBuf, sizeof(aBuf), "removed \"%s\" from the %s list", pName, pWarType->m_aWarName);
        GameClient()->m_Fex.UnTempWar(pName, true);
        GameClient()->m_Fex.UnTempHelper(pName, true);
    }
    GameClient()->aMessage(aBuf);
    RemoveWarEntry(Entry.m_aName, Entry.m_aClan, Entry.m_pWarType->m_aWarName);

    if(IsClan)
    {
        SendDiscordLogAsyncRemoval(Client()->PlayerName(), Entry.m_pWarType->m_aWarName, "", Entry.m_aClan);
    }
    else
    {
        SendDiscordLogAsyncRemoval(Client()->PlayerName(), Entry.m_pWarType->m_aWarName, pName, "");
    }
}

void CWarList::AddMuteEntry(const char *pName)
{
	if(!str_comp(pName, ""))
		return;

	CMuteEntry Entry(pName);
	str_copy(Entry.m_aMutedName, pName);

	m_MuteEntries.push_back(Entry);
}

void CWarList::AddMute(const char *pName)
{
	if(!str_comp(pName, ""))
		return;

	CMuteEntry Entry(pName);
	str_copy(Entry.m_aMutedName, pName);

	char aBuf[128];
	str_format(aBuf, sizeof(aBuf), "Added \"%s\" to the Mute List", pName);
	GameClient()->aMessage(aBuf);
	DelMute(pName, true);

	m_MuteEntries.push_back(Entry);

	GameClient()->m_Fex.UnTempMute(pName, true);
}

void CWarList::DelMute(const char *pName, bool Silent)
{
	if(str_comp(pName, "") == 0)
		return;

	char aBuf[128];
	str_format(aBuf, sizeof(aBuf), "couldn't find \"%s\" in the Mute List", pName);
	CMuteEntry Entry(pName);

	auto it = std::find(m_MuteEntries.begin(), m_MuteEntries.end(), Entry);
	if(it != m_MuteEntries.end())
	{
		for(CMuteEntry &Entries : m_MuteEntries)
		{
			for(auto it2 = m_MuteEntries.begin(); it2 != m_MuteEntries.end();)
			{
				bool IsDuplicate = !str_comp(it2->m_aMutedName, pName);

				if(IsDuplicate)
					it2 = m_MuteEntries.erase(it2);
				else
					++it2;

				if(!str_comp(Entries.m_aMutedName, pName))
					str_format(aBuf, sizeof(aBuf), "Removed \"%s\" from the Mute List", pName);
			}
		}
	}
	if(GameClient()->m_Fex.UnTempMute(pName, true))
		str_format(aBuf, sizeof(aBuf), "Removed \"%s\" from the Mute List", pName);

	if(!Silent)
		GameClient()->aMessage(aBuf);
}

void CWarList::UpdateWarEntry(int Index, const char *pName, const char *pClan, const char *pReason, CWarType *pType)
{
	if(Index >= 0 && Index < static_cast<int>(m_WarEntries.size()))
	{
		str_copy(m_WarEntries[Index].m_aName, pName);
		str_copy(m_WarEntries[Index].m_aClan, pClan);
		str_copy(m_WarEntries[Index].m_aReason, pReason);
		m_WarEntries[Index].m_pWarType = pType;
	}
}

void CWarList::UpsertWarType(int Index, const char *pType, ColorRGBA Color)
{
	if(str_comp(pType, "none") == 0)
		return;

	if(Index >= 0 && Index < static_cast<int>(m_WarTypes.size()))
	{
		str_copy(m_WarTypes[Index]->m_aWarName, pType);
		m_WarTypes[Index]->m_Color = Color;
	}
	else
	{
		AddWarType(pType, Color);
	}
}


void CWarList::AddWarEntry(const char *pName, const char *pClan, const char *pReason, const char *pType)
{
	if(str_comp(pName, "") == 0 && str_comp(pClan, "") == 0)
		return;

	CWarType *WarType = FindWarType(pType);
	if(WarType == m_pWarTypeNone)
	{
		AddWarType(pType, ColorRGBA(0, 0, 0, 1));
		WarType = FindWarType(pType);
	}

	CWarEntry Entry(WarType);
	str_copy(Entry.m_aReason, pReason);

	if(str_comp(pClan, "") != 0)
		str_copy(Entry.m_aClan, pClan);
	else if(str_comp(pName, "") != 0)
		str_copy(Entry.m_aName, pName);

	if(!g_Config.m_ClWarListAllowDuplicates)
		RemoveWarEntryDuplicates(pName, pClan);
	m_WarEntries.push_back(Entry);
}

void CWarList::RemoveWarEntryDuplicates(const char *pName, const char *pClan)
{
	if(str_comp(pName, "") == 0 && str_comp(pClan, "") == 0)
		return;

	for(auto it = m_WarEntries.begin(); it != m_WarEntries.end();)
	{
		bool IsDuplicate =
			(str_comp(it->m_aName, pName) == 0) &&
			(str_comp(it->m_aClan, pClan) == 0);

		if(IsDuplicate)
			it = m_WarEntries.erase(it);
		else
			++it;
	}
}

void CWarList::AddWarType(const char *pType, ColorRGBA Color)
{
	if(str_comp(pType, "none") == 0)
		return;

	CWarType *Type = FindWarType(pType);
	if(Type == m_pWarTypeNone)
	{
		CWarType *NewType = new CWarType(pType, Color);
		m_WarTypes.push_back(NewType);
	}
	else
	{
		Type->m_Color = Color;
	}
}

void CWarList::RemoveWarEntry(const char *pName, const char *pClan, const char *pType)
{
	CWarType *WarType = FindWarType(pType);
	CWarEntry Entry(WarType, pName, pClan, "");
	auto it = std::find(m_WarEntries.begin(), m_WarEntries.end(), Entry);
	if(it != m_WarEntries.end())
		m_WarEntries.erase(it);
}

void CWarList::RemoveWarEntry(CWarEntry *Entry)
{
	auto it = std::find_if(m_WarEntries.begin(), m_WarEntries.end(),
		[Entry](const CWarEntry &WarEntry) { return &WarEntry == Entry; });
	if(it != m_WarEntries.end())
		m_WarEntries.erase(it);
}

void CWarList::RemoveWarType(const char *pType)
{
    if(str_comp(pType, "") == 0)
        return;

    for(auto it = m_WarTypes.begin(); it != m_WarTypes.end(); ++it)
    {
        if(str_comp((*it)->m_aWarName, pType) == 0)
        {
            if(!(*it)->m_Removable)
            {
                GameClient()->aMessage("War type is not removable.");
                return;
            }
            m_WarTypes.erase(it);

            char aBuf[128];
            str_format(aBuf, sizeof(aBuf), "removed war type \"%s\"", pType);
            GameClient()->aMessage(aBuf);
            return;
        }
    }
}

int CWarList::FindWarTypeWithName(const char *pName)
{
	for(CWarEntry &Entry : m_WarEntries)
	{
		if(str_comp(pName, Entry.m_aName) == 0 && str_comp(Entry.m_aName, "") != 0)
		{
			return Entry.m_pWarType->m_Index;
		}
	}
	return 0;
}

int CWarList::FindWarTypeWithClan(const char *pClan)
{
	for(CWarEntry &Entry : m_WarEntries)
	{
		if(str_comp(pClan, Entry.m_aClan) == 0 && str_comp(Entry.m_aClan, "") != 0)
		{
			return Entry.m_pWarType->m_Index;
		}
	}
	return 0;
}

char *CWarList::GetWarTypeName(int ClientId)
{
	for(CWarEntry &Entry : m_WarEntries)
	{
		if(!str_comp(GameClient()->m_aClients[ClientId].m_aName, Entry.m_aName) && str_comp(Entry.m_aName, "") != 0)
		{
			return Entry.m_pWarType->m_aWarName;
		}
		else if(!str_comp(GameClient()->m_aClients[ClientId].m_aClan, Entry.m_aClan) && str_comp(Entry.m_aClan, "") != 0)
		{
			return Entry.m_pWarType->m_aWarName;
		}
	}
	return nullptr;
}

CWarType *CWarList::FindWarType(const char *pType)
{
	CWarType Type(pType);
	auto it = std::find_if(m_WarTypes.begin(), m_WarTypes.end(),
		[&Type](CWarType *warTypePtr) { return *warTypePtr == Type; });
	if(it != m_WarTypes.end())
		return *it;
	else
		return m_pWarTypeNone;
}

CWarEntry *CWarList::FindWarEntry(const char *pName, const char *pClan, const char *pType)
{
	CWarType *WarType = FindWarType(pType);
	CWarEntry Entry(WarType, pName, pClan, "");
	auto it = std::find(m_WarEntries.begin(), m_WarEntries.end(), Entry);

	if(it != m_WarEntries.end())
		return &(*it);
	else
		return nullptr;
}

ColorRGBA CWarList::GetPriorityColor(int ClientId)
{
	if(m_WarPlayers[ClientId].IsWarClan && !m_WarPlayers[ClientId].IsWarName)
		return m_WarPlayers[ClientId].m_ClanColor;
	else
		return m_WarPlayers[ClientId].m_NameColor;
}

ColorRGBA CWarList::GetNameplateColor(int ClientId)
{
	return m_WarPlayers[ClientId].m_NameColor;
}

ColorRGBA CWarList::GetClanColor(int ClientId)
{
	return m_WarPlayers[ClientId].m_ClanColor;
}

bool CWarList::GetAnyWar(int ClientId)
{
	if(ClientId < 0)
		return false;
	return m_WarPlayers[ClientId].IsWarClan || m_WarPlayers[ClientId].IsWarName;
}

bool CWarList::GetNameWar(int ClientId)
{
	if(ClientId < 0)
		return false;
	return m_WarPlayers[ClientId].IsWarName;
}
bool CWarList::GetClanWar(int ClientId)
{
	if(ClientId < 0)
		return false;
	return m_WarPlayers[ClientId].IsWarClan;
}

void CWarList::GetReason(char *pReason, int ClientId)
{
	str_copy(pReason, m_WarPlayers[ClientId].m_aReason, sizeof(m_WarPlayers[ClientId].m_aReason));
}

CWarDataCache &CWarList::GetWarData(int ClientId)
{
	return m_WarPlayers[ClientId];
}

void CWarList::SortWarEntries()
{
	// TODO
}

void CWarList::UpdateWarPlayers()
{
	for(int i = 0; i < (int)m_WarTypes.size(); ++i)
		m_WarTypes[i]->m_Index = i;

	for(int i = 0; i < MAX_CLIENTS; ++i)
	{
		if(!GameClient()->m_aClients[i].m_Active)
			continue;

		m_WarPlayers[i].IsMuted = false; // E-Client [Mutes]

		m_WarPlayers[i].IsWarName = false;
		m_WarPlayers[i].IsWarClan = false;
		memset(m_WarPlayers[i].m_aReason, 0, sizeof(m_WarPlayers[i].m_aReason));
		m_WarPlayers[i].m_NameColor = ColorRGBA(1, 1, 1, 1);
		m_WarPlayers[i].m_ClanColor = ColorRGBA(1, 1, 1, 1);
		m_WarPlayers[i].m_WarGroupMatches.clear();
		m_WarPlayers[i].m_WarGroupMatches.resize((int)m_WarTypes.size(), false);

		for(CWarEntry &Entry : m_WarEntries)
		{
			if(str_comp(GameClient()->m_aClients[i].m_aName, Entry.m_aName) == 0 && str_comp(Entry.m_aName, "") != 0)
			{
				str_copy(m_WarPlayers[i].m_aReason, Entry.m_aReason);
				m_WarPlayers[i].IsWarName = true;
				m_WarPlayers[i].m_NameColor = Entry.m_pWarType->m_Color;
				m_WarPlayers[i].m_WarGroupMatches[Entry.m_pWarType->m_Index] = true;
			}
			else if(str_comp(GameClient()->m_aClients[i].m_aClan, Entry.m_aClan) == 0 && str_comp(Entry.m_aClan, "") != 0)
			{
				// Name war reason has priority over clan war reason
				if(!m_WarPlayers[i].IsWarName)
					str_copy(m_WarPlayers[i].m_aReason, Entry.m_aReason);

				m_WarPlayers[i].IsWarClan = true;
				m_WarPlayers[i].m_ClanColor = Entry.m_pWarType->m_Color;
				m_WarPlayers[i].m_WarGroupMatches[Entry.m_pWarType->m_Index] = true;
			}
		}

		for(CMuteEntry &Entry : m_MuteEntries) // E-Client [Mutes]
		{
			if(str_comp(GameClient()->m_aClients[i].m_aName, Entry.m_aMutedName) == 0 && str_comp(Entry.m_aMutedName, "") != 0)
			{
				m_WarPlayers[i].IsMuted = true;
			}
		}
	}
}

void CWarList::UpdateClientWarStates(int ClientId) 
{
    if(ClientId < 0 || ClientId >= MAX_CLIENTS)
        return;

    const int64_t Now = time_get();
    const int64_t UPDATE_INTERVAL = time_freq() * 0.5f;
    
    if(!m_aStatesDirty[ClientId] && Now - m_aLastUpdateTime[ClientId] < UPDATE_INTERVAL)
        return;

    bool WasPrevWar = GameClient()->m_aClients[ClientId].m_IsWar;
    bool WasPrevTeam = GameClient()->m_aClients[ClientId].m_IsTeam;
    bool WasPrevHelper = GameClient()->m_aClients[ClientId].m_IsHelper;

    // Reset states
    GameClient()->m_aClients[ClientId].m_IsWar = false;
    GameClient()->m_aClients[ClientId].m_IsTeam = false;
    GameClient()->m_aClients[ClientId].m_IsHelper = false;

    // Check all war entries
    for(const auto &Entry : m_WarEntries)
    {
        // Check name matches
        if(Entry.m_aName[0] && !str_comp(Entry.m_aName, GameClient()->m_aClients[ClientId].m_aName))
        {
            if(!str_comp(Entry.m_pWarType->m_aWarName, "enemy"))
                GameClient()->m_aClients[ClientId].m_IsWar = true;
            else if(!str_comp(Entry.m_pWarType->m_aWarName, "helper"))
                GameClient()->m_aClients[ClientId].m_IsHelper = true;
            else if(!str_comp(Entry.m_pWarType->m_aWarName, "team"))
                GameClient()->m_aClients[ClientId].m_IsTeam = true;
        }

        // Check clan matches 
        if(Entry.m_aClan[0] && !str_comp(Entry.m_aClan, GameClient()->m_aClients[ClientId].m_aClan))
        {
            if(!str_comp(Entry.m_pWarType->m_aWarName, "enemy"))
                GameClient()->m_aClients[ClientId].m_IsWar = true;
            else if(!str_comp(Entry.m_pWarType->m_aWarName, "helper"))
                GameClient()->m_aClients[ClientId].m_IsHelper = true;
            else if(!str_comp(Entry.m_pWarType->m_aWarName, "team"))
                GameClient()->m_aClients[ClientId].m_IsTeam = true;
        }
    }

    m_aStatesDirty[ClientId] = false;
    m_aLastUpdateTime[ClientId] = Now;

    if(WasPrevWar != GameClient()->m_aClients[ClientId].m_IsWar ||
       WasPrevTeam != GameClient()->m_aClients[ClientId].m_IsTeam ||
       WasPrevHelper != GameClient()->m_aClients[ClientId].m_IsHelper)
    {
        GameClient()->OnClientStateChange(ClientId);
    }
}

void CWarList::MarkClientStateDirty(int ClientId)
{
    if(ClientId >= 0 && ClientId < MAX_CLIENTS)
        m_aStatesDirty[ClientId] = true;
}

// Call this when adding/removing war entries
void CWarList::OnWarEntryChange()
{
    // Mark all clients as needing an update
    for(int i = 0; i < MAX_CLIENTS; i++)
        m_aStatesDirty[i] = true;
}

CWarList::~CWarList()
{
	for(CWarType *WarType : m_WarTypes)
		delete WarType;
	m_WarTypes.clear();
}

CWarList::CWarList()
{
	str_copy(m_WarTypes[0]->m_aWarName, "none");
	m_WarTypes[0]->m_Color = ColorRGBA(1, 1, 1, 1);
}

bool CWarList::RemoveEntryByName(int Type, const char* pName)
{
    // Type 1 = War, 2 = Team, 3 = Helper, others = 4 etc..
    if(Type < 1 || Type >= (int)m_WarTypes.size() || !pName)
        return false;

    bool Removed = false;
    for(auto it = m_WarEntries.begin(); it != m_WarEntries.end();)
    {
        if(it->m_pWarType == m_WarTypes[Type] && 
           ((str_comp(it->m_aName, pName) == 0 && str_comp(it->m_aName, "") != 0) ||
            (str_comp(it->m_aClan, pName) == 0 && str_comp(it->m_aClan, "") != 0)))
        {
            it = m_WarEntries.erase(it);
            Removed = true;
        }
        else
            ++it;
    }
    return Removed;
}

void CWarList::WriteLine(const char *pLine)
{
	if(!m_WarlistFile || io_write(m_WarlistFile, pLine, str_length(pLine)) != static_cast<unsigned>(str_length(pLine)) || !io_write_newline(m_WarlistFile))
		return;
}

static void EscapeParam(char *pDst, const char *pSrc, int Size)
{
	str_escape(&pDst, pSrc, pDst + Size);
}

void CWarList::ConfigSaveCallback(IConfigManager *pConfigManager, void *pUserData)
{
	CWarList *pThis = (CWarList *)pUserData;
	bool Failed = false;
	pThis->m_WarlistFile = pThis->m_pStorage->OpenFile(WARLIST_FILE, IOFLAG_WRITE, IStorage::TYPE_SAVE);

	if(!pThis->m_WarlistFile)
	{
		dbg_msg("config", "ERROR: opening %s failed", WARLIST_FILE);
		return;
	}

	char aBuf[1024];
	for(int i = 0; i < static_cast<int>(pThis->m_WarTypes.size()); i++)
	{
		CWarType &WarType = *pThis->m_WarTypes[i];

		// Imported wartypes don't get saved
		if(WarType.m_Imported)
			continue;

		char aEscapeType[MAX_WARLIST_TYPE_LENGTH * 2];
		EscapeParam(aEscapeType, WarType.m_aWarName, sizeof(aEscapeType));
		ColorHSLA Color = color_cast<ColorHSLA>(WarType.m_Color);

		str_format(aBuf, sizeof(aBuf), "update_war_group %d \"%s\" %d", i, aEscapeType, Color.Pack(false));
		pThis->WriteLine(aBuf);
	}
	for(CWarEntry &Entry : pThis->m_WarEntries)
	{
		// Imported entries don't get saved
		if(Entry.m_Imported)
			continue;

		char aEscapeType[MAX_WARLIST_TYPE_LENGTH * 2];
		char aEscapeName[MAX_NAME_LENGTH * 2];
		char aEscapeClan[MAX_CLAN_LENGTH * 2];
		char aEscapeReason[MAX_WARLIST_REASON_LENGTH * 2];
		EscapeParam(aEscapeType, Entry.m_pWarType->m_aWarName, sizeof(aEscapeType));
		EscapeParam(aEscapeName, Entry.m_aName, sizeof(aEscapeName));
		EscapeParam(aEscapeClan, Entry.m_aClan, sizeof(aEscapeClan));
		EscapeParam(aEscapeReason, Entry.m_aReason, sizeof(aEscapeReason));

		str_format(aBuf, sizeof(aBuf), "add_war_entry \"%s\" \"%s\" \"%s\" \"%s\"", aEscapeType, aEscapeName, aEscapeClan, aEscapeReason);
		pThis->WriteLine(aBuf);
	}
	for(CMuteEntry &Entry : pThis->m_MuteEntries)
	{
		char aEscapeName[MAX_NAME_LENGTH * 2];
		EscapeParam(aEscapeName, Entry.m_aMutedName, sizeof(aEscapeName));

		str_format(aBuf, sizeof(aBuf), "add_mute \"%s\"", aEscapeName);
		pThis->WriteLine(aBuf);
	}

	if(io_sync(pThis->m_WarlistFile) != 0)
		Failed = true;
	if(io_close(pThis->m_WarlistFile) != 0)
		Failed = true;
	pThis->m_WarlistFile = {};
	if(Failed)
		dbg_msg("config", "ERROR: writing to %s failed", WARLIST_FILE);
}

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <curl/curl.h>

void CWarList::ParseWebhookUrls()
{
    m_Webhooks.clear();
    m_Webhooks.resize(g_Config.m_ClDiscordWebhookCount);

    char aUrls[2560];
    str_copy(aUrls, g_Config.m_ClDiscordWebhookUrls);
    
    char *pUrl = aUrls;
    char *pSavePtr = nullptr;
    int WebhookIndex = 0;
    
    // Split by semicolon
    pUrl = strtok_r(pUrl, ";", &pSavePtr);
    while(pUrl && WebhookIndex < g_Config.m_ClDiscordWebhookCount)
    {
        str_copy(m_Webhooks[WebhookIndex].m_aUrl, pUrl, sizeof(WebhookInfo::m_aUrl));
        m_Webhooks[WebhookIndex].m_Valid = true;
        
        WebhookIndex++;
        pUrl = strtok_r(nullptr, ";", &pSavePtr);
    }

    // Debug output
    dbg_msg("warlist", "Parsed %d webhook URLs:", WebhookIndex);
    for(int i = 0; i < WebhookIndex; i++)
    {
        if(m_Webhooks[i].m_Valid)
            dbg_msg("warlist", "Webhook %d: %s", i+1, m_Webhooks[i].m_aUrl);
    }
}

const char* CWarList::GetWebhookUrl(int Index)
{
    if(Index < 0 || Index >= (int)m_Webhooks.size())
    {
        dbg_msg("warlist", "Invalid webhook index: %d", Index);
        return nullptr;
    }

    if(!m_Webhooks[Index].m_Valid || !m_Webhooks[Index].m_aUrl[0])
    {
        dbg_msg("warlist", "No valid webhook URL at index %d", Index);
        return nullptr;
    }

    dbg_msg("warlist", "Getting webhook URL for index %d: %s", Index, m_Webhooks[Index].m_aUrl);
    return m_Webhooks[Index].m_aUrl;
}

void CWarList::SaveWebhookUrls()
{
    char aUrls[2560] = {0};
    int Offset = 0;
    
    for(size_t i = 0; i < m_Webhooks.size(); i++)
    {
        if(m_Webhooks[i].m_Valid)
        {
            if(Offset > 0)
                str_append(aUrls, ";", sizeof(aUrls));
                
            str_append(aUrls, m_Webhooks[i].m_aUrl, sizeof(aUrls));
        }
    }
    
    str_copy(g_Config.m_ClDiscordWebhookUrls, aUrls);
}

static int ColorToInt(const ColorRGBA &Color)
{
    int r = static_cast<int>(Color.r * 255);
    int g = static_cast<int>(Color.g * 255);
    int b = static_cast<int>(Color.b * 255);
    return (r << 16) | (g << 8) | b;
}

#include <ctime>

void getCurrentLocalTime(char *pBuffer, size_t bufferSize)
{
    time_t now = time(nullptr);
#if defined(_WIN32) || defined(_WIN64)
    struct tm localTime;
    if(localtime_s(&localTime, &now) != 0)
    {
        strncpy(pBuffer, "Unknown Time", bufferSize);
        return;
    }
    strftime(pBuffer, bufferSize, "%Y-%m-%d %H:%M:%S", &localTime);
#else
    struct tm localTime;
    if(localtime_r(&now, &localTime) == nullptr)
    {
        strncpy(pBuffer, "Unknown Time", bufferSize);
        return;
    }
    strftime(pBuffer, bufferSize, "%Y-%m-%d %H:%M:%S", &localTime);
#endif
}


void CWarList::SendDiscordLog(const char *pActor, const char *pWarType, const char *pTarget, const char *pClan)
{
    if(!g_Config.m_ClDiscordWebhooks)
        return;

    const char* pWebhookUrl = nullptr;
    
    // First try to find webhook from scheme
    char aScheme[128];
    str_copy(aScheme, g_Config.m_ClDiscordWebhookScheme);
    char *pToken = strtok(aScheme, ";");
    
    while(pToken)
    {
        char aType[32] = {0};
        int WebhookIndex = 0;
        
        if(sscanf(pToken, "%31[^:]:%d", aType, &WebhookIndex) == 2)
        {
            if(str_comp(aType, pWarType) == 0)
            {
                pWebhookUrl = GetWebhookUrl(WebhookIndex - 1);
                break;
            }
            else if(aType[0] == pWarType[0] && !pWebhookUrl)
            {
                pWebhookUrl = GetWebhookUrl(WebhookIndex - 1);
            }
        }
        pToken = strtok(NULL, ";");
    }

    // Fallback to first webhook if none found
    if(!pWebhookUrl || !pWebhookUrl[0])
        pWebhookUrl = GetWebhookUrl(0);
        
    // Check if we have a valid URL
    if(!pWebhookUrl || !pWebhookUrl[0] || str_length(pWebhookUrl) < 5)
    {
        dbg_msg("warlist", "No valid webhook URL found");
        return;
    }

    // Verify webhook URL starts with https://
    if(str_comp_num(pWebhookUrl, "https://", 8) != 0)
    {
        dbg_msg("warlist", "Invalid webhook URL format");
        return;
    }

    // Get color for war type
    int embedColor = 0xffffff;
    for(auto &pType : m_WarTypes)
    {
        if(str_comp(pType->m_aWarName, pWarType) == 0)
        {
            embedColor = ColorToInt(pType->m_Color);
            break;
        }
    }

    char timeStr[100];
    getCurrentLocalTime(timeStr, sizeof(timeStr));

    const char *extraFieldName = (pClan && pClan[0] != '\0') ? "Clan" : "Target";
    const char *extraFieldValue = (pClan && pClan[0] != '\0') ? pClan : pTarget;

    // Build JSON payload
    char jsonPayload[2048];
    int written = snprintf(
        jsonPayload, sizeof(jsonPayload),
        "{"
        "  \"username\": \"FeX Warlog\","
        "  \"embeds\": ["
        "    {"
        "      \"title\": \"War Log Addition\","
        "      \"color\": %d,"
        "      \"fields\": ["
        "        { \"name\": \"Actor\", \"value\": \"%s\", \"inline\": true },"
        "        { \"name\": \"War Type\", \"value\": \"%s\", \"inline\": true },"
        "        { \"name\": \"%s\", \"value\": \"%s\", \"inline\": true }"
        "      ],"
        "      \"footer\": { \"text\": \"%s\" }"
        "    }"
        "  ]"
        "}",
        embedColor, pActor, pWarType, extraFieldName, extraFieldValue, timeStr
    );

    if(written < 0 || written >= (int)sizeof(jsonPayload))
    {
        dbg_msg("warlist", "JSON payload formatting error");
        return;
    }

    // Send webhook
    CURL *curl = curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, pWebhookUrl);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonPayload);

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Add timeout
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
        
        // Enable debug messages
        dbg_msg("warlist", "Sending webhook to: %s", pWebhookUrl);
        dbg_msg("warlist", "Payload: %s", jsonPayload);

        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK)
        {
            dbg_msg("warlist", "Webhook failed: %s", curl_easy_strerror(res));
        }
        else
        {
            long httpCode = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
            if(httpCode != 204 && httpCode != 200)
                dbg_msg("warlist", "Webhook failed with HTTP code: %d", httpCode);
            else
                dbg_msg("warlist", "Webhook sent successfully");
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    else
    {
        dbg_msg("warlist", "Failed to initialize CURL");
    }
}
void CWarList::SendDiscordLogRemoval(const char *pActor, const char *pWarType, const char *pTarget, const char *pClan)
{
    if(!g_Config.m_ClDiscordWebhooks)
        return;

    const char* pWebhookUrl = nullptr;
    
    // First try to find webhook from scheme
    char aScheme[128];
    str_copy(aScheme, g_Config.m_ClDiscordWebhookScheme);
    char *pToken = strtok(aScheme, ";");
    
    while(pToken)
    {
        char aType[32] = {0};
        int WebhookIndex = 0;
        
        if(sscanf(pToken, "%31[^:]:%d", aType, &WebhookIndex) == 2)
        {
            if(str_comp(aType, pWarType) == 0)
            {
                pWebhookUrl = GetWebhookUrl(WebhookIndex - 1);
                break;
            }
            else if(aType[0] == pWarType[0] && !pWebhookUrl)
            {
                pWebhookUrl = GetWebhookUrl(WebhookIndex - 1);
            }
        }
        pToken = strtok(NULL, ";");
    }

    // Fallback to first webhook if none found
    if(!pWebhookUrl || !pWebhookUrl[0])
        pWebhookUrl = GetWebhookUrl(0);
        
    // Check if we have a valid URL
    if(!pWebhookUrl || !pWebhookUrl[0] || str_length(pWebhookUrl) < 5)
    {
        dbg_msg("warlist", "No valid webhook URL found");
        return;
    }

    // Verify webhook URL starts with https://
    if(str_comp_num(pWebhookUrl, "https://", 8) != 0)
    {
        dbg_msg("warlist", "Invalid webhook URL format");
        return;
    }

    // Get color for war type
    int embedColor = 0xffffff;
    for(auto &pType : m_WarTypes)
    {
        if(str_comp(pType->m_aWarName, pWarType) == 0)
        {
            embedColor = ColorToInt(pType->m_Color);
            break;
        }
    }

    char timeStr[100];
    getCurrentLocalTime(timeStr, sizeof(timeStr));

    const char *extraFieldName = (pClan && pClan[0] != '\0') ? "Clan" : "Target";
    const char *extraFieldValue = (pClan && pClan[0] != '\0') ? pClan : pTarget;

    // Build JSON payload
    char jsonPayload[2048];
    int written = snprintf(
        jsonPayload, sizeof(jsonPayload),
        "{"
        "  \"username\": \"FeX Warlog\","
        "  \"embeds\": ["
        "    {"
        "      \"title\": \"War Log Deletion\","
        "      \"color\": %d,"
        "      \"fields\": ["
        "        { \"name\": \"Actor\", \"value\": \"%s\", \"inline\": true },"
        "        { \"name\": \"War Type\", \"value\": \"%s\", \"inline\": true },"
        "        { \"name\": \"%s\", \"value\": \"%s\", \"inline\": true }"
        "      ],"
        "      \"footer\": { \"text\": \"%s\" }"
        "    }"
        "  ]"
        "}",
        embedColor, pActor, pWarType, extraFieldName, extraFieldValue, timeStr
    );

    if(written < 0 || written >= (int)sizeof(jsonPayload))
    {
        dbg_msg("warlist", "JSON payload formatting error");
        return;
    }

    // Send webhook
    CURL *curl = curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, pWebhookUrl);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonPayload);

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Add timeout
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
        
        // Enable debug messages
        dbg_msg("warlist", "Sending webhook to: %s", pWebhookUrl);
        dbg_msg("warlist", "Payload: %s", jsonPayload);

        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK)
        {
            dbg_msg("warlist", "Webhook failed: %s", curl_easy_strerror(res));
        }
        else
        {
            long httpCode = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
            if(httpCode != 204 && httpCode != 200)
                dbg_msg("warlist", "Webhook failed with HTTP code: %d", httpCode);
            else
                dbg_msg("warlist", "Webhook sent successfully");
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    else
    {
        dbg_msg("warlist", "Failed to initialize CURL");
    }
}

#include <thread>
#include <string>

void CWarList::SendDiscordLogAsync(const char *pActor, const char *pWarType, const char *pTarget, const char *pClan)
{
    std::string sActor(pActor);
    std::string sWarType(pWarType);
    std::string sTarget(pTarget);
    std::string sClan(pClan);

    std::thread([this, sActor, sWarType, sTarget, sClan]() {
        this->SendDiscordLog(sActor.c_str(), sWarType.c_str(), sTarget.c_str(), sClan.c_str());
    }).detach();
}

void CWarList::SendDiscordLogAsyncRemoval(const char *pActor, const char *pWarType, const char *pTarget, const char *pClan)
{
    std::string sActor(pActor);
    std::string sWarType(pWarType);
    std::string sTarget(pTarget);
    std::string sClan(pClan);

    std::thread([this, sActor, sWarType, sTarget, sClan]() {
        this->SendDiscordLogRemoval(sActor.c_str(), sWarType.c_str(), sTarget.c_str(), sClan.c_str());
    }).detach();
}