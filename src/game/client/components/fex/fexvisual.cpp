#include <engine/graphics.h>
#include <engine/shared/config.h>

#include <game/client/animstate.h>
#include <game/client/render.h>
#include <game/generated/client_data.h>
#include <game/generated/protocol.h>

#include <game/client/gameclient.h>

#include "fexvisual.h"

template<typename T>
T color_lerp(T a, T b, float c)
{
	T result;
	for(size_t i = 0; i < 4; ++i)
		result[i] = a[i] + c * (b[i] - a[i]);
	return result;
}

void CVisual::OnRender()
{
	if(!g_Config.m_ClVisualTees && !g_Config.m_ClVisualHook && !g_Config.m_ClVisualWeapon && !g_Config.m_ClVisualCursor)
		return;

	if(g_Config.m_ClVisualModeT == 0 && g_Config.m_ClVisualModeW == 0 && g_Config.m_ClVisualModeH == 0 && g_Config.m_ClVisualModeC == 0)
		return;

	static float Time = 0.0f;
	Time += Client()->RenderFrameTime() * ((float)g_Config.m_ClVisualSpeed / 100.0f);
	float DefTick = std::fmod(Time, 1.0f);
	ColorRGBA ColT;
    ColorRGBA ColH;
    ColorRGBA ColC;
    ColorRGBA ColW;

    // ****************
    // Visual Col Modes: 1 = Weapon, 2 = Hook, 3 = Tees, 4 = Cursor
    // ****************

    // ****************
    // Mode: Tees
    // ****************

    switch(g_Config.m_ClVisualModeT)
	{
	case m_Tees.COLORMODE_RAINBOW:
        ColT = color_cast<ColorRGBA>(ColorHSLA(DefTick, 1.0f, 0.5f));
		break;
	case m_Tees.COLORMODE_PULSE:
        ColT = color_cast<ColorRGBA>(ColorHSLA(std::fmod(std::floor(Time) * 0.1f, 1.0f), 1.0f, 0.5f + std::fabs(DefTick - 0.5f)));
		break;
	case m_Tees.COLORMODE_CUSTOM:
        ColT = color_cast<ColorRGBA>(ColorHSLA(g_Config.m_ClVisualCusColor3));
		break;
	case m_Tees.COLORMODE_RANDOM:
		static ColorHSLA ColT1 = ColorHSLA(0.0f, 0.0f, 0.0f, 0.0f), ColT2 = ColorHSLA(0.0f, 0.0f, 0.0f, 0.0f);
		if(ColT2.a == 0.0f) // Create first target
            ColT2 = ColorHSLA((float)rand() / (float)RAND_MAX, 1.0f, (float)rand() / (float)RAND_MAX, 1.0f);
		static float LastSwap = -INFINITY;
		if(Time - LastSwap > 1.0f) // Shift target to source, create new target
		{
			LastSwap = Time;
			ColT1 = ColT2;
			ColT2 = ColorHSLA((float)rand() / (float)RAND_MAX, 1.0f, (float)rand() / (float)RAND_MAX, 1.0f);
		}
		ColT = color_cast<ColorRGBA>(color_lerp(ColT1, ColT2, DefTick));
		break;
	}

    // ****************
    // Mode: Hook
    // ****************

    switch(g_Config.m_ClVisualModeH)
	{
	case m_Hook.COLORMODE_RAINBOW:
        ColH = color_cast<ColorRGBA>(ColorHSLA(DefTick, 1.0f, 0.5f));
		break;
	case m_Hook.COLORMODE_PULSE:
        ColH = color_cast<ColorRGBA>(ColorHSLA(std::fmod(std::floor(Time) * 0.1f, 1.0f), 1.0f, 0.5f + std::fabs(DefTick - 0.5f)));
		break;
	case m_Hook.COLORMODE_CUSTOM:
        ColH = color_cast<ColorRGBA>(ColorHSLA(g_Config.m_ClVisualCusColor2));
		break;
	case m_Hook.COLORMODE_RANDOM:
		static ColorHSLA ColH1 = ColorHSLA(0.0f, 0.0f, 0.0f, 0.0f), ColH2 = ColorHSLA(0.0f, 0.0f, 0.0f, 0.0f);
		if(ColH2.a == 0.0f) // Create first target
            ColH2 = ColorHSLA((float)rand() / (float)RAND_MAX, 1.0f, (float)rand() / (float)RAND_MAX, 1.0f);
		static float LastSwap = -INFINITY;
		if(Time - LastSwap > 1.0f) // Shift target to source, create new target
		{
			LastSwap = Time;
			ColH1 = ColH2;
			ColH2 = ColorHSLA((float)rand() / (float)RAND_MAX, 1.0f, (float)rand() / (float)RAND_MAX, 1.0f);
		}
		ColH = color_cast<ColorRGBA>(color_lerp(ColH1, ColH2, DefTick));
		break;
	}

    // ****************
    // Mode: Weapon
    // ****************

    switch(g_Config.m_ClVisualModeW)
	{
	case m_Weapon.COLORMODE_RAINBOW:
        ColW = color_cast<ColorRGBA>(ColorHSLA(DefTick, 1.0f, 0.5f));
		break;
	case m_Weapon.COLORMODE_PULSE:
        ColW = color_cast<ColorRGBA>(ColorHSLA(std::fmod(std::floor(Time) * 0.1f, 1.0f), 1.0f, 0.5f + std::fabs(DefTick - 0.5f)));
		break;
	case m_Weapon.COLORMODE_CUSTOM:
        ColW = color_cast<ColorRGBA>(ColorHSLA(g_Config.m_ClVisualCusColor1));
		break;
	case m_Weapon.COLORMODE_RANDOM:
		static ColorHSLA ColW1 = ColorHSLA(0.0f, 0.0f, 0.0f, 0.0f), ColW2 = ColorHSLA(0.0f, 0.0f, 0.0f, 0.0f);
		if(ColW2.a == 0.0f) // Create first target
        ColW2 = ColorHSLA((float)rand() / (float)RAND_MAX, 1.0f, (float)rand() / (float)RAND_MAX, 1.0f);
		static float LastSwap = -INFINITY;
		if(Time - LastSwap > 1.0f) // Shift target to source, create new target
		{
			LastSwap = Time;
			ColW1 = ColW2;
			ColW2 = ColorHSLA((float)rand() / (float)RAND_MAX, 1.0f, (float)rand() / (float)RAND_MAX, 1.0f);
		}
		ColW = color_cast<ColorRGBA>(color_lerp(ColW1, ColW2, DefTick));
		break;
	}

    // ****************
    // Mode: Cursor
    // ****************

    switch(g_Config.m_ClVisualModeC)
	{
	case m_Cursor.COLORMODE_RAINBOW:
        ColC = color_cast<ColorRGBA>(ColorHSLA(DefTick, 1.0f, 0.5f));
		break;
	case m_Cursor.COLORMODE_PULSE:
        ColC = color_cast<ColorRGBA>(ColorHSLA(std::fmod(std::floor(Time) * 0.1f, 1.0f), 1.0f, 0.5f + std::fabs(DefTick - 0.5f)));
		break;
	case m_Cursor.COLORMODE_CUSTOM:
        ColC = color_cast<ColorRGBA>(ColorHSLA(g_Config.m_ClVisualCusColor4));
		break;
	case m_Cursor.COLORMODE_RANDOM:
		static ColorHSLA ColC1 = ColorHSLA(0.0f, 0.0f, 0.0f, 0.0f), ColC2 = ColorHSLA(0.0f, 0.0f, 0.0f, 0.0f);
		if(ColC2.a == 0.0f) // Create first target
        ColC2 = ColorHSLA((float)rand() / (float)RAND_MAX, 1.0f, (float)rand() / (float)RAND_MAX, 1.0f);
		static float LastSwap = -INFINITY;
		if(Time - LastSwap > 1.0f) // Shift target to source, create new target
		{
			LastSwap = Time;
			ColC1 = ColC2;
			ColC2 = ColorHSLA((float)rand() / (float)RAND_MAX, 1.0f, (float)rand() / (float)RAND_MAX, 1.0f);
		}
		ColC = color_cast<ColorRGBA>(color_lerp(ColC1, ColC2, DefTick));
		break;
	}

	m_Cursor.m_VisualColor = ColC;
	m_Hook.m_VisualColor = ColH;
	m_Weapon.m_VisualColor = ColW;
	m_Tees.m_VisualColor = ColT;
    
    for(int i = 0; i < MAX_CLIENTS; i++)
	{
		if(!m_pClient->m_Snap.m_aCharacters[i].m_Active)
			continue;
		// check if local player
		bool Local = m_pClient->m_Snap.m_LocalClientId == i;
		CTeeRenderInfo *RenderInfo = &m_pClient->m_aClients[i].m_RenderInfo;

		// check if rainbow is enabled
		if(Local ? g_Config.m_ClVisualTees : (g_Config.m_ClVisualTees && g_Config.m_ClVisualTeesOthers))
		{
			RenderInfo->m_BloodColor = ColT;
			RenderInfo->m_ColorBody = ColT;
			RenderInfo->m_ColorFeet = ColT;
			RenderInfo->m_CustomColoredSkin = true;
		}
	}

}
