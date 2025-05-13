#ifndef GAME_CLIENT_COMPONENTS_FEX_FEXWARLIST_H
#define GAME_CLIENT_COMPONENTS_FEX_FEXWARLIST_H

#include <engine/console.h>
#include <engine/shared/protocol.h>
#include <game/client/component.h>

#define WARLIST_FILE "fex_wars.cfg"

enum
{
	MAX_WARLIST_TYPE_LENGTH = 10,
	MAX_WARLIST_IMPORT_ID_LENGTH = 16,
	MAX_WARLIST_REASON_LENGTH = 256,

	MAX_WARS = 4028
};

// TODO, add chat prefix
class CWarType
{
public:
	// Intentionally named redundantly because it was confusing otherwise
	char m_aWarName[MAX_WARLIST_TYPE_LENGTH] = "";
	ColorRGBA m_Color = ColorRGBA(1, 1, 1, 1);
	bool m_Removable = true;
	bool m_Imported = false;
	int m_Index = 0;
	CWarType(const char *pName, ColorRGBA Color = ColorRGBA(1, 1, 1, 1), bool Removable = true, bool IsImport = false)
	{
		str_copy(m_aWarName, pName);
		m_Color = Color;
		m_Removable = Removable;
		m_Imported = IsImport;
	}

	bool operator==(const CWarType &Other) const
	{
		return str_comp(m_aWarName, Other.m_aWarName) == 0;
	}
};

class CWarEntry
{
public:
	// a war entry can have a name, or clan, but not both
	// name matches the user with that name
	// clan matches all users with that clan
	char m_aName[MAX_NAME_LENGTH] = "";
	char m_aClan[MAX_CLAN_LENGTH] = "";
	char m_aReason[MAX_WARLIST_REASON_LENGTH] = "";

	CWarType *m_pWarType = nullptr;
	bool m_Imported = false;

	const CServerInfo *m_ServerInfo = nullptr;

	CWarEntry(CWarType *pWarType)
	{
		m_pWarType = pWarType;
	}

	CWarEntry(CWarType *pWarType, const char *pName, const char *pClan, const char *pReason, bool IsImport = false)
	{
		m_pWarType = pWarType;
		str_copy(m_aName, pName);
		str_copy(m_aClan, pClan);
		str_copy(m_aReason, pReason);
		m_Imported = IsImport;
	}

	bool operator==(const CWarEntry &Other) const
	{
		bool NameMatch = str_comp(m_aName, Other.m_aName) == 0 && str_comp(m_aName, "") != 0;
		bool ClanMatch = str_comp(m_aClan, Other.m_aClan) == 0 && str_comp(m_aClan, "") != 0;
		return (NameMatch || ClanMatch) && m_pWarType == Other.m_pWarType;
	}
};

// E-Client [Mutes]
class CMuteEntry
{
public:
	char m_aMutedName[MAX_NAME_LENGTH] = "";

	CMuteEntry(const char *pName)
	{
		str_copy(m_aMutedName, pName);
	}

	bool operator==(const CMuteEntry &Other) const
	{
		return !str_comp(m_aMutedName, Other.m_aMutedName);
	}
};

class CWarDataCache
{
public:
	ColorRGBA m_NameColor = ColorRGBA(1, 1, 1, 1);
	ColorRGBA m_ClanColor = ColorRGBA(1, 1, 1, 1);
	bool IsWarName = false;
	bool IsWarClan = false;

	bool IsMuted = false; // E-Client [Mutes]

	std::vector<char> m_WarGroupMatches = {false, false, false, false};

	char m_aReason[MAX_WARLIST_REASON_LENGTH] = "";
};

class CWarList : public CComponent
{
	// The war list will have these commands
	//
	// Preset Commands
	// .war [name] [reason]
	// .clanwar [name] [reason]
	// .team [name] [reason]
	// .clanteam [name] [reason]
	// .delwar [name]
	// .delteam [name]
	// .delclanwar [name]
	// .delclanteam [team]
	//
	// Generic Commands
	// .name [type] [name] [reason]
	// .clan [type] [clan] [reason]
	// .delname [type] [name]
	// .delclan [type] [clan]
	//
	// Backend commands
	// update_war_group [index] [type] [color]
	// add_war_entry [type] [name] [clan] [reason]

	// Preset war Commands
	static void ConNameIndex(IConsole::IResult *pResult, void *pUserData);
	static void ConClanIndex(IConsole::IResult *pResult, void *pUserData);
	static void ConRemoveNameIndex(IConsole::IResult *pResult, void *pUserData);
	static void ConRemoveClanIndex(IConsole::IResult *pResult, void *pUserData);

	static void ConNameTeam(IConsole::IResult *pResult, void *pUserData);
	static void ConClanTeam(IConsole::IResult *pResult, void *pUserData);
	static void ConRemoveNameWar(IConsole::IResult *pResult, void *pUserData);
	static void ConRemoveNameTeam(IConsole::IResult *pResult, void *pUserData);
	static void ConRemoveClanWar(IConsole::IResult *pResult, void *pUserData);
	static void ConRemoveClanTeam(IConsole::IResult *pResult, void *pUserData);

