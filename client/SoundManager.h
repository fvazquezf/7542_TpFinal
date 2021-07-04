//
// Created by leogm99 on 4/7/21.
//

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#define SOUND_PATH "../sprites/sfx/"

#include <map>
#include "sdlwrap/SdlSound.h"
#define MAX_SOUND_DISTANCE 25.0f
#define MAX_CHUNKS 5

// sound manager unico
// singleton instance
class SoundManager {
private:
    // contenedor de todos los sonidos
    // si el sonido no existe se crea
    // y si existe se reproduce desde aca
    std::map<int, SdlSound> soundMap;

    // cuadno un channel termina un sonido
    // este callback reduce la cantidad de chunks
    // que se estan reproduciendo (pq el ultimo termino)
    size_t chunksPlaying;

    void pStart();

    void pPlaySound(int code, float distance);
    // define por unica vez un objeto estatico
    // y devuelve una instancia
    static SoundManager& getSoundManager();

public:
    enum soundRepertoire : int {
        KNF_S, GLOCK_S, AK47_S, M3_S, AWP_S,
        STEP1, DIE1, HIT1, GO, BOMB_PLANTED,
        CT_WIN, TT_WIN, DROP_WEAPON, PICKUP_WEAPON
    };
    SoundManager();

    SoundManager(const SoundManager& other) = delete;
    SoundManager& operator=(const SoundManager& other) = delete;

    SoundManager(SoundManager&& other) = delete;
    SoundManager& operator=(SoundManager&& other) = delete;

    static void start();
    static void playSound(int soundId, float distanceFromPlayer);
    static void channelFinishedCallback(int channel);
    ~SoundManager();
};


#endif
