#include "Pickup.h"

Pickup::Pickup() {

}

void Pickup::serialize(std::function<void(std::vector<unsigned char>)> &callback, const Protocol &protocol) {
    protocol.handleByte(PICKUP, callback);
}

Pickup::~Pickup() {

}


