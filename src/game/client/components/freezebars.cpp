#include <game/client/gameclient.h>

#include "freezebars.h"

void CFreezeBars::RenderKillBar()
{
	if(g_Config.m_ClFreezeKillColor)
	{
		if(g_Config.m_ClVisualFreezeKillBars)
		{
					
			if(!g_Config.m_ClFreezeKill || !GameClient()->CurrentRaceTime())
				return;
	
			if(g_Config.m_ClFreezeKillMultOnly)
			{
				if(str_comp(Client()->GetCurrentMap(), "Multeasymap") != 0)
					return;
			}
	
			int ClientId = m_pClient->m_Snap.m_LocalClientId;
	
			const float FreezeBarWidth = 64.0f;
			const float FreezeBarHalfWidth = 32.0f;
			const float FreezeBarHight = 16.0f;
	
			// pCharacter contains the predicted character for local players or the last snap for players who are spectated
			CCharacterCore *pCharacter = &m_pClient->m_aClients[ClientId].m_Predicted;
	
			if(pCharacter->m_FreezeEnd <= 0 || pCharacter->m_FreezeStart == 0 || pCharacter->m_FreezeEnd <= pCharacter->m_FreezeStart || !m_pClient->m_Snap.m_aCharacters[ClientId].m_HasExtendedDisplayInfo)
			{
				return;
			}
	
			float Time = (static_cast<float>(GameClient()->m_FreezeKill.m_LastFreeze) - time_get());
			float Max = g_Config.m_ClFreezeKillMs / 1000.0f;
			float FreezeProgress = clamp(Time / 1000000000.0f, 0.0f, Max) / Max;
			if(FreezeProgress <= 0.0f)
			{
				return;
			}
	
	
			vec2 Position = m_pClient->m_aClients[ClientId].m_RenderPos;
			Position.x -= FreezeBarHalfWidth;
			Position.y += 22;
	
			ColorHSVA ColorHSV(round_to_int(LocalTime() * g_Config.m_ClVisualSpeed) % 255 / 255.f, 1.f, 1.f);
			ColorRGBA ColorWithAlpha = color_cast<ColorRGBA>(ColorHSV);
			ColorWithAlpha.a = 1.f;
	
			float R = ColorWithAlpha.r;
			float G = ColorWithAlpha.g;
			float B = ColorWithAlpha.b;
	
			RenderFreezeBarPos(Position.x, Position.y, FreezeBarWidth, FreezeBarHight, FreezeProgress, R, G, B, 100.0f);
		}
		else
		{				
			if(!g_Config.m_ClFreezeKill || !GameClient()->CurrentRaceTime())
				return;
	
			if(g_Config.m_ClFreezeKillMultOnly)
			{
				if(str_comp(Client()->GetCurrentMap(), "Multeasymap") != 0)
					return;
			}
	
			int ClientId = m_pClient->m_Snap.m_LocalClientId;
	
			const float FreezeBarWidth = 64.0f;
			const float FreezeBarHalfWidth = 32.0f;
			const float FreezeBarHight = 16.0f;
	
			// pCharacter contains the predicted character for local players or the last snap for players who are spectated
			CCharacterCore *pCharacter = &m_pClient->m_aClients[ClientId].m_Predicted;
	
			if(pCharacter->m_FreezeEnd <= 0 || pCharacter->m_FreezeStart == 0 || pCharacter->m_FreezeEnd <= pCharacter->m_FreezeStart || !m_pClient->m_Snap.m_aCharacters[ClientId].m_HasExtendedDisplayInfo)
			{
				return;
			}
	
			float Time = (static_cast<float>(GameClient()->m_FreezeKill.m_LastFreeze) - time_get());
			float Max = g_Config.m_ClFreezeKillMs / 1000.0f;
			float FreezeProgress = clamp(Time / 1000000000.0f, 0.0f, Max) / Max;
			if(FreezeProgress <= 0.0f)
			{
				return;
			}
	
	
			vec2 Position = m_pClient->m_aClients[ClientId].m_RenderPos;
			Position.x -= FreezeBarHalfWidth;
			Position.y += 22;

			ColorHSVA ColorHSV(g_Config.m_ClFreezeKillColorCol);
			ColorRGBA ColorWithAlpha = color_cast<ColorRGBA>(ColorHSLA(ColorHSV));
			float R = ColorWithAlpha.r;
			float G = ColorWithAlpha.g;
			float B = ColorWithAlpha.b;
			
			RenderFreezeBarPos(Position.x, Position.y, FreezeBarWidth, FreezeBarHight, FreezeProgress, R, G, B, 100.0f);
		}
	}
	else
	{
		if(!g_Config.m_ClFreezeKill || !GameClient()->CurrentRaceTime())
		return;

		if(g_Config.m_ClFreezeKillMultOnly)
		{
			if(str_comp(Client()->GetCurrentMap(), "Multeasymap") != 0)
				return;
		}

		int ClientId = m_pClient->m_Snap.m_LocalClientId;

		const float FreezeBarWidth = 64.0f;
		const float FreezeBarHalfWidth = 32.0f;
		const float FreezeBarHight = 16.0f;

		// pCharacter contains the predicted character for local players or the last snap for players who are spectated
		CCharacterCore *pCharacter = &m_pClient->m_aClients[ClientId].m_Predicted;

		if(pCharacter->m_FreezeEnd <= 0 || pCharacter->m_FreezeStart == 0 || pCharacter->m_FreezeEnd <= pCharacter->m_FreezeStart || !m_pClient->m_Snap.m_aCharacters[ClientId].m_HasExtendedDisplayInfo)
		{
			return;
		}

		float Time = (static_cast<float>(GameClient()->m_FreezeKill.m_LastFreeze) - time_get());
		float Max = g_Config.m_ClFreezeKillMs / 1000.0f;
		float FreezeProgress = clamp(Time / 1000000000.0f, 0.0f, Max) / Max;
		if(FreezeProgress <= 0.0f)
		{
			return;
		}


		vec2 Position = m_pClient->m_aClients[ClientId].m_RenderPos;
		Position.x -= FreezeBarHalfWidth;
		Position.y += 22;

		float R = 1.f;
		float G = 0.f;
		float B = 1.f;

		RenderFreezeBarPos(Position.x, Position.y, FreezeBarWidth, FreezeBarHight, FreezeProgress, R, G, B, 100.0f);
	}

}

