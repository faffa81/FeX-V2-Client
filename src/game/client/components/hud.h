/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_CLIENT_COMPONENTS_HUD_H
#define GAME_CLIENT_COMPONENTS_HUD_H
#include <engine/client.h>
#include <engine/shared/protocol.h>
#include <engine/textrender.h>
#include <game/client/component.h>
#include <game/generated/protocol.h>

struct SScoreInfo
{
	SScoreInfo()
	{
		Reset();
	}

	void Reset()
	{
		m_TextRankContainerIndex.Reset();
		m_TextScoreContainerIndex.Reset();
		m_RoundRectQuadContainerIndex = -1;
		m_OptionalNameTextContainerIndex.Reset();
		m_aScoreText[0] = 0;
		m_aRankText[0] = 0;
		m_aPlayerNameText[0] = 0;
		m_ScoreTextWidth = 0.f;
		m_Initialized = false;
	}

	STextContainerIndex m_TextRankContainerIndex;
	STextContainerIndex m_TextScoreContainerIndex;
	float m_ScoreTextWidth;
	char m_aScoreText[16];
	char m_aRankText[16];
	char m_aPlayerNameText[MAX_NAME_LENGTH];
	int m_RoundRectQuadContainerIndex;
	STextContainerIndex m_OptionalNameTextContainerIndex;

	bool m_Initialized;
};

class CHud : public CComponent
{
	float m_Width, m_Height;

	int m_HudQuadContainerIndex;
	SScoreInfo m_aScoreInfo[2];
	STextContainerIndex m_FPSTextContainerIndex;
	STextContainerIndex m_DDRaceEffectsTextContainerIndex;
	STextContainerIndex m_PlayerAngleTextContainerIndex;
	char m_aPlayerAngleText[128];
	STextContainerIndex m_aPlayerSpeedTextContainers[2];
	char m_aaPlayerSpeedText[2][128];
	int m_aPlayerSpeed[2];
	enum class ESpeedChange
	{
		NONE,
		INCREASE,
		DECREASE
	};
	ESpeedChange m_aLastPlayerSpeedChange[2];
	STextContainerIndex m_aPlayerPositionContainers[2];
	char m_aaPlayerPositionText[2][128];


	void RenderCursor();

	void RenderTextInfo();
	void RenderConnectionWarning();
	void RenderTeambalanceWarning();
	void RenderSpectatorChallengeOverlay();
	void RenderVoting();

	void PrepareAmmoHealthAndArmorQuads();
	void RenderAmmoHealthAndArmor(const CNetObj_Character *pCharacter);

	void PreparePlayerStateQuads();
	void RenderPlayerState(int ClientId);

	void RenderNotification();

	void ShowSoloState(int State);

	int m_LastSpectatorCountTick;
	void RenderSpectatorCount();
	void RenderDummyActions();
	void RenderMovementInformation();

	void UpdateMovementInformationTextContainer(STextContainerIndex &TextContainer, float FontSize, float Value, char *pPrevValue, size_t Size);
	void RenderMovementInformationTextContainer(STextContainerIndex &TextContainer, const ColorRGBA &Color, float X, float Y);

	void RenderGameTimer();
	void RenderPauseNotification();
	void RenderSuddenDeath();

	void RenderScoreHud();
	int m_LastLocalClientId = -1;

	void RenderSpectatorHud();
	void RenderWarmupTimer();
	void RenderLocalTime(float x);

	static constexpr float MOVEMENT_INFORMATION_LINE_HEIGHT = 8.0f;

public:
	CHud();
	virtual int Sizeof() const override { return sizeof(*this); }

	void ResetHudContainers();
	virtual void OnWindowResize() override;
	virtual void OnReset() override;
	virtual bool OnInput(const IInput::CEvent &Event) override;
	vec2 WorldToScreen(vec2 WorldPos);
	virtual void OnRender() override;
	virtual void OnInit() override;
	void Render1v1Hud();
	virtual void OnNewSnapshot() override;

	// DDRace

	virtual void OnMessage(int MsgType, void *pRawMsg) override;
	void RenderNinjaBarPos(float x, float y, float Width, float Height, float Progress, float Alpha = 1.0f);

	void ShowNotification(const char *pText, float Duration = 2.5f, float FadeOutTime = 1.5f, ColorRGBA BgColor = ColorRGBA(0.f,0.f,0.f,0.25), ColorRGBA TextColor = ColorRGBA(1.f,1.f,1.f,1.f));

private:
	void RenderRecord();
	void RenderSpectatorQuickActions();
	void RenderDDRaceEffects();
	float m_TimeCpDiff;
	float m_ServerRecord;
	float m_aPlayerRecord[NUM_DUMMIES];
	float m_FinishTimeDiff;
	int m_DDRaceTime;
	int m_FinishTimeLastReceivedTick;
	int m_TimeCpLastReceivedTick;
	bool m_ShowFinishTime;

	int m_1v1Points;
    int m_1v1EnemyPoints;
    char m_1v1OpponentName[64];
    bool m_In1v1;

	inline float GetMovementInformationBoxHeight();
	inline int GetDigitsIndex(int Value, int Max);

	// Quad Offsets
	int m_aAmmoOffset[NUM_WEAPONS];
	int m_HealthOffset;
	int m_EmptyHealthOffset;
	int m_ArmorOffset;
	int m_EmptyArmorOffset;
	int m_aCursorOffset[NUM_WEAPONS];
	int m_FlagOffset;
	int m_AirjumpOffset;
	int m_AirjumpEmptyOffset;
	int m_aWeaponOffset[NUM_WEAPONS];
	int m_EndlessJumpOffset;
	int m_EndlessHookOffset;
	int m_JetpackOffset;
	int m_TeleportGrenadeOffset;
	int m_TeleportGunOffset;
	int m_TeleportLaserOffset;
	int m_SoloOffset;
	int m_CollisionDisabledOffset;
	int m_HookHitDisabledOffset;
	int m_HammerHitDisabledOffset;
	int m_GunHitDisabledOffset;
	int m_ShotgunHitDisabledOffset;
	int m_GrenadeHitDisabledOffset;
	int m_LaserHitDisabledOffset;
	int m_DeepFrozenOffset;
	int m_LiveFrozenOffset;
	int m_DummyHammerOffset;
	int m_DummyCopyOffset;
	int m_PracticeModeOffset;
	int m_Team0ModeOffset;
	int m_LockModeOffset;

    bool m_NotificationActive;
    int64_t m_NotificationStartTime;
    float m_NotificationDuration;
    float m_NotificationFadeOutTime;
    char m_NotificationText[256]; // Adjust size if needed
    ColorRGBA m_NotificationBgColor;
    ColorRGBA m_NotificationTextColor;
    STextContainerIndex m_NotificationTextContainerIndex;

	int m_lastSoloState;

    bool m_SpectatorActionMenuActive;
    int m_SpectatorActionPage;
    float m_SpectatorActionMenuAlpha;
    int64_t m_SpectatorActionMenuShowTime;
    
    void RenderSpectatorActionMenu();
    bool IsSpectatorActionMenuShown();
    void HandleSpectatorActionInput(int Key);

    // Icon indices for the action menu
    int m_WarIconOffset;
    int m_TeamIconOffset;
    int m_HelperIconOffset;
    int m_ClanIconOffset;

    void PrepareSpectatorActionIcons();
	vec2 m_SpectatorActionMenuPos{0, 0};
};

#endif
