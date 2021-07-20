#include "HpUpdate.h"

HpUpdate::HpUpdate(uint8_t hp)
: hp(hp) {
}

void HpUpdate::serialize(std::function<void(std::vector<unsigned char>)>& callback) {
    protocol.updatePlayerState(HEALTH_UPDATE, hp, callback);
}

HpUpdate::~HpUpdate() {
}