void CFreezeBars::RenderFreezeBar(const int ClientId)
{
	float R = 1.0f;
	float G = 1.0f;
	float B = 1.0f;


	const float FreezeBarWidth = 64.0f;
	const float FreezeBarHalfWidth = 32.0f;
	const float FreezeBarHight = 16.0f;

	// pCharacter contains the predicted character for local players or the last snap for players who are spectated
	CCharacterCore *pCharacter = &m_pClient->m_aClients[ClientId].m_Predicted;

	if(pCharacter->m_FreezeEnd <= 0 || pCharacter->m_FreezeStart == 0 || pCharacter->m_FreezeEnd <= pCharacter->m_FreezeStart || !m_pClient->m_Snap.m_aCharacters[ClientId].m_HasExtendedDisplayInfo || (pCharacter->m_IsInFreeze && g_Config.m_ClFreezeBarsAlphaInsideFreeze == 0))
	{
		return;
	}

	const int Max = pCharacter->m_FreezeEnd - pCharacter->m_FreezeStart;
	float FreezeProgress = clamp(Max - (Client()->GameTick(g_Config.m_ClDummy) - pCharacter->m_FreezeStart), 0, Max) / (float)Max;
	if(FreezeProgress <= 0.0f)
	{
		return;
	}

	vec2 Position = m_pClient->m_aClients[ClientId].m_RenderPos;
	Position.x -= FreezeBarHalfWidth;
	Position.y += 22;

	float Alpha = m_pClient->IsOtherTeam(ClientId) ? g_Config.m_ClShowOthersAlpha / 100.0f : 1.0f;
	if(pCharacter->m_IsInFreeze)
	{
		Alpha *= g_Config.m_ClFreezeBarsAlphaInsideFreeze / 100.0f;
	}

	RenderFreezeBarPos(Position.x, Position.y, FreezeBarWidth, FreezeBarHight, FreezeProgress, R, G, B, Alpha);
}

