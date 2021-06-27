#ifndef SDLLOOP_H
#define SDLLOOP_H

#include <memory>
#include "../common/Thread.h"
#include "../common/Protocol.h"
#include "../common/BlockingQueue.h"
#include "commands/Command.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include "WorldView.h"
#include <map>
#include <set>

class SdlLoop : public Thread{
private:
    bool done;
    Protocol prot;
    BlockingQueue<std::unique_ptr<Command>>& commands;
    WorldView& world;
    SDL_Event currentEvent;

    std::map<uint32_t, std::function<void()>> eventMap;
    // tracks if the key has been pressed and not released
    std::map<SDL_Keycode, bool> presses;
    // keeps posible number presses
    std::set<SDL_Keycode> numbers;
    // tracks if the button has been pressed and not released
    std::map<uint8_t, bool> mousePresses;

    void handleKey(bool pressed, SDL_Keycode key);
    void mouseButton(bool pressed, uint8_t button);

    void handleKeyDown();
    void handleKeyUp();
    void handleMouseButtonDown();
    void handleMouseButtonUp();
    void handleQuit();
    void handleRotation();

    static Uint32 issueSynchronousEvent(Uint32 interval, void* param);

    void run() override;
public:
    SdlLoop(BlockingQueue<std::unique_ptr<Command>>& commandsQ, WorldView& world);

    bool isDone();

    ~SdlLoop() override;
};


#endif
