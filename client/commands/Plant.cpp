#include "Plant.h"

Plant::Plant(bool isPlanting)
: planting(isPlanting) {
}

void Plant::serialize(std::function<void(std::vector<unsigned char>)> &callback, const Protocol &protocol) {
    protocol.startStopCommand(planting ? PLANT : STOP_PLANT, callback);
}

Plant::~Plant() {
}
