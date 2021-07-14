#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#define SOUND_PATH "../sprites/sfx/"

#include <map>
#include "sdlwrap/SdlSound.h"
#define MAX_SOUND_DISTANCE 25.0f
#define MAX_CHUNKS 10

// sound manager unico
// singleton instance
class SoundManager {
private:
    bool on;
    Mix_Music* music;
    // contenedor de todos los sonidos
    // si el sonido no existe se crea
    // y si existe se reproduce desde aca
    std::map<int, SdlSound> soundMap;

    // cuadno un channel termina un sonido
    // este callback reduce la cantidad de chunks
    // que se estan reproduciendo (pq el ultimo termino)
    size_t chunksPlaying;

    void pStart(bool onFlag);

    void pPlaySound(int code, float distance);
    void pPlayMusic();
    void pStopMusic();
    void pHaltMusic();
    // define por unica vez un objeto estatico
    // y devuelve una instancia
    static SoundManager& getSoundManager();

public:
    enum soundRepertoire : int {
        KNF_S, GLOCK_S, AK47_S, M3_S, AWP_S,
        STEP1, DIE1, HIT1, GO, BOMB_PLANTED,
        BOMB_EXPLODE, CT_WIN, TT_WIN,
        DROP_WEAPON, PICKUP_WEAPON, MENU_SOUND
    };
    SoundManager();

    SoundManager(const SoundManager& other) = delete;
    SoundManager& operator=(const SoundManager& other) = delete;

    SoundManager(SoundManager&& other) = delete;
    SoundManager& operator=(SoundManager&& other) = delete;

    static void start(bool onFlag);
    static void playSound(int soundId, float distanceFromPlayer);
    static void playMusic();
    static void stopMusic();
    static void channelFinishedCallback(int channel);
    ~SoundManager();

    static void haltMusic();

};


#endif
