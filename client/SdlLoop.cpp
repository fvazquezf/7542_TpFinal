#include "SdlLoop.h"
#include <SDL2/SDL.h>
#include "commands/Move.h"
#include "commands/CreateGame.h"
#include "commands/JoinGame.h"
#include "commands/Rotate.h"
#include "commands/Attack.h"
#include "commands/ChangeWeapon.h"
#include "commands/Buy.h"
#include "commands/Pickup.h"
#include <functional>

SdlLoop::SdlLoop(BlockingQueue<std::unique_ptr<Command>> &commandsQ, WorldView& world)
: done(false), commands(commandsQ), world(world){
    eventMap[SDL_KEYDOWN] = std::bind(&SdlLoop::handleKeyDown, this);
    eventMap[SDL_KEYUP] = std::bind(&SdlLoop::handleKeyUp, this);
    eventMap[SDL_MOUSEBUTTONDOWN] = std::bind(&SdlLoop::handleMouseButtonDown, this);
    eventMap[SDL_MOUSEBUTTONUP] = std::bind(&SdlLoop::handleMouseButtonUp, this);
    eventMap[SDL_QUIT] = std::bind(&SdlLoop::handleQuit, this);

    numbers.insert(SDLK_1);
    numbers.insert(SDLK_2);
    numbers.insert(SDLK_3);
    numbers.insert(SDLK_4);

    presses[SDLK_w] = false;
    presses[SDLK_a] = false;
    presses[SDLK_s] = false;
    presses[SDLK_d] = false;

    mousePresses[SDL_BUTTON_LEFT] = false;
    mousePresses[SDL_BUTTON_RIGHT] = false;
}

void SdlLoop::run() {
    Uint32 delay = 20;
    SDL_TimerID my_timer_id = SDL_AddTimer(delay, SdlLoop::issueSynchronousEvent, this);
    while (!done && SDL_WaitEvent(&currentEvent)){
        try {
            eventMap.at(currentEvent.type)();
        } catch(const std::exception& e){
            continue;
        }
    }
    commands.signalClosed();
    SDL_RemoveTimer(my_timer_id);
}

SdlLoop::~SdlLoop() {

}

bool SdlLoop::isDone() {
    return done;
}

void SdlLoop::handleKeyDown() {
    /*if (world.isMenuTime()){
        return;
    }*/
    try {
        handleKey(true, currentEvent.key.keysym.sym);
    } catch(const std::exception& e){
        return;
    }
}

void SdlLoop::handleKeyUp() {
    /*if (world.isMenuTime()){
        return;
    }*/
    try {
        handleKey(false, currentEvent.key.keysym.sym);
    } catch(const std::exception& e){
        return;
    }
}

void SdlLoop::handleMouseButtonDown() {
    try {
        mouseButton(true, currentEvent.button.button);
    } catch(const std::exception& e){
        return;
    }
}

void SdlLoop::handleMouseButtonUp() {
    try {
        mouseButton(false, currentEvent.button.button);
    } catch(const std::exception& e){
        return;
    }
}

void SdlLoop::handleQuit(){
    done = true;
}

void SdlLoop::handleKey(bool pressed, SDL_Keycode key){
    // tecla a la cual no trackeamos
    // estos son los cambios de arma
    if (key == SDLK_e){
        if (pressed){
            commands.push(std::unique_ptr<Command>(new Pickup()));
        }
        else {
            return;
        }
    }

    if (pressed && (numbers.find(key) != numbers.end())){
        commands.push(std::unique_ptr<Command>(new ChangeWeapon(key)));
        return;
    }

    if (pressed && !presses.at(key)){
        presses.at(key) = true;
        commands.push(std::unique_ptr<Command>(new Move(key)));
    } else if (!pressed){
        presses.at(key) = false;
        commands.push(std::unique_ptr<Command>(new Move(key, true)));
    }
}

void SdlLoop::mouseButton(bool pressed, uint8_t button){
    int mouseX, mouseY = 0;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (pressed && world.menuButtonPressed(mouseX, mouseY)){
        commands.push(std::unique_ptr<Command>(new Buy(world.getPressedButtonCode())));
        return;
    } else if (pressed && !mousePresses.at(button)){
        mousePresses.at(button) = true;
        commands.push(std::unique_ptr<Command>(new Attack()));
    } else if (!pressed){
        mousePresses.at(button) = false;
        commands.push(std::unique_ptr<Command>(new Attack(true)));
    }
}

Uint32 SdlLoop::issueSynchronousEvent(Uint32 interval, void *param) {
    auto loop = (SdlLoop *) (param);
    loop->handleRotation();
    return interval;
}

void SdlLoop::handleRotation() {
    int16_t angle = world.getPlayerAngle();
    commands.push(std::unique_ptr<Command>(new Rotate(angle)));
}
