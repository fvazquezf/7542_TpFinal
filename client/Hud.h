#ifndef HUD_H
#define HUD_H

// pixeles
#include <vector>
#include "sdlwrap/SdlWindow.h"
#include "sdlwrap/SdlTexture.h"

#define HUD_SYMBOLS 13
#define HUD_SYMBOL_W 832
#define HUD_SYMBOL_H 64
#define HUD_SYMBOL_PATH "../sprites/gfx/hud_symbols.png"
#define HUD_NUMS 11
#define HUD_NUM_W 528 // sacado con gimp -> hay 12 simbolos, pero 1 de ellos no tiene el mismo tamaño al resto
#define HUD_NUM_H 66
#define HUD_NUM_PATH "../sprites/gfx/hud_nums.bmp"
// cuantos ticks para el reloj? 130 -> 2 minutos 10 segundos
#define TICKS 130

class Hud {
private:
    SdlTexture symbols;
    SdlTexture numbers;
    std::vector<std::tuple<Area, Area, Area>> clock;
    std::vector<std::tuple<Area, Area, Area>> life;
    Color numberColors;
    uint8_t health;
    uint8_t currentClockTick;
    int w;
    int h;
    void showClock();
    void showLife();
    void setNumberColors(Color colors);
public:
    explicit Hud(SdlWindow& window);

    void show();
    void updateHealth(uint8_t healthPoints);
    void updateTime(uint8_t clockTick);

    ~Hud();
};


#endif
