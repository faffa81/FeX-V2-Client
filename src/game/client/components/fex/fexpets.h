#ifndef GAME_CLIENT_COMPONENTS_FEX_FEXPETS_H
#define GAME_CLIENT_COMPONENTS_FEX_FEXPETS_H

#include <game/client/component.h>
#include <base/vmath.h>

#include <engine/client.h>

class CPet : public CComponent
{
private:
	vec2 m_Target;
	vec2 m_Position;
	vec2 m_Velocity;
	vec2 m_Dir;
	float m_Alpha = 0.0f;
    IGraphics::CTextureHandle m_PetTexture;

public:
	int Sizeof() const override { return sizeof(*this); }
	void UpdateCustomPetTexture();
	void OnRender() override;
	void OnMapLoad() override;
};

#endif
