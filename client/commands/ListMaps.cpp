//
// Created by leogm99 on 5/7/21.
//

#include "ListMaps.h"

ListMaps::ListMaps() {
}

void ListMaps::serialize(std::function<void(std::vector<unsigned char>)> &callback, const Protocol &protocol) {
    protocol.handleByte(LIST_MAPS, callback);
}

ListMaps::~ListMaps() {
}