void CFreezeBars::RenderFreezeBarPos(float x, const float y, const float width, const float height, float Progress, const float R, const float G, const float B, const float Alpha)
{
	Progress = clamp(Progress, 0.0f, 1.0f);

	// what percentage of the end pieces is used for the progress indicator and how much is the rest
	// half of the ends are used for the progress display
	const float RestPct = 0.5f;
	const float ProgPct = 0.5f;

	const float EndWidth = height; // to keep the correct scale - the height of the sprite is as long as the width
	const float BarHeight = height;
	const float WholeBarWidth = width;
	const float MiddleBarWidth = WholeBarWidth - (EndWidth * 2.0f);
	const float EndProgressWidth = EndWidth * ProgPct;
	const float EndRestWidth = EndWidth * RestPct;
	const float ProgressBarWidth = WholeBarWidth - (EndProgressWidth * 2.0f);
	const float EndProgressProportion = EndProgressWidth / ProgressBarWidth;
	const float MiddleProgressProportion = MiddleBarWidth / ProgressBarWidth;

	// beginning piece
	float BeginningPieceProgress = 1;
	if(Progress <= EndProgressProportion)
	{
		BeginningPieceProgress = Progress / EndProgressProportion;
	}

	// full
	Graphics()->WrapClamp();
	Graphics()->TextureSet(m_pClient->m_HudSkin.m_SpriteHudFreezeBarFullLeft);
	Graphics()->QuadsBegin();
	Graphics()->SetColor(R, G, B, Alpha);
	// Subset: top_l, top_m, btm_m, btm_l
	Graphics()->QuadsSetSubsetFree(0, 0, RestPct + ProgPct * BeginningPieceProgress, 0, RestPct + ProgPct * BeginningPieceProgress, 1, 0, 1);
	IGraphics::CQuadItem QuadFullBeginning(x, y, EndRestWidth + EndProgressWidth * BeginningPieceProgress, BarHeight);
	Graphics()->QuadsDrawTL(&QuadFullBeginning, 1);
	Graphics()->QuadsEnd();

	// empty
	if(BeginningPieceProgress < 1.0f)
	{
		Graphics()->TextureSet(m_pClient->m_HudSkin.m_SpriteHudFreezeBarEmptyRight);
		Graphics()->QuadsBegin();
		Graphics()->SetColor(R, G, B, Alpha);
		// Subset: top_m, top_l, btm_l, btm_m | it is mirrored on the horizontal axe and rotated 180 degrees
		Graphics()->QuadsSetSubsetFree(ProgPct - ProgPct * BeginningPieceProgress, 0, 0, 0, 0, 1, ProgPct - ProgPct * BeginningPieceProgress, 1);
		IGraphics::CQuadItem QuadEmptyBeginning(x + EndRestWidth + EndProgressWidth * BeginningPieceProgress, y, EndProgressWidth * (1.0f - BeginningPieceProgress), BarHeight);
		Graphics()->QuadsDrawTL(&QuadEmptyBeginning, 1);
		Graphics()->QuadsEnd();
	}

	// middle piece
	x += EndWidth;

	float MiddlePieceProgress = 1;
	if(Progress <= EndProgressProportion + MiddleProgressProportion)
	{
		if(Progress <= EndProgressProportion)
		{
			MiddlePieceProgress = 0;
		}
		else
		{
			MiddlePieceProgress = (Progress - EndProgressProportion) / MiddleProgressProportion;
		}
	}

	const float FullMiddleBarWidth = MiddleBarWidth * MiddlePieceProgress;
	const float EmptyMiddleBarWidth = MiddleBarWidth - FullMiddleBarWidth;

	// full freeze bar
	Graphics()->TextureSet(m_pClient->m_HudSkin.m_SpriteHudFreezeBarFull);
	Graphics()->QuadsBegin();
	Graphics()->SetColor(R, G, B, Alpha);
	// select the middle portion of the sprite so we don't get edge bleeding
	if(FullMiddleBarWidth <= EndWidth)
	{
		// prevent pixel puree, select only a small slice
		// Subset: top_l, top_m, btm_m, btm_l
		Graphics()->QuadsSetSubsetFree(0, 0, FullMiddleBarWidth / EndWidth, 0, FullMiddleBarWidth / EndWidth, 1, 0, 1);
	}
	else
	{
		// Subset: top_l, top_r, btm_r, btm_l
		Graphics()->QuadsSetSubsetFree(0, 0, 1, 0, 1, 1, 0, 1);
	}
	IGraphics::CQuadItem QuadFull(x, y, FullMiddleBarWidth, BarHeight);
	Graphics()->QuadsDrawTL(&QuadFull, 1);
	Graphics()->QuadsEnd();

	// empty freeze bar
	Graphics()->TextureSet(m_pClient->m_HudSkin.m_SpriteHudFreezeBarEmpty);
	Graphics()->QuadsBegin();
	Graphics()->SetColor(R, G, B, Alpha);
	// select the middle portion of the sprite so we don't get edge bleeding
	if(EmptyMiddleBarWidth <= EndWidth)
	{
		// prevent pixel puree, select only a small slice
		// Subset: top_m, top_l, btm_l, btm_m | it is mirrored on the horizontal axe and rotated 180 degrees
		Graphics()->QuadsSetSubsetFree(EmptyMiddleBarWidth / EndWidth, 0, 0, 0, 0, 1, EmptyMiddleBarWidth / EndWidth, 1);
	}
	else
	{
		// Subset: top_r, top_l, btm_l, btm_r | it is mirrored on the horizontal axe and rotated 180 degrees
		Graphics()->QuadsSetSubsetFree(1, 0, 0, 0, 0, 1, 1, 1);
	}

	IGraphics::CQuadItem QuadEmpty(x + FullMiddleBarWidth, y, EmptyMiddleBarWidth, BarHeight);
	Graphics()->QuadsDrawTL(&QuadEmpty, 1);
	Graphics()->QuadsEnd();

	// end piece
	x += MiddleBarWidth;
	float EndingPieceProgress = 1;
	if(Progress <= 1)
	{
		if(Progress <= (EndProgressProportion + MiddleProgressProportion))
		{
			EndingPieceProgress = 0;
		}
		else
		{
			EndingPieceProgress = (Progress - EndProgressProportion - MiddleProgressProportion) / EndProgressProportion;
		}
	}
	if(EndingPieceProgress > 0.0f)
	{
		// full
		Graphics()->TextureSet(m_pClient->m_HudSkin.m_SpriteHudFreezeBarFullLeft);
		Graphics()->QuadsBegin();
		Graphics()->SetColor(R, G, B, Alpha);
		// Subset: top_r, top_m, btm_m, btm_r | it is mirrored on the horizontal axe and rotated 180 degrees
		Graphics()->QuadsSetSubsetFree(1, 0, 1.0f - ProgPct * EndingPieceProgress, 0, 1.0f - ProgPct * EndingPieceProgress, 1, 1, 1);
		IGraphics::CQuadItem QuadFullEnding(x, y, EndProgressWidth * EndingPieceProgress, BarHeight);
		Graphics()->QuadsDrawTL(&QuadFullEnding, 1);
		Graphics()->QuadsEnd();
	}
	// empty
	Graphics()->TextureSet(m_pClient->m_HudSkin.m_SpriteHudFreezeBarEmptyRight);
	Graphics()->QuadsBegin();
	Graphics()->SetColor(R, G, B, Alpha);
	// Subset: top_m, top_r, btm_r, btm_m
	Graphics()->QuadsSetSubsetFree(ProgPct - ProgPct * (1.0f - EndingPieceProgress), 0, 1, 0, 1, 1, ProgPct - ProgPct * (1.0f - EndingPieceProgress), 1);
	IGraphics::CQuadItem QuadEmptyEnding(x + EndProgressWidth * EndingPieceProgress, y, EndProgressWidth * (1.0f - EndingPieceProgress) + EndRestWidth, BarHeight);
	Graphics()->QuadsDrawTL(&QuadEmptyEnding, 1);
	Graphics()->QuadsEnd();

	Graphics()->QuadsSetSubset(0, 0, 1, 1);
	Graphics()->SetColor(R, G, B, Alpha);
	Graphics()->WrapNormal();
}

