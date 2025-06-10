#include "fexpets.h"

#include <game/client/animstate.h>
#include <game/client/gameclient.h>

#include <engine/shared/config.h>

void CPet::UpdateCustomPetTexture()
{
    static char s_aLastPetSkin[IO_MAX_PATH_LENGTH] = "";

    const char *pDesiredSkin = g_Config.m_ClCustomPetSkin[0] ? g_Config.m_ClCustomPetSkin : "default";

    if(str_comp(s_aLastPetSkin, pDesiredSkin) == 0 && m_PetTexture.IsValid())
    {
        return;
    }

    str_copy(s_aLastPetSkin, pDesiredSkin, sizeof(s_aLastPetSkin));

    if(m_PetTexture.IsValid())
    {
        Graphics()->UnloadTexture(&m_PetTexture);
    }

    char aPath[IO_MAX_PATH_LENGTH];
    str_format(aPath, sizeof(aPath), "fex/pets/%s.png", pDesiredSkin);

    m_PetTexture = Graphics()->LoadTexture(aPath, IStorage::TYPE_ALL);
}


void CPet::OnRender()
{
	if(Client()->State() != IClient::STATE_ONLINE && Client()->State() != IClient::STATE_DEMOPLAYBACK)
		return;
	if(g_Config.m_ClShowPet <= 0)
		return;

	const int PlayerId = GameClient()->m_aLocalIds[g_Config.m_ClDummy];
	if(PlayerId < 0)
		return;
	const auto &Player = GameClient()->m_aClients[PlayerId];

	const float Delta = Client()->RenderFrameTime();

	const float Scale = (float)g_Config.m_ClSizePet / 100.0f;

    if(g_Config.m_ClPetDebugLine)
    {
        vec2 DrawInitPos = Player.m_RenderPos;
        vec2 DrawFinishPos = m_Position;

        ColorRGBA DebugLineColor = color_cast<ColorRGBA>(ColorHSLA(g_Config.m_ClPetDebugLineColor));

        int Thickness = g_Config.m_ClPetDebugLineThickness;
        float Alpha = g_Config.m_ClPetDebugLineAlpha / 100.0f;

        if(Thickness == 1)
        {
            Graphics()->LinesBegin();
            Graphics()->SetColor(ColorRGBA(DebugLineColor.r, DebugLineColor.g, DebugLineColor.b, Alpha));
            IGraphics::CLineItem LineItem(DrawInitPos.x, DrawInitPos.y, DrawFinishPos.x, DrawFinishPos.y);
            Graphics()->LinesDraw(&LineItem, 1);
            Graphics()->LinesEnd();
        }
        else
        {
            vec2 Diff = DrawFinishPos - DrawInitPos;
            vec2 Perp = normalize(vec2(Diff.y, -Diff.x));

            float Zoom = GameClient()->m_Camera.m_Zoom;
            float HalfThickness = (float)Thickness * 0.5f * Zoom;

            vec2 Pos0 = DrawFinishPos - Perp * HalfThickness;
            vec2 Pos1 = DrawFinishPos + Perp * HalfThickness;
            vec2 Pos2 = DrawInitPos - Perp * HalfThickness;
            vec2 Pos3 = DrawInitPos + Perp * HalfThickness;

            Graphics()->QuadsBegin();
            Graphics()->SetColor(ColorRGBA(DebugLineColor.r, DebugLineColor.g, DebugLineColor.b, Alpha));
            IGraphics::CFreeformItem FreeformItem(Pos0.x, Pos0.y, Pos1.x, Pos1.y, Pos2.x, Pos2.y, Pos3.x, Pos3.y);
            Graphics()->QuadsDrawFreeform(&FreeformItem, 1);
            Graphics()->QuadsEnd();
        }
    }

    if(Player.m_Active && Player.m_Team != TEAM_SPECTATORS)
    {
        const float offsetX = 64.0f + Scale * 32.0f;
        const float offsetY = 100.0f + Scale * 32.0f;
        switch(g_Config.m_ClPetPosition)
        {
            case 0:
                m_Target.x = Player.m_RenderPos.x - offsetX;
                m_Target.y = Player.m_RenderPos.y - offsetY;
                break;
            case 1:
                m_Target.x = Player.m_RenderPos.x + offsetX;
                m_Target.y = Player.m_RenderPos.y - offsetY;
                break;
            case 2:
                m_Target.x = Player.m_RenderPos.x + offsetX;
                m_Target.y = Player.m_RenderPos.y + offsetY;
                break;
            case 3:
                m_Target.x = Player.m_RenderPos.x - offsetX;
                m_Target.y = Player.m_RenderPos.y + offsetY;
                break;
            default:
                m_Target.x = Player.m_RenderPos.x + offsetX;
                m_Target.y = Player.m_RenderPos.y - offsetY;
                break;
        }
        
        m_Target.y += std::sin((float)Client()->GameTick(g_Config.m_ClDummy) / (float)Client()->GameTickSpeed() / 2.0f) * 8.0f;
        
        if(m_Alpha == 0.0f)
        {
            m_Position = m_Target;
            m_Velocity = vec2(0.0f, 0.0f);
            m_Dir = random_direction();
        }
        if(m_Alpha < 1.0f)
        {
            m_Alpha += Delta;
            if(m_Alpha >= 1.0f)
                m_Alpha = 1.0f;
        }
        {
            vec2 DP = m_Target - m_Position;
            float DL = length(DP);
            if(DL > 512.0f)
                m_Alpha = 0.01f;
        }
        
        m_Position += m_Velocity * Delta;
        
        vec2 deltaPos = m_Target - m_Position;
        float deltaLen = length(deltaPos);
        if(deltaLen > 512.0f)
            m_Alpha = 0.01f;
        
        static const float k = 50.0f;
        vec2 deltaDamped = (m_Velocity * -2.0f * std::sqrt(k) + deltaPos * k) * Delta;
        static const float friction = 0.01f;
        vec2 deltaWizzy = (m_Velocity + deltaPos * Delta * 50.0f) * std::pow(friction, Delta) - m_Velocity;
        
        float speedMultiplier = (float)g_Config.m_ClPetFollowSpeed / 100.0f;

        if(g_Config.m_ClPetFollowMode == 0)
        {
            m_Velocity += mix(deltaDamped, deltaWizzy, clamp(deltaLen / 64.0f, 0.0f, 1.0f)) * speedMultiplier;
            m_Position += m_Velocity * Delta;
        }
        else if(g_Config.m_ClPetFollowMode == 1)
        {
            m_Velocity += deltaWizzy * speedMultiplier;
            m_Position += m_Velocity * Delta;
        }
        else if(g_Config.m_ClPetFollowMode == 2)
        {
            m_Velocity += deltaDamped * speedMultiplier;
            m_Position += m_Velocity * Delta;
        }
        else if(g_Config.m_ClPetFollowMode == 3)
        {
            float factor = clamp(Delta * speedMultiplier, 0.0f, 1.0f);
            m_Position = m_Position + (m_Target - m_Position) * factor;
            m_Velocity = (m_Target - m_Position) / Delta;
        }
    }
    else
    {
        if(m_Alpha > 0.0f)
        {
            m_Alpha -= Delta;
            if(m_Alpha < 0.0f)
                m_Alpha = 0.0f;
        }
    }

    if(m_Alpha <= 0.0f)
        return;

    const auto &Character = Player.m_RenderCur;
    vec2 DirTarget;
    int Emote = 0;
    if(GameClient()->m_Snap.m_SpecInfo.m_Active)
    {
        DirTarget = GameClient()->m_Camera.m_Center - m_Target;
        if(length(DirTarget) > 1.0f)
            DirTarget = normalize(DirTarget);
    }
    else
    {
        Emote = Character.m_Emote;
        vec2 DirMouse = GameClient()->m_Controls.m_aMousePos[g_Config.m_ClDummy];
        if(length(DirMouse) > 1.0f)
            DirMouse = normalize(DirMouse);
        vec2 DirVel = m_Velocity;
        if(length(DirVel) > 1.0f)
            DirVel = normalize(DirVel);
        DirTarget = mix(DirMouse, DirVel, clamp(length(m_Velocity) / 32.0f, 0.0f, 1.0f));
    }
    m_Dir = (DirTarget + m_Dir) / 2.0f; // TODO: stop being lazy

    if(g_Config.m_ClUseCustomPetSkin)
    {
        UpdateCustomPetTexture();
        Graphics()->TextureSet(m_PetTexture);
        Graphics()->QuadsBegin();
        
        float Size = 72.0f * Scale;
        float x = m_Position.x - (Size / 2);
        float y = m_Position.y - (Size / 2);

        Graphics()->SetColor(1.0f, 1.0f, 1.0f, m_Alpha * (float)g_Config.m_ClAlphaPet / 100.0f);
        IGraphics::CQuadItem QuadItem(x, y, Size, Size);
        Graphics()->QuadsDrawTL(&QuadItem, 1);
        
        Graphics()->QuadsEnd();
    }
    else
    {
        CTeeRenderInfo TeeRenderInfo;
        TeeRenderInfo.Apply(m_pClient->m_Skins.Find(g_Config.m_ClSkinPet));
        TeeRenderInfo.m_Size = 64.0f * Scale;
        TeeRenderInfo.m_GotAirJump = m_Velocity.y > -10.0f;
        RenderTools()->RenderTee(CAnimState::GetIdle(), &TeeRenderInfo, Emote, m_Dir, m_Position, m_Alpha * (float)g_Config.m_ClAlphaPet / 100.0f);
    }
}

void CPet::OnMapLoad()
{
	m_Alpha = 0.0f;
}
