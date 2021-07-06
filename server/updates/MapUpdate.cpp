//
// Created by leogm99 on 6/7/21.
//

#include "MapUpdate.h"

MapUpdate::MapUpdate(std::string map)
: map(std::move(map)){
}

void MapUpdate::serialize(std::function<void(std::vector<unsigned char>)> &callback) {
    protocol.updateMapInformation(map, callback);
}

MapUpdate::~MapUpdate() {
}
