#ifndef GAME_CLIENT_COMPONENTS_FEX_FEX_H
#define GAME_CLIENT_COMPONENTS_FEX_FEX_H

#include <game/client/component.h>
#include <engine/console.h>
#include <base/system.h>
#include <vector>

class CTempEntry
{
public:
	// name matches the user with that name
	char m_aTempWar[16] = "";
	char m_aTempHelper[16] = "";
	char m_aTempMute[16] = "";

	CTempEntry(const char *pTempWar, const char *pTempHelper, const char *pTempMute)
	{
		if(!str_comp(pTempWar, ""))
			str_copy(m_aTempWar, pTempWar);
		if(!str_comp(pTempHelper, ""))
			str_copy(m_aTempHelper, pTempHelper);
		if(!str_comp(pTempMute, ""))
			str_copy(m_aTempMute, pTempMute);
	}

	bool operator==(const CTempEntry &Other) const
	{
		return !str_comp(m_aTempWar, Other.m_aTempWar) || !str_comp(m_aTempHelper, Other.m_aTempHelper) || !str_comp(m_aTempMute, Other.m_aTempMute);
	}

};

class CTempData
{
public:
	bool IsTempWar = false;
	bool IsTempHelper = false;
	bool IsTempMute = false;
};

class CFex : public CComponent
{
public:
    void TempWar(const char *pName);
	void UnTempWar(const char *pName, bool Silent = false);

	void TempHelper(const char *pName);
	void UnTempHelper(const char *pName, bool Silent = false);

	void TempMute(const char *pName);
	void UnTempMute(const char *pName, bool Silent = false);

    bool IsSpecialClan(const char *pClanName);

	static void ConTempWar(IConsole::IResult *pResult, void *pUserData);
	static void ConUnTempWar(IConsole::IResult *pResult, void *pUserData);

	static void ConTempHelper(IConsole::IResult *pResult, void *pUserData);
	static void ConUnTempHelper(IConsole::IResult *pResult, void *pUserData);

	static void ConTempMute(IConsole::IResult *pResult, void *pUserData);
	static void ConUnTempMute(IConsole::IResult *pResult, void *pUserData);


private:
    static constexpr const char* SPECIAL_CLAN = "ɢαиsτα";

public:
	// Temporary War Entries
	std::vector<CTempEntry> m_TempEntries;
	CTempData m_TempPlayers[MAX_CLIENTS];
	void UpdateTempPlayers();
    virtual void OnConsoleInit() override;
    void ProcessAutoMessage();
    void DisplayRandomClans();
    virtual void OnRender() override;
    static void ConOnlineInfo(IConsole::IResult *pResult, void *pUserData);
    static void ConPlayerInfo(IConsole::IResult *pResult, void *pUserData);
    static void ConAutoMessage(IConsole::IResult *pResult, void *pUserData);
    void OnlineInfo(bool Integrate = false);
	void RemoveWarEntryDuplicates(const char *pName);
	void RemoveWarEntry(const char *pNameW, const char *pNameH, const char *pNameM);
    int IdWithName(const char *pName);
    void PlayerInfo(const char *pName);


	// FeX Autojoins
	// int64_t m_AutoJoinTeamTick;
	int64_t m_AutoJoinDummyTick;
	bool m_OnAttemptingDummyJoin;
	int m_LastPlayerCount;
	// bool m_AutoJoinTeamAttempted;
	bool m_AutoJoinDummyAttempted;
	bool m_ServerJustJoined;
	int64_t m_AutoJoinDummySwitchTick;
	bool m_FirstTimerExpired = false;
	bool m_HasSwitchedBack = false;
	void CheckPlayerLeave();

private:
	virtual int Sizeof() const override { return sizeof(*this); }
    virtual void OnNewSnapshot() override;
    virtual void OnInit() override;
    virtual void OnStateChange(int NewState, int OldState) override;

	// // Auto message
    // bool m_AutoMessageEnabled;
    // int64_t m_LastMessageTick;
    // int m_MessageCount;
    // int64_t m_MessageResetTick;
    // std::vector<int> m_MessageTargets;
    // char m_CurrentMessage[256];
    // bool m_IsWhisper;
    // int m_CurrentTargetIndex;
    // bool m_IsClanMode;
    // char m_SingleTarget[MAX_NAME_LENGTH];

    // void SendAutoMessage();
    // bool IsValidTarget(int ClientID);
    // void RefreshTargetList();

    // int64_t m_LastAuthCheck;
    // void CheckAuthorizedPlayers();

	// char m_OriginalName[MAX_NAME_LENGTH];
    // void RandomizeName();
    // void RestoreOriginalName();

	// int64_t m_LastNameChangeTick;
    // bool m_NameJustChanged;

	// bool m_IsRandomName;
};

#endif // FEX_H
