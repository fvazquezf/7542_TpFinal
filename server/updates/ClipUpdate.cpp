#include "ClipUpdate.h"

ClipUpdate::ClipUpdate(uint8_t clip)
: clip(clip){
}

void ClipUpdate::serialize(std::function<void(std::vector<unsigned char>)>& callback) {
    protocol.updatePlayerState(CLIP_UPDATE, clip, callback);
}

ClipUpdate::~ClipUpdate() {
}