	// Generic Commands
	static void ConName(IConsole::IResult *pResult, void *pUserData);
	static void ConClan(IConsole::IResult *pResult, void *pUserData);
	static void ConRemoveName(IConsole::IResult *pResult, void *pUserData);
	static void ConRemoveClan(IConsole::IResult *pResult, void *pUserData);

	// E-Client
	static void ConAddMute(IConsole::IResult *pResult, void *pUserData);
	static void ConDelMute(IConsole::IResult *pResult, void *pUserData);

	// Backend Commands for config file
	static void ConAddWarEntry(IConsole::IResult *pResult, void *pUserData);
	static void ConUpsertWarType(IConsole::IResult *pResult, void *pUserData);

	// E-Client
	static void ConAddMuteEntry(IConsole::IResult *pResult, void *pUserData);

	static void ConfigSaveCallback(IConfigManager *pConfigManager, void *pUserData);

	void WriteLine(const char *pLine);
	class IStorage *m_pStorage = nullptr;
	IOHANDLE m_WarlistFile = nullptr;

public:
	CWarList();
	void OnWarEntryChange();
	~CWarList();

	/*
	* duplicate war types are NOT allowed
	* 0 = none
	* 1 = enemy
	* 2 = team
	* 3 = helper
	*/
	std::vector<CWarType *> m_WarTypes = {
		new CWarType("none", ColorRGBA(1.0f, 1.0f, 1.0f, 1.0f), false), // 0
		new CWarType("enemy", ColorRGBA(1.0f, 0.2f, 0.2f, 1.0f), false), // 1
		new CWarType("team", ColorRGBA(0.0f, 0.9f, 0.2f, 1.0f), false), // 2
		new CWarType("helper", ColorRGBA(0.9f, 0.87f, 0.2f, 1.0f), false), // 3
	};

	// E-Client [Mutes]
	std::vector<CMuteEntry> m_MuteEntries;

	// None type war entries will float to the top of the list, so they can be assigned a type
	CWarType *m_pWarTypeNone = m_WarTypes[0];

	// Duplicate war entries ARE allowed
	std::vector<CWarEntry> m_WarEntries;
	// TODO: create an unordered map for war clans and war names, to speed up updating the WarPlayers cache
	// It should be updated when m_WarList changes

	CWarDataCache m_WarPlayers[MAX_CLIENTS];

	virtual int Sizeof() const override { return sizeof(*this); }
	virtual void OnNewSnapshot() override;
	virtual void OnConsoleInit() override;

	void UpdateWarPlayers();

	void UpdateWarEntry(int Index, const char *pName, const char *pClan, const char *pReason, CWarType *pType);

	// Adds a new war entry if the specified index is not found
	void UpsertWarType(int Index, const char *pType, ColorRGBA Color);

	void AddWarEntryInGame(int WarType, const char *pName, const char *pReason, bool IsClan);
	void RemoveWarEntryInGame(int WarType, const char *pName, bool IsClan);

	// E-Client
	void AddMuteEntry(const char *pName); // E-Client [Mutes]
	void AddMute(const char *pName);
	void DelMute(const char *pName, bool Silent = false);

	int FindWarTypeWithName(const char *pName);
	int FindWarTypeWithClan(const char *pClan);
	char *GetWarTypeName(int ClientId);

	void AddWarEntry(const char *pName, const char *pClan, const char *pReason, const char *pType);
	void AddWarType(const char *pType, ColorRGBA Color);

	void RemoveWarEntry(const char *pName, const char *pClan, const char *pType);
	void RemoveWarType(const char *pType);

	void RemoveWarEntryDuplicates(const char *pName, const char *pClan);

	void RemoveWarEntry(CWarEntry *Entry);

	void RemoveWarEntry(int Index);
	void RemoveWarType(int Index);

	ColorRGBA GetPriorityColor(int ClientId);
	ColorRGBA GetNameplateColor(int ClientId);
	ColorRGBA GetClanColor(int ClientId);
	bool GetAnyWar(int ClientId);
	bool GetNameWar(int ClientId);
	bool GetClanWar(int ClientId);

	void GetReason(char *pReason, int ClientId);
	CWarDataCache &GetWarData(int ClientId);

	void SortWarEntries();

	CWarType *FindWarType(const char *pType);
	CWarEntry *FindWarEntry(const char *pName, const char *pClan, const char *pType);

	bool RemoveEntryByName(int Type, const char *pName);
	void UpdateClientWarStates(int ClientId);

	void MarkClientStateDirty(int ClientId);

	void SendDiscordLog(const char *pActor, const char *pWarType, const char *pTarget, const char *pClan);

	void SendDiscordLogRemoval(const char *pActor, const char *pWarType, const char *pTarget, const char *pClan);

	void SendDiscordLogAsync(const char *pActor, const char *pWarType, const char *pTarget, const char *pClan);

	void SendDiscordLogAsyncRemoval(const char *pActor, const char *pWarType, const char *pTarget, const char *pClan);

    int64_t m_aLastUpdateTime[MAX_CLIENTS];
    bool m_aStatesDirty[MAX_CLIENTS];

	struct WebhookInfo
    {
        char m_aUrl[256];
        bool m_Valid;
    };
    
    std::vector<WebhookInfo> m_Webhooks;
    void ParseWebhookUrls();
    const char* GetWebhookUrl(int Index);
    void SaveWebhookUrls();
};

#endif