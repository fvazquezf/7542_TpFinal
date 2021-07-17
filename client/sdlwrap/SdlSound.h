#ifndef SDLSOUND_H
#define SDLSOUND_H

#include <SDL2/SDL_mixer.h>
#include <string>
#include "../../common/Exception.h"

class SdlSound {
private:
    Mix_Chunk* effect;
public:
    explicit SdlSound(const std::string& soundPath);

    SdlSound(const SdlSound& other) = delete;
    SdlSound& operator=(const SdlSound& other) = delete;

    SdlSound(SdlSound&& other) ;
    SdlSound& operator=(SdlSound&& other) ;

    // reproduce con cierto volumen
    // en un canal habilitado
    int play();

    ~SdlSound();
};


#endif
