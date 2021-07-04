#include "MoneyUpdate.h"

// TODO: cambiar money a uint16_t
MoneyUpdate::MoneyUpdate(uint8_t money)
: money(money){
}

void MoneyUpdate::serialize(std::function<void(std::vector<unsigned char>)>& callback) {
    protocol.updateMoney(money, callback);
}

MoneyUpdate::~MoneyUpdate() {
}
