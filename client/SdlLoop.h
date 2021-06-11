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

class SdlLoop : public Thread{
private:
    bool done;
    Protocol prot;
    BlockingQueue<std::unique_ptr<Command>>& commands;
public:
    explicit SdlLoop(BlockingQueue<std::unique_ptr<Command>>& commandsQ);

    void run() override;

    void handleKeyDown(SDL_Keycode keyPressed);
    void handleKeyUp(SDL_Keycode keyReleased);

    bool isDone();

    ~SdlLoop() override;
};


#endif
