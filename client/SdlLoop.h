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

class SdlLoop : public Thread{
private:
    bool done;
    Protocol prot;
    BlockingQueue<std::unique_ptr<Command>>& commands;
    WorldView& world;
public:
    SdlLoop(BlockingQueue<std::unique_ptr<Command>>& commandsQ, WorldView& world);

    void run() override;

    void handleKeyDown(SDL_Keycode keyPressed);
    void handleKeyUp(SDL_Keycode keyReleased);

    void handleMouseButtonDown(SDL_MouseButtonEvent mouseEvent);
    void handleMouseButtonUp(SDL_MouseButtonEvent mouseEvent);

    bool isDone();

    ~SdlLoop() override;
};


#endif
