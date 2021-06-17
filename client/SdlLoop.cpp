#include "SdlLoop.h"
#include <SDL2/SDL.h>
#include "commands/Move.h"
#include "commands/CreateGame.h"
#include "commands/JoinGame.h"
#include <functional>

SdlLoop::SdlLoop(BlockingQueue<std::unique_ptr<Command>> &commandsQ, WorldView& world)
: done(false), commands(commandsQ), world(world){
    eventMap[SDL_KEYDOWN] = std::bind(&SdlLoop::handleKeyDown, this);
    eventMap[SDL_KEYUP] = std::bind(&SdlLoop::handleKeyUp, this);
    eventMap[SDL_MOUSEMOTION] = std::bind(&SdlLoop::handleMouseMotion, this);
    eventMap[SDL_MOUSEBUTTONDOWN] = std::bind(&SdlLoop::handleMouseButtonDown, this);
    eventMap[SDL_MOUSEBUTTONUP] = std::bind(&SdlLoop::handleMouseButtonUp, this);
    eventMap[SDL_QUIT] = std::bind(&SdlLoop::handleQuit, this);

    presses[SDLK_w] = false;
    presses[SDLK_a] = false;
    presses[SDLK_s] = false;
    presses[SDLK_d] = false;
}

void SdlLoop::run() {
    while (!done && SDL_WaitEvent(&currentEvent)){
        try {
            eventMap.at(currentEvent.type)();
        } catch(const std::exception& e){
            continue;
        }
    }
    commands.signalClosed();
}

SdlLoop::~SdlLoop() {

}

bool SdlLoop::isDone() {
    return done;
}

void SdlLoop::handleKeyDown() {
    try {
        handleKey(true, currentEvent.key.keysym.sym);
    } catch(const std::exception& e){
        return;
    }
}

void SdlLoop::handleKeyUp() {
    try {
        handleKey(false, currentEvent.key.keysym.sym);
    } catch(const std::exception& e){
        return;
    }
}

void SdlLoop::handleMouseMotion(){
}

void SdlLoop::handleMouseButtonDown() {
    try {
        mouseButton(false, currentEvent.button.button);
    } catch(const std::exception& e){
        return;
    }
}

void SdlLoop::handleMouseButtonUp() {
    try {
        //handleKey(false, currentEvent.button.button);
    } catch(const std::exception& e){
        return;
    }
}

void SdlLoop::handleQuit(){
    done = true;
}

void SdlLoop::handleKey(bool pressed, SDL_Keycode key){
    if (pressed && !presses.at(key)){
        presses.at(key) = true;
        commands.push(std::unique_ptr<Command>(new Move(key)));
    } else if (!pressed){
        presses.at(key) = false;
        commands.push(std::unique_ptr<Command>(new Move(key, true)));
    }
}

void SdlLoop::mouseButton(bool pressed, uint8_t button){
    if (button == SDL_BUTTON_LEFT){
        commands.push(std::unique_ptr<Command>(new CreateGame("UnaPartida")));
    } else if (button == SDL_BUTTON_RIGHT){
        commands.push(std::unique_ptr<Command>(new JoinGame("UnaPartida")));
    }
}
