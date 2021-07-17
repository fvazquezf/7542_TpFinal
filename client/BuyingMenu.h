#ifndef BUYINGMENU_H
#define BUYINGMENU_H

#include <vector>
#include "Button.h"
#include "sdlwrap/SdlText.h"
#include <yaml-cpp/yaml.h>

// con gimp encontramos los parametros para Color Key
#define R_KEY 0xff
#define G_KEY 0
#define B_KEY 0xff

#define AK_CODE 0
#define M3_CODE 1
#define AWP_CODE 2

class BuyingMenu {
private:
    SdlWindow& window;
    std::vector<Button> menuButtons;
    SdlTexture& buttonSlot;
    std::vector<SdlTexture> buttonContTextures;
    uint8_t lastButtonPressed;
    SdlText menuText;
    Area menuTextArea;
public:
    BuyingMenu(SdlWindow& window, SdlTexture& hudButton, YAML::Node& clientConfig);

    void showMenu();

    ~BuyingMenu();

    bool isButtonPressed(int mouseX, int mouseY);

    uint8_t getPressedButtonCode();
};


#endif
