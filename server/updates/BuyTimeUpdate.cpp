#include "BuyTimeUpdate.h"

BuyTimeUpdate::BuyTimeUpdate(bool buyingTime)
: buyingTime(buyingTime) {
}

void BuyTimeUpdate::serialize(std::function<void(std::vector<unsigned char>)> &callback) {
    protocol.updateBuyingTime(buyingTime, callback);
}

BuyTimeUpdate::~BuyTimeUpdate() {

}
