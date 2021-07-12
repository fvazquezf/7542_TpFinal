#include "BuyingMenu.h"

BuyingMenu::BuyingMenu(SdlWindow& window, SdlTexture& hudButton)
: window(window),
  buttonSlot(hudButton){
    // creo las texturas de los botones
    buttonContTextures.emplace_back(AK_PATH, window, Color{R_KEY, G_KEY, B_KEY});
    buttonContTextures.emplace_back(M3_PATH, window, Color{R_KEY, G_KEY, B_KEY});
    buttonContTextures.emplace_back(AWP_PATH, window, Color{R_KEY, G_KEY, B_KEY});

    // creo los botones
    menuButtons.emplace_back(200, 100, 150, 40,
                             buttonSlot,
                             buttonContTextures.at(0),
                             SDL_Rect{0, 0, 51, 17},
                             AK_CODE);

    menuButtons.emplace_back(200, 300, 150, 40,
                             buttonSlot,
                             buttonContTextures.at(1),
                             SDL_Rect{0, 0, 66, 16},
                             M3_CODE);

    menuButtons.emplace_back(200, 500, 150, 40,
                             buttonSlot,
                             buttonContTextures.at(2),
                             SDL_Rect{0, 0, 50, 16},
                             AWP_CODE);
}

BuyingMenu::~BuyingMenu() {

}

void BuyingMenu::showMenu() {
    window.drawRectangle(50, 150, 50, 500, 550);
    for (auto& it : menuButtons){
        it.show();
    }
}

bool BuyingMenu::isButtonPressed(int mouseX, int mouseY) {
    for (auto& it : menuButtons){
        if (it.checkPressed(mouseX, mouseY)){
            lastButtonPressed = it.getCode();
            return true;
        }
    }
    return false;
}

uint8_t BuyingMenu::getPressedButtonCode() {
    return lastButtonPressed;
}
