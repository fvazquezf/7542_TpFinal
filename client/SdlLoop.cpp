#include "SdlLoop.h"
#include <SDL2/SDL.h>
#include "commands/Move.h"
#include "commands/CreateGame.h"
#include "commands/Rotate.h"
#include "commands/Attack.h"
#include "commands/ChangeWeapon.h"
#include "commands/Buy.h"
#include "commands/Pickup.h"
#include "commands/Reload.h"
#include "commands/Plant.h"
#include <functional>
#include <commands/EarlyStart.h>

SdlLoop::SdlLoop(BlockingQueue<std::unique_ptr<Command>> &commandsQ, WorldView& world)
: done(false), commands(commandsQ), world(world) {
    eventMap[SDL_KEYDOWN] = std::bind(&SdlLoop::handleKeyDown, this);
    eventMap[SDL_KEYUP] = std::bind(&SdlLoop::handleKeyUp, this);
    eventMap[SDL_MOUSEBUTTONDOWN] = std::bind(&SdlLoop::handleMouseButtonDown, this);
    eventMap[SDL_MOUSEBUTTONUP] = std::bind(&SdlLoop::handleMouseButtonUp, this);
    eventMap[SDL_QUIT] = std::bind(&SdlLoop::handleQuit, this);

    numbers.insert(SDLK_1);
    numbers.insert(SDLK_2);
    numbers.insert(SDLK_3);
    numbers.insert(SDLK_4);

    movePresses[SDLK_w] = false;
    movePresses[SDLK_a] = false;
    movePresses[SDLK_s] = false;
    movePresses[SDLK_d] = false;

    miscPresses[SDLK_e] = false;
    miscPresses[SDLK_SPACE] = false;
    miscPresses[SDLK_r] = false;

    mousePresses[SDL_BUTTON_LEFT] = false;
    mousePresses[SDL_BUTTON_RIGHT] = false;
}

void SdlLoop::run() {
    Uint32 delay = 20;
    SDL_TimerID my_timer_id = SDL_AddTimer(delay, SdlLoop::issueSynchronousEvent, this);
    while (!done && SDL_WaitEvent(&currentEvent)) {
        try {
            eventMap.at(currentEvent.type)();
        } catch(const std::exception& e) {
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
    try {
        handleKey(true, currentEvent.key.keysym.sym);
    } catch(const std::exception& e) {
        return;
    }
}

void SdlLoop::handleKeyUp() {
    try {
        handleKey(false, currentEvent.key.keysym.sym);
    } catch(const std::exception& e) {
        return;
    }
}

void SdlLoop::handleMouseButtonDown() {
    try {
        mouseButton(true, currentEvent.button.button);
    } catch(const std::exception& e) {
        return;
    }
}

void SdlLoop::handleMouseButtonUp() {
    try {
        mouseButton(false, currentEvent.button.button);
    } catch(const std::exception& e) {
        return;
    }
}

void SdlLoop::handleQuit() {
    done = true;
}

void SdlLoop::handleKey(bool pressed, SDL_Keycode key) {
    if (world.isMenuTime()) {
        if (menuPresses.count(key)) {
            menuPresses.erase(key);
        } else {
            menuPresses.emplace(key, pressed);
        }
        return;
    }

    // bug de movimiento infinito despues del tiempo de menu
    // es tan solo un hotfix
    if (!menuPresses.empty()) {
        try {
            bool wasPressed = menuPresses.at(key);
            if (wasPressed != pressed) {
                menuPresses.erase(key);
                return;
            }
        } catch (const std::exception& e) {
            return;
        }
    }

    if (pressed && (miscPresses.find(key) != miscPresses.end()) && !miscPresses.at(key)) {
        if (key == SDLK_e) {
            commands.push(std::unique_ptr<Command>(new Pickup()));
        } else if (key == SDLK_SPACE) {
            commands.push(std::unique_ptr<Command>(new Plant(true)));
        } else if (key == SDLK_r) {
            commands.push(std::unique_ptr<Command>(new Reload()));
        }
        miscPresses.at(key) = true;
        return;
    } else if (!pressed && (miscPresses.find(key) != miscPresses.end()) &&miscPresses.at(key)) {
        if (key == SDLK_SPACE) {
            commands.push(std::unique_ptr<Command>(new Plant(false)));
        }
        miscPresses.at(key) = false;
        return;
    }

    if (pressed && (numbers.find(key) != numbers.end())) {
        commands.push(std::unique_ptr<Command>(new ChangeWeapon(key)));
        return;
    }

    if (pressed && !movePresses.at(key)) {
        movePresses.at(key) = true;
        commands.push(std::unique_ptr<Command>(new Move(key)));
    } else if (!pressed) {
        movePresses.at(key) = false;
        commands.push(std::unique_ptr<Command>(new Move(key, true)));
    }
}

void SdlLoop::mouseButton(bool pressed, uint8_t button) {
    int mouseX, mouseY = 0;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (pressed && !world.skinSelectionTime() && world.menuButtonPressed(mouseX, mouseY) ) {
        commands.push(std::unique_ptr<Command>(new Buy(world.getPressedButtonCode())));
        return;
    } else if (pressed && world.lobbyButtonPressed(mouseX, mouseY)) {
        commands.push(std::unique_ptr<Command>(new EarlyStart()));
        return;
    } else if (pressed && world.skinSelectionTime()) {
        world.selectSkin();
        return;
    } else if (pressed && !mousePresses.at(button)) {
        mousePresses.at(button) = true;
        commands.push(std::unique_ptr<Command>(new Attack()));
    } else if (!pressed) {
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
