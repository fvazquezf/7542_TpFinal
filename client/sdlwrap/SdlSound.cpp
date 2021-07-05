//
// Created by leogm99 on 4/7/21.
//

#include "SdlSound.h"

SdlSound::SdlSound(const std::string &soundPath)
: effect(Mix_LoadWAV(soundPath.c_str())){
    if (!effect){
        throw std::exception();
    }
}

// "deleting null pointer has no effect"
// por eso no pongo el if
SdlSound::~SdlSound() {
    delete effect;
}

SdlSound::SdlSound(SdlSound &&other) noexcept
: effect(other.effect){
    other.effect = nullptr;
}

SdlSound &SdlSound::operator=(SdlSound &&other) noexcept {
    if (this == &other){
        return *this;
    }
    effect = other.effect;
    other.effect = nullptr;

    return *this;
}

int SdlSound::play() {
    return Mix_PlayChannel(-1, effect, 0);
}
