#include "LobbyScreen.h"
#include "SoundManager.h"

LobbyScreen::LobbyScreen(SdlWindow &window)
: window(window),
  buttonSlot("../sprites/gfx/hud_slot.bmp",window),
  backgroundTexture("../sprites/gfx/splash.bmp", window),
  buttonBackgroundTexture("../sprites/gfx/gametitle.png", window),
  waitingScreen("../sprites/gfx/waiting.bmp", window, {0x20, 0x20, 0x80}),
  startEarlyButton((window.getWidth() / 2) - 75, 2 * window.getHeight() / 3, 150, 40,
                   buttonSlot,
                   buttonBackgroundTexture,
                   SDL_Rect{0, 0, 48, 20},
                   0){
    //SoundManager::playMusic();
}

void LobbyScreen::draw() {
    auto width = window.getWidth();
    auto height = window.getHeight();
    Area srcBackground(0, 0, 1280, 720);
    Area dstBackground(0, 0, width, height);
    backgroundTexture.render(srcBackground, dstBackground, SDL_FLIP_NONE);

    Area srcWaiting(0, 0, 1683, 495);
    Area dstWaiting(1/2 * width, 1/2 * height, width / 2, height / 2);
    waitingScreen.render(srcWaiting, dstWaiting, SDL_FLIP_NONE);
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
