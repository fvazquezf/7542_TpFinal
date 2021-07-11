#ifndef LOBBYSCREEN_H
#define LOBBYSCREEN_H


#include "sdlwrap/SdlWindow.h"
#include "sdlwrap/SdlTexture.h"
#include "Button.h"

// pantalla de lobby
// al crear una partida se dibuja un boton para iniciarla
// si estas uniendote solamente te muestra "awaitingPlayers"
class LobbyScreen {
private:
    SdlWindow& window;
    SdlTexture buttonSlot;
    SdlTexture backgroundTexture;
    SdlTexture buttonBackgroundTexture;
    SdlTexture waitingScreen;
    Button startEarlyButton;
public:
    explicit LobbyScreen(SdlWindow& window);

    LobbyScreen(const LobbyScreen& other) = delete;
    LobbyScreen& operator=(const LobbyScreen& other) = delete;

    LobbyScreen(LobbyScreen&& other) noexcept;
    LobbyScreen& operator=(LobbyScreen&& other) noexcept;

    void draw();
    void stopPlayingLobbyMusic();
    bool isButtonPressed(int mouseX, int mouseY);

    ~LobbyScreen();
};


#endif
