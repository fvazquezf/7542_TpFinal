#include "Buy.h"

Buy::Buy(uint8_t weaponCode)
: weaponCode(weaponCode){
}

void Buy::serialize(std::function<void(std::vector<unsigned char>)> &callback, const Protocol &protocol) {
    protocol.buy(weaponCode, callback);
}

Buy::~Buy() {
}
