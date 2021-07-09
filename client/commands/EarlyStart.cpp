//
// Created by leogm99 on 8/7/21.
//

#include "EarlyStart.h"

EarlyStart::EarlyStart() {
}

void EarlyStart::serialize(std::function<void(std::vector<unsigned char>)> &callback, const Protocol &protocol) {
    protocol.handleByte(EARLY_START, callback);
}

EarlyStart::~EarlyStart() {

}
