#ifndef SDLLOOP_H
#define SDLLOOP_H

#include <vector>
#include <memory>
#include "../common/Thread.h"
#include "../common/Protocol.h"
#include "../common/BlockingQueue.h"
#include "commands/Command.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include "WorldView.h"
#include <map>

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

    void handleKey(bool pressed, SDL_Keycode key);
    void mouseButton(bool pressed, uint8_t button);

    void handleKeyDown();
    void handleKeyUp();
    void handleMouseMotion();
    void handleMouseButtonDown();
    void handleMouseButtonUp();
    void handleQuit();

    void run() override;
public:
    SdlLoop(BlockingQueue<std::unique_ptr<Command>>& commandsQ, WorldView& world);

    bool isDone();

    ~SdlLoop() override;
};


#endif
