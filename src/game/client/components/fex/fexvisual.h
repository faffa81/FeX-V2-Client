#ifndef GAME_CLIENT_COMPONENTS_FEX_FEXVISUAL_H
#define GAME_CLIENT_COMPONENTS_FEX_FEXVISUAL_H
#include <game/client/component.h>

class CVisual : public CComponent
{
public:
	virtual int Sizeof() const override { return sizeof(*this); }
    virtual void OnRender() override;

    class CWeaponCols
    {
    public:
        enum COLORMODES
        {
            COLORMODE_RAINBOW = 1,
            COLORMODE_PULSE,
            COLORMODE_CUSTOM,
            COLORMODE_RANDOM
        };
    
        ColorRGBA m_VisualColor = ColorRGBA(1, 1, 1, 1);
    };

    class CHookCols
    {
    public:
        enum COLORMODES
        {
            COLORMODE_RAINBOW = 1,
            COLORMODE_PULSE,
            COLORMODE_CUSTOM,
            COLORMODE_RANDOM
        };
    
        ColorRGBA m_VisualColor = ColorRGBA(1, 1, 1, 1);
    };

    class CTeesCols
    {
    public:
        enum COLORMODES
        {
            COLORMODE_RAINBOW = 1,
            COLORMODE_PULSE,
            COLORMODE_CUSTOM,
            COLORMODE_RANDOM
        };
    
        ColorRGBA m_VisualColor = ColorRGBA(1, 1, 1, 1);
    };

    class CCursorCols
    {
    public:
        enum COLORMODES
        {
            COLORMODE_RAINBOW = 1,
            COLORMODE_PULSE,
            COLORMODE_CUSTOM,
            COLORMODE_RANDOM
        };
    
        ColorRGBA m_VisualColor = ColorRGBA(1, 1, 1, 1);
    };

    CWeaponCols m_Weapon;
    CHookCols m_Hook;
    CTeesCols m_Tees;
    CCursorCols m_Cursor;

};

#endif
