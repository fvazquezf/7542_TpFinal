#ifndef BUYINGMENU_H
#define BUYINGMENU_H

#include <vector>
#include "Button.h"

// paths a las texturas del menu (_m)
#define AK_PATH "../sprites/gfx/weapons/ak47_m.bmp"
#define M3_PATH "../sprites/gfx/weapons/m3_m.bmp"
#define AWP_PATH "../sprites/gfx/weapons/awp_m.bmp"
#define BUTTON_VIEW "../sprites/gfx/hud_slot.bmp"

// con gimp encontramos los parametros para Color Key
#define R_KEY 0xff
#define G_KEY 0
#define B_KEY 0xff

#define AK_CODE 0
#define M3_CODE 1
#define AWP_CODE 2

class BuyingMenu {
private:
    std::vector<Button> menuButtons;
    SdlTexture buttonSlot;
    std::vector<SdlTexture> buttonContTextures;
    uint8_t lastButtonPressed;
public:
    explicit BuyingMenu(SdlWindow& window);

    void showMenu();

    ~BuyingMenu();

    bool isButtonPressed(int mouseX, int mouseY);

    uint8_t getPressedButtonCode();
};


#endif
