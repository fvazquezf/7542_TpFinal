#include "PositionUpdate.h"

PositionUpdate::PositionUpdate(std::map<uint8_t, std::pair<float, float>> positionUpdates)
: positionUpdates(std::move(positionUpdates)){
}

void PositionUpdate::serialize(std::function<void(std::vector<unsigned char>)>& callback) {
    protocol.updatePositions(positionUpdates, callback);
}

PositionUpdate::~PositionUpdate() {

}
