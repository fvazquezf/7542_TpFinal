#include "SdlSound.h"

SdlSound::SdlSound(const std::string &soundPath)
: effect(Mix_LoadWAV(soundPath.c_str())) {
    if (!effect) {
        throw Exception("SdlSound: ", Mix_GetError());
    }
}

SdlSound::~SdlSound() {
    if (effect != nullptr) {
        Mix_FreeChunk(effect);
    }
}

SdlSound::SdlSound(SdlSound &&other)
: effect(other.effect) {
    other.effect = nullptr;
}

SdlSound &SdlSound::operator=(SdlSound &&other)  {
    if (this == &other) {
        return *this;
    }
    if ((effect != nullptr) && (effect != other.effect)) {
        Mix_FreeChunk(effect);
    }

    effect = other.effect;
    other.effect = nullptr;

    return *this;
}

int SdlSound::play() {
    return Mix_PlayChannel(-1, effect, 0);
}
