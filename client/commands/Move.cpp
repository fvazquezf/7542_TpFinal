#include "Move.h"
#include <iostream>

Move::Move(SDL_Keycode key, bool isDone)
: isDoneMove(isDone) {
    dir = directionMap.at(key);
}

void Move::serialize(std::function<void(std::vector<unsigned char>)> &callback, const Protocol &protocol) {
    protocol.move(dir, isDoneMove, callback);
}

Move::~Move() {

}
