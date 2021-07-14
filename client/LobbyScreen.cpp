#include "LobbyScreen.h"
#include "SoundManager.h"

LobbyScreen::LobbyScreen(SdlWindow &window, SdlTexture& hudButton)
: window(window),
  backgroundTexture("../sprites/gfx/splash.bmp", window),
  buttonBackgroundTexture("../sprites/gfx/gametitle.png", window),
  waitingTextScreen("../sprites/fonts/counter_strike.ttf",
                    window,
                    30),
  startEarlyButton((window.getWidth() / 2) - 75, 2 * window.getHeight() / 3, 150, 40,
                   hudButton,
                   buttonBackgroundTexture,
                   SDL_Rect{0, 0, 48, 20},
                   0){
    //SoundManager::playMusic();
    waitingTextScreen.setText("Espera a otros jugadores o toca el boton para jugar");
}

void LobbyScreen::draw() {
    auto width = window.getWidth();
    auto height = window.getHeight();
    Area srcBackground(0, 0, 1280, 720);
    Area dstBackground(0, 0, width, height);
    backgroundTexture.render(srcBackground, dstBackground, SDL_FLIP_NONE);

    Area txtDst(50, height / 3, 650, 100);
    waitingTextScreen.render(txtDst);
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
