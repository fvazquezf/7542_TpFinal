#include "Attack.h"

Attack::Attack(bool done)
: done(done){
}

void Attack::serialize(std::function<void(std::vector<unsigned char>)> &callback, const Protocol &protocol) {
    protocol.attack(done, callback);
}

Attack::~Attack() {
}
