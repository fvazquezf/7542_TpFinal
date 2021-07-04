#include "MoneyUpdate.h"

MoneyUpdate::MoneyUpdate(uint8_t money)
: money(money){
}

void MoneyUpdate::serialize(std::function<void(std::vector<unsigned char>)>& callback) {
}

MoneyUpdate::~MoneyUpdate() {
}
