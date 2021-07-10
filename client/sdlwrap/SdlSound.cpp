//
// Created by leogm99 on 4/7/21.
//

#include "SdlSound.h"

SdlSound::SdlSound(const std::string &soundPath)
: effect(Mix_LoadWAV(soundPath.c_str())) {
    if (!effect) {
        // Usar exceptions propias.
        throw std::exception();
    }
}

SdlSound::~SdlSound() {
    if (effect != nullptr){
        Mix_FreeChunk(effect);
    }
}

// Revisar todos los usos de noexcept. Usar esto puede traer problemas en ejecución muy
//  complicados de debuggear.
SdlSound::SdlSound(SdlSound &&other) noexcept
: effect(other.effect) {
    other.effect = nullptr;
}

SdlSound &SdlSound::operator=(SdlSound &&other) noexcept {
    if (this == &other){
        return *this;
    }

    // Y si effect == other.effect?
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
