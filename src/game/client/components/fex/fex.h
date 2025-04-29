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
	char m_aReason[128] = "";

	/*
	* Type = 0 -> TempWar
	* Type = 1 -> TempHelper
	* type = 2 -> TempMute
	*/
	CTempEntry(int Type, const char *pName, const char *pReason)
	{
		if(Type == 0)
			str_copy(m_aTempWar, pName);
		else if(Type == 1)
			str_copy(m_aTempHelper, pName);
		else if(Type == 2)
			str_copy(m_aTempMute, pName);

		if(!str_comp(pReason, ""))
			str_copy(m_aReason, pReason);
	}

	bool operator==(const CTempEntry &Other) const
	{
		bool TempWarMatch = !str_comp(m_aTempWar, Other.m_aTempWar) && str_comp(m_aTempWar, "") != 0;
		bool TempHelperMatch = !str_comp(m_aTempHelper, Other.m_aTempHelper) && str_comp(m_aTempHelper, "") != 0;
		bool TempMuteMatch = !str_comp(m_aTempMute, Other.m_aTempMute) && str_comp(m_aTempHelper, "") != 0;
		return (TempWarMatch || TempHelperMatch || TempMuteMatch);
	}
};

class CTempData
{
public:
	bool IsTempWar = false;
	bool IsTempHelper = false;
	bool IsTempMute = false;

	char m_aReason[128] = "";
};
class CFex : public CComponent
{
public:
	void TempWar(const char *pName, const char *pReason, bool Silent = false);
	void TempHelper(const char *pName, const char *pReason, bool Silent = false);
	void TempMute(const char *pName, bool Silent = false);

	bool UnTempHelper(const char *pName, bool Silent = false);
	bool UnTempWar(const char *pName, bool Silent = false);
	bool UnTempMute(const char *pName, bool Silent = false);

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
	void RemoveWarEntryDuplicates(const char *pName);
	void RemoveWarEntry(int Type, const char *pName);
    virtual void OnConsoleInit() override;
    void ProcessAutoMessage();
    void DisplayRandomClans();
    virtual void OnRender() override;
    static void ConOnlineInfo(IConsole::IResult *pResult, void *pUserData);
    static void ConPlayerInfo(IConsole::IResult *pResult, void *pUserData);
    static void ConAutoMessage(IConsole::IResult *pResult, void *pUserData);
    void OnlineInfo(bool Integrate = false);
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
};

#endif // FEX_H
