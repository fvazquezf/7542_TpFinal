#include "SdlSound.h"

SdlSound::SdlSound(const std::string &soundPath)
: effect(Mix_LoadWAV(soundPath.c_str())){
    if (!effect){
        throw std::exception();
    }
}

SdlSound::~SdlSound() {
    if (effect != nullptr){
        Mix_FreeChunk(effect);
    }
}

SdlSound::SdlSound(SdlSound &&other) noexcept
: effect(other.effect){
    other.effect = nullptr;
}

SdlSound &SdlSound::operator=(SdlSound &&other) noexcept {
    if (this == &other){
        return *this;
    }
    if (effect != nullptr){
        Mix_FreeChunk(effect);
    }

    effect = other.effect;
    other.effect = nullptr;

    return *this;
}

int SdlSound::play() {
    return Mix_PlayChannel(-1, effect, 0);
}
