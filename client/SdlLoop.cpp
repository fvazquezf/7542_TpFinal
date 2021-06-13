#include "SdlLoop.h"
#include <SDL2/SDL.h>
#include "commands/Move.h"
#include "commands/CreateGame.h"
#include "commands/JoinGame.h"

SdlLoop::SdlLoop(BlockingQueue<std::unique_ptr<Command>> &commandsQ, WorldView& world)
: done(false), commands(commandsQ), world(world){
}

void SdlLoop::run() {
    SDL_Event e;
    while(SDL_WaitEvent(&e) && !done){
        switch (e.type){
            case SDL_KEYDOWN:
                try{
                    handleKeyDown(e.key.keysym.sym);
                } catch (const std::invalid_argument& e){
                    std::cout << e.what();
                    break;
                }
                break;
            case SDL_KEYUP:
                try{
                    handleKeyUp(e.key.keysym.sym);
                } catch (const std::invalid_argument& e){
                    std::cout << e.what();
                    break;
                }
                break;
            case SDL_MOUSEMOTION:
                break;
            case SDL_MOUSEBUTTONDOWN:
                try {
                    handleMouseButtonDown(e.button);
                } catch(const std::invalid_argument& e) {
                    std::cout << e.what();
                    break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                /*try {
                    handleMouseButtonUp(e.button);
                } catch(const std::invalid_argument& e) {
                    std::cout << e.what();
                    break;
                }*/
                break;
            case SDL_QUIT:
                commands.signalClosed();
                done = true;
        }
    }
}

SdlLoop::~SdlLoop() {

}

bool SdlLoop::isDone() {
    return done;
}

void SdlLoop::handleKeyDown(SDL_Keycode keyPressed) {
    std::unique_ptr<Command> comm;
    switch (keyPressed){
        case SDLK_w:
            comm = std::unique_ptr<Command> (new Move(Move::UP));
            break;
        case SDLK_s:
            comm = std::unique_ptr<Command> (new Move(Move::DOWN));
            break;
        case SDLK_a:
            comm = std::unique_ptr<Command> (new Move(Move::LEFT));
            break;
        case SDLK_d:
            comm = std::unique_ptr<Command> (new Move(Move::RIGHT));
            break;
        default:
            // throw exception, key invalid
            // deberiamos volver a leer un evento;
            throw std::invalid_argument("Key inval excep\n");
    }
    // se supone que si llegue hasta aca
    // el evento es valido
    commands.push(std::move(comm));
}

void SdlLoop::handleKeyUp(SDL_Keycode keyReleased) {
    std::unique_ptr<Command> comm;
    switch (keyReleased){
        case SDLK_w:
            comm = std::unique_ptr<Command>(new Move(Move::UP, true));
            break;
        case SDLK_s:
            comm = std::unique_ptr<Command>(new Move(Move::DOWN, true));
            break;
        case SDLK_a:
            comm = std::unique_ptr<Command>(new Move(Move::LEFT, true));
            break;
        case SDLK_d:
            comm = std::unique_ptr<Command>(new Move(Move::RIGHT, true));
            break;
        default:
            // throw exception, key invalid
            // deberiamos volver a leer un evento;
            throw std::invalid_argument("Key inval excep\n");
    }
    // se supone que si llegue hasta aca
    // el evento es valido
    commands.push(std::move(comm));
}

// para probar a ver si funcan los comandos
void SdlLoop::handleMouseButtonDown(SDL_MouseButtonEvent mouseEvent) {
    std::unique_ptr<Command> comm;
    switch (mouseEvent.button){
        case SDL_BUTTON_LEFT:{
            comm = std::unique_ptr<Command>(new CreateGame("UnaPartida"));
            break;
        }
        case SDL_BUTTON_RIGHT:{
            break;
        }
        default:
            throw std::invalid_argument("Invalid mouse event\n");
    }
    commands.push(std::move(comm));
}

void SdlLoop::handleMouseButtonUp(SDL_MouseButtonEvent mouseEvent) {
    std::unique_ptr<Command> comm;
    switch (mouseEvent.button){
        case SDL_BUTTON_LEFT:{
            break;
        }
        case SDL_BUTTON_RIGHT:{
            break;
        }
        default:
            throw std::invalid_argument("Invalid mouse event\n");
    }
    commands.push(std::move(comm));
}
