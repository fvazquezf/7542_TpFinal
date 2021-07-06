#include "Attack.h"

Attack::Attack(bool done)
: done(done){
}

void Attack::serialize(std::function<void(std::vector<unsigned char>)> &callback, const Protocol &protocol) {
    protocol.startStopCommand(done ? STOP_ATTACK : ATTACK, callback);
}

Attack::~Attack() {
}
