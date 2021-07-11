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

class Hud {
private:
    SdlTexture symbols;
    SdlTexture numbers;
    std::vector<Area> numberSelector;
    uint8_t health;
    uint8_t currentClockTick;
    uint16_t money;
    uint8_t clip;
    int w;
    int h;
    void showClock();
    void showLife();
    void showMoney();
    void showClip();
    void setNumberColors(Color colors);
    Area areaFromIdxPosition(uint8_t idx) const; // los bmp son horizontales, solo me muevo en "x"
    void loadNumberVector(int number);
public:
    explicit Hud(SdlWindow& window);

    void show();
    void updateHealth(uint8_t healthPoints);
    void updateTime(uint8_t clockTick);
    void updateMoney(uint16_t money);
    void updateClip(uint8_t newClip);

    ~Hud();

};


#endif
