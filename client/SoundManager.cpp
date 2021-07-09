//
// Created by leogm99 on 4/7/21.
//

#include "SoundManager.h"

SoundManager::SoundManager()
: chunksPlaying(0){

}

SoundManager::~SoundManager() {
    Mix_FreeMusic(music);
}

SoundManager &SoundManager::getSoundManager() {
    static SoundManager soundManager;
    return soundManager;
}

void SoundManager::playSound(int soundId, float distanceFromPlayer) {
    getSoundManager().pPlaySound(soundId, distanceFromPlayer);
}

void SoundManager::pPlaySound(int code, float distance) {
    if (soundMap.count(code) == 0){
        return; // no existe el sonido
    }

    if (distance > MAX_SOUND_DISTANCE){
        return;
    }

    if (chunksPlaying == MAX_CHUNKS){
        return;
    }

    int channel = soundMap.at(code).play();
    if (channel == -1) {
        return;
    } else {
        ++chunksPlaying;
    }
    uint8_t soundDistance = 20 * distance;
    Mix_SetDistance(channel, soundDistance);
}

void SoundManager::start() {
    SoundManager::getSoundManager().pStart();
}

void SoundManager::pStart() {
    chunksPlaying = 0;
    std::string path = SOUND_PATH;
    soundMap.emplace(std::piecewise_construct,
                     std::forward_as_tuple(soundRepertoire::KNF_S),
                     std::forward_as_tuple(path + "weapons/knife_slash.wav"));
    soundMap.emplace(std::piecewise_construct,
                     std::forward_as_tuple(soundRepertoire::GLOCK_S),
                     std::forward_as_tuple(path + "weapons/glock18.wav"));
    soundMap.emplace(std::piecewise_construct,
                     std::forward_as_tuple(soundRepertoire::AK47_S),
                     std::forward_as_tuple(path + "weapons/ak47.wav"));
    soundMap.emplace(std::piecewise_construct,
                     std::forward_as_tuple(soundRepertoire::M3_S),
                     std::forward_as_tuple(path + "weapons/m3.wav"));
    soundMap.emplace(std::piecewise_construct,
                     std::forward_as_tuple(soundRepertoire::AWP_S),
                     std::forward_as_tuple(path + "weapons/awp.wav"));
    soundMap.emplace(std::piecewise_construct,
                     std::forward_as_tuple(soundRepertoire::STEP1),
                     std::forward_as_tuple(path + "player/pl_step1.wav"));
    soundMap.emplace(std::piecewise_construct,
                     std::forward_as_tuple(soundRepertoire::DIE1),
                     std::forward_as_tuple(path + "player/die1.wav"));
    soundMap.emplace(std::piecewise_construct,
                     std::forward_as_tuple(soundRepertoire::HIT1),
                     std::forward_as_tuple(path + "player/hit1.wav"));
    soundMap.emplace(std::piecewise_construct,
                     std::forward_as_tuple(soundRepertoire::GO),
                     std::forward_as_tuple(path + "radio/go.ogg"));
    soundMap.emplace(std::piecewise_construct,
                     std::forward_as_tuple(soundRepertoire::BOMB_PLANTED),
                     std::forward_as_tuple(path + "radio/bombpl.ogg"));
    soundMap.emplace(std::piecewise_construct,
                     std::forward_as_tuple(soundRepertoire::CT_WIN),
                     std::forward_as_tuple(path + "radio/ctwin.ogg"));
    soundMap.emplace(std::piecewise_construct,
                     std::forward_as_tuple(soundRepertoire::TT_WIN),
                     std::forward_as_tuple(path + "radio/terwin.ogg"));
    soundMap.emplace(std::piecewise_construct,
                     std::forward_as_tuple(soundRepertoire::DROP_WEAPON),
                     std::forward_as_tuple(path + "items/drop.wav"));
    soundMap.emplace(std::piecewise_construct,
                     std::forward_as_tuple(soundRepertoire::PICKUP_WEAPON),
                     std::forward_as_tuple(path + "items/pickup.wav"));

    music = Mix_LoadMUS((path + "menu.wav").c_str());
    Mix_ChannelFinished(channelFinishedCallback);
}

void SoundManager::channelFinishedCallback(int channel) {
    --(SoundManager::getSoundManager().chunksPlaying);
}

void SoundManager::playMusic() {
    SoundManager::getSoundManager().pPlayMusic();
}

void SoundManager::pPlayMusic() {
    if (music == nullptr){
        return;
    }

    Mix_PlayMusic(music, 0);
}

void SoundManager::stopMusic() {
    SoundManager::getSoundManager().pStopMusic();
}

void SoundManager::pStopMusic() {
    if (!Mix_FadeOutMusic(1000)){
        throw std::exception();
    }
    //Mix_HaltMusic();
}

void SoundManager::haltMusic() {
    SoundManager::getSoundManager().pHaltMusic();
}

void SoundManager::pHaltMusic() {
    Mix_HaltMusic();
}
