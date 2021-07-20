#include "AngleUpdate.h"

AngleUpdate::AngleUpdate(std::map<uint8_t, int16_t> angles)
: angles(std::move(angles)) {
}

void AngleUpdate::serialize(std::function<void(std::vector<unsigned char>)> &callback) {
    protocol.updateAngles(angles, callback);
}

AngleUpdate::~AngleUpdate() {
}
