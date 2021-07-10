//
// Created by leogm99 on 8/7/21.
//

#include "LobbyScreen.h"
#include "SoundManager.h"

LobbyScreen::LobbyScreen(SdlWindow &window)
: window(window),
  // como en otros lugares del código, tener mucho cuidado con los paths y revisar que
  // funcionen cuando haya instalador. Una manera es mandar todos los paths a un archivo
  // de configuración que se podría generar en el momento de la instalación.
  buttonSlot("../sprites/gfx/hud_slot.bmp",window),
  backgroundTexture("../sprites/gfx/splash.bmp", window),
  buttonBackgroundTexture("../sprites/gfx/gametitle.png", window),
  startEarlyButton((window.getWidth() / 2) - 75, 2 * window.getHeight() / 3, 150, 40,
                   buttonSlot,
                   buttonBackgroundTexture,
                   SDL_Rect{0, 0, 48, 20},
                   0){
    SoundManager::playMusic();
}

void LobbyScreen::draw() {
    Area src(0, 0, 1280, 720);
    Area dst(0, 0, window.getWidth(), window.getHeight());
    backgroundTexture.render(src, dst, SDL_FLIP_NONE);
    startEarlyButton.show();
}

LobbyScreen::~LobbyScreen() {

}

void LobbyScreen::stopPlayingLobbyMusic() {
    try {
        SoundManager::stopMusic();
    } catch (const std::exception& e){
        SoundManager::haltMusic();
    }
}

bool LobbyScreen::isButtonPressed(int mouseX, int mouseY) {
    return startEarlyButton.checkPressed(mouseX, mouseY);
}