inline bool CFreezeBars::IsPlayerInfoAvailable(int ClientId) const
{
	const void *pPrevInfo = Client()->SnapFindItem(IClient::SNAP_PREV, NETOBJTYPE_PLAYERINFO, ClientId);
	const void *pInfo = Client()->SnapFindItem(IClient::SNAP_CURRENT, NETOBJTYPE_PLAYERINFO, ClientId);
	return pPrevInfo && pInfo;
}

void CFreezeBars::OnRender()
{
	float Time = (static_cast<float>(GameClient()->m_FreezeKill.m_LastFreeze) - time_get());
	float Max = g_Config.m_ClFreezeKillMs / 1000.0f;
	float FreezeProgress = clamp(Time / 1000000000.0f, 0.0f, Max) / Max;

	int LocalClientId = m_pClient->m_Snap.m_LocalClientId;

	if(FreezeProgress < 0.95f)
		RenderKillBar();

	if(Client()->State() != IClient::STATE_ONLINE && Client()->State() != IClient::STATE_DEMOPLAYBACK)
		return;

	if(!g_Config.m_ClShowFreezeBars)
	{
		return;
	}
	// get screen edges to avoid rendering offscreen
	float ScreenX0, ScreenY0, ScreenX1, ScreenY1;
	Graphics()->GetScreen(&ScreenX0, &ScreenY0, &ScreenX1, &ScreenY1);
	// expand the edges to prevent popping in/out onscreen
	//
	// it is assumed that the tee with the freeze bar fit into a 240x240 box centered on the tee
	// this may need to be changed or calculated differently in the future
	float BorderBuffer = 120;
	ScreenX0 -= BorderBuffer;
	ScreenX1 += BorderBuffer;
	ScreenY0 -= BorderBuffer;
	ScreenY1 += BorderBuffer;

	// render everyone else's freeze bar, then our own
	for(int ClientId = 0; ClientId < MAX_CLIENTS; ClientId++)
	{
		if(ClientId == LocalClientId || !m_pClient->m_Snap.m_aCharacters[ClientId].m_Active || !IsPlayerInfoAvailable(ClientId))
		{
			continue;
		}

		//don't render if the tee is offscreen
		vec2 *pRenderPos = &m_pClient->m_aClients[ClientId].m_RenderPos;
		if(pRenderPos->x < ScreenX0 || pRenderPos->x > ScreenX1 || pRenderPos->y < ScreenY0 || pRenderPos->y > ScreenY1)
		{
			continue;
		}
		RenderFreezeBar(ClientId);
	}
	if(LocalClientId != -1 && m_pClient->m_Snap.m_aCharacters[LocalClientId].m_Active && IsPlayerInfoAvailable(LocalClientId))
	{
		if(FreezeProgress > 0.95f || !g_Config.m_ClFreezeKill)
			RenderFreezeBar(LocalClientId);
		else if(g_Config.m_ClFreezeKillMultOnly && str_comp(Client()->GetCurrentMap(), "Multeasymap") != 0)
			RenderFreezeBar(LocalClientId);
		if(GameClient()->m_FreezeKill.m_SentFreezeKill == true)
			RenderFreezeBar(LocalClientId);
	}
}
