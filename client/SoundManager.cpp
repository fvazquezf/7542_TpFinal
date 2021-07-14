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
    if (!on) {
        return;
    }

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
    uint8_t soundDistanceSdl = 0;
    if (distance >= 12.75) {
        soundDistanceSdl = 255; // no se escucha nada
    } else {
        soundDistanceSdl = 20 * distance; // a lo sumo es 255 ;)
    }
    Mix_SetDistance(channel, soundDistanceSdl);
}

void SoundManager::start(bool onFlag) {
    SoundManager::getSoundManager().pStart(onFlag);
}

void SoundManager::pStart(bool onFlag) {
    this->on = onFlag;
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
    soundMap.emplace(std::piecewise_construct,
                     std::forward_as_tuple(soundRepertoire::BOMB_EXPLODE),
                     std::forward_as_tuple(path + "weapons/c4_explode.wav"));

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
    if (!on) {
        return;
    }
    if (music == nullptr){
        return;
    }

    Mix_PlayMusic(music, 0);
}

void SoundManager::stopMusic() {
    SoundManager::getSoundManager().pStopMusic();
}

void SoundManager::pStopMusic() {
    if (!on) {
        return;
    }

    if (!Mix_FadeOutMusic(1000)){
        throw std::exception();
    }
}

void SoundManager::haltMusic() {
    SoundManager::getSoundManager().pHaltMusic();
}

void SoundManager::pHaltMusic() {
    Mix_HaltMusic();
}
