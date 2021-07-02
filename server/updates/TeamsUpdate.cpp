#include "TeamsUpdate.h"

TeamsUpdate::TeamsUpdate(std::map<uint8_t, bool> teamsUpdates)
: teamsUpdates(std::move(teamsUpdates)){
}

void TeamsUpdate::serialize(std::function<void(std::vector<unsigned char>)>& callback) {
    // superProtocolo
    // protocol.updatePositions(positionUpdates, callback);
}

TeamsUpdate::~TeamsUpdate() {

}
