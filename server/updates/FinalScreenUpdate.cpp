#include "FinalScreenUpdate.h"

FinalScreenUpdate::FinalScreenUpdate(std::vector<std::tuple<uint8_t, uint8_t, uint8_t, uint16_t, bool>> scores):
 scores(scores) {
}

void FinalScreenUpdate::serialize(std::function<void(std::vector<unsigned char>)> &callback) {
    protocol.updateScore(scores, callback);
}

FinalScreenUpdate::~FinalScreenUpdate() {
}
