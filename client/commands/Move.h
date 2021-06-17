#ifndef MOVE_H
#define MOVE_H

#include "Command.h"
#include <SDL2/SDL_keycode.h>
#include <map>

class Move : public Command{
public:
    // direcciones basicas, hay que ver como es el tema de mirar/apuntar
    // UP == 0, DOWN == 1, LEFT == 2, RIGHT == 3
    // Las unicas rotaciones que se pueden hacer son izq y der
    // Puedo mandar un mensaje para indicar hacia donde rotar
    // Esta rotacion coincide con mover el mouse para la izquierda o la derecha
    enum Direction : uint8_t {UP, DOWN, LEFT, RIGHT};

    // de base digamos que si llamo a move es false
    // pero si quiero decirle para de moverte
    // le mando true
    explicit Move(SDL_Keycode key, bool isDone = false);

    void serialize(std::function<void (std::vector<unsigned char>)> &callback,
                   const Protocol &protocol) override;

    ~Move() override;
private:
    uint8_t dir;
    bool isDoneMove;
    std::map<SDL_Keycode, Move::Direction> directionMap{
        {SDLK_w, Direction::UP},
        {SDLK_a, Direction::LEFT},
        {SDLK_s, Direction::DOWN},
        {SDLK_d, Direction::RIGHT}
    };
};


#endif
