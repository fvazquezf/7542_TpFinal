#include "Rotate.h"

Rotate::Rotate(int16_t angle)
: angle(angle) {
}

Rotate::~Rotate() {
}

void Rotate::serialize(std::function<void(std::vector<unsigned char>)> &callback, const Protocol &protocol) {
    protocol.rotate(angle, callback);
}

