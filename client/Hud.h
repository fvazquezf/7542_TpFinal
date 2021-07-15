#ifndef HUD_H
#define HUD_H

// pixeles
#include <vector>
#include "sdlwrap/SdlWindow.h"
#include "sdlwrap/SdlTexture.h"
#include "SoundManager.h"
#include <yaml-cpp/yaml.h>

#define HUD_SYMBOLS 13
#define HUD_SYMBOL_W 832
#define HUD_SYMBOL_H 64
#define HUD_NUMS 11
#define HUD_NUM_W 528 // sacado con gimp -> hay 12 simbolos, pero 1 de ellos no tiene el mismo tamaño al resto
#define HUD_NUM_H 66

#define CT_ROUND_W 219
#define CT_ROUND_H 167
#define TT_ROUND_W 233
#define TT_ROUND_H 186
#define TT_W 1139
#define TT_H 161
#define CT_W 1501
#define CT_H 147
#define BAR_W 195
#define BAR_H 181

class Hud {
private:
    SdlTexture symbols;
    SdlTexture numbers;
    SdlTexture ctWin;
    SdlTexture ttWin;
    SdlTexture ctRoundsTex;
    SdlTexture ttRoundsTex;
    SdlTexture bar;
    std::vector<Area> numberSelector;
    uint8_t health;
    uint8_t currentClockTick;
    uint16_t money;
    uint8_t clip;
    uint8_t ttRounds;
    uint8_t ctRounds;
    bool winnerTime;
    bool ctWon;
    int w;
    int h;
    void showClock();
    void showLife();
    void showMoney();
    void showClip();
    void showRounds();
    void setNumberColors(Color colors);
    Area areaFromIdxPosition(uint8_t idx) const; // los bmp son horizontales, solo me muevo en "x"
    void loadNumberVector(int number);
public:
    explicit Hud(SdlWindow& window, YAML::Node& config);

    void show();
    void updateHealth(uint8_t healthPoints);
    void updateTime(uint8_t clockTick);
    void updateMoney(uint16_t money);
    void updateClip(uint8_t newClip);
    void updateWinner(bool ctIsWinner);

    void resetHud();

    ~Hud();

    void showWinner();
};


#endif
