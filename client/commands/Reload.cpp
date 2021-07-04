//
// Created by leogm99 on 3/7/21.
//

#include "Reload.h"

Reload::Reload() {
}

void Reload::serialize(std::function<void(std::vector<unsigned char>)> &callback, const Protocol &protocol) {
    protocol.handleByte(RELOAD, callback);
}

Reload::~Reload() {
}
