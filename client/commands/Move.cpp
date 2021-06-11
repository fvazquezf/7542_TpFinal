#include "Move.h"

Move::Move(Move::Direction dir, bool isDone)
: dir(dir), isDoneMove(isDone){
}

void Move::serialize(std::function<void(std::vector<unsigned char>)> &callback, const Protocol &protocol) {
    protocol.move(dir, isDoneMove, callback);
}

Move::~Move() {

}
