#include <tuple>
#include <iostream>
#include <sstream>
#include "Hud.h"

Hud::Hud(SdlWindow &window)
: symbols(HUD_SYMBOL_PATH, window, Color{0, 0, 0}),
  numbers(HUD_NUM_PATH, window, Color{0, 0, 0}),
  health(23),
  currentClockTick(0),
  w(window.getWidth()),
  h(window.getHeight()){
}

Hud::~Hud() {
}

void Hud::show() {
    showClock();
    showLife();
}

void Hud::showClock() {
    int minutesIdx = std::floor(currentClockTick / 60); // primer numero (minutos)
    int seconds = currentClockTick % 60; // segundo numero (segundos)
    int secondsIdxH = std::floor(seconds / 10);
    int secondsIdxL = seconds % 10;
    loadNumberVector(minutesIdx);
    loadNumberVector(secondsIdxH);
    loadNumberVector(secondsIdxL);
    Area srcClock(2 * HUD_SYMBOL_W / HUD_SYMBOLS, 0, HUD_SYMBOL_W / HUD_SYMBOLS, HUD_SYMBOL_H);
    Area dstClock(w/2 - 2*64, h - HUD_SYMBOL_H + 20, HUD_SYMBOL_W / HUD_SYMBOLS, HUD_SYMBOL_H * 2/3);
    Area srcColon(480,0, HUD_NUM_W / HUD_NUMS * 2/3, HUD_NUM_H* 2/3);
    Area dstColon(w/2 - 15, h - HUD_NUM_H + 15, HUD_NUM_W / HUD_NUMS* 2/3, HUD_NUM_H* 2/3);
    numbers.render(srcColon, dstColon, SDL_FLIP_NONE);
    symbols.render(srcClock, dstClock, SDL_FLIP_NONE);
    for (size_t i = 0; i < numberSelector.size(); ++i){
        Area dst( w/2 - 48 + i * 48, h - HUD_NUM_H + 20, HUD_NUM_W / HUD_NUMS * 2/3, HUD_NUM_H * 2/3);
        numbers.render(numberSelector.at(i), dst, SDL_FLIP_NONE);
    }
    numberSelector.clear();

    /*auto clockTuple = clock.at(currentClockTick);
    if (currentClockTick == TICKS + 1){
        currentClockTick = 0;
    }
    Area srcClock(2 * HUD_SYMBOL_W / HUD_SYMBOLS, 0, HUD_SYMBOL_W / HUD_SYMBOLS, HUD_SYMBOL_H);
    Area dstClock(w/2 - 2*64, h - HUD_SYMBOL_H + 20, HUD_SYMBOL_W / HUD_SYMBOLS, HUD_SYMBOL_H * 2/3);
    Area dst(w/2 -48 + 0, h - HUD_NUM_H + 20, HUD_NUM_W / HUD_NUMS * 2/3, HUD_NUM_H * 2/3);
    Area src1(480,0, HUD_NUM_W / HUD_NUMS * 2/3, HUD_NUM_H* 2/3);
    Area dst1(w/2 -48 + 48, h - HUD_NUM_H + 20, HUD_NUM_W / HUD_NUMS* 2/3, HUD_NUM_H* 2/3);
    Area dst2(w/2 -48 + 65, h - HUD_NUM_H + 20, HUD_NUM_W / HUD_NUMS* 2/3, HUD_NUM_H* 2/3);
    Area dst3(w/2 -48 + 111, h - HUD_NUM_H + 20, HUD_NUM_W / HUD_NUMS* 2/3, HUD_NUM_H* 2/3);
    symbols.render(srcClock, dstClock, SDL_FLIP_NONE);
    setNumberColors({255, 0, 0});
    numbers.render(std::get<0>(clockTuple), dst, SDL_FLIP_NONE);
    numbers.render(src1, dst1, SDL_FLIP_NONE);
    numbers.render(std::get<1>(clockTuple), dst2, SDL_FLIP_NONE);
    numbers.render(std::get<2>(clockTuple), dst3, SDL_FLIP_NONE);*/
}

void Hud::updateHealth(uint8_t healthPoints) {
    health = healthPoints;
}

void Hud::updateTime(uint8_t clockTick) {
    currentClockTick = clockTick;
}

void Hud::showLife() {
    loadNumberVector(health);

    if (health >= 70){
        setNumberColors({0, 255, 0});
    } else if (health > 30 && health < 70){
        setNumberColors({255, 255, 0});
    } else {
        setNumberColors({255, 0, 0});
    }

    for (size_t i = 0; i < numberSelector.size(); ++i){
        Area dst( i * 48, h - HUD_NUM_H + 20, HUD_NUM_W / HUD_NUMS * 2/3, HUD_NUM_H * 2/3);
        numbers.render(numberSelector.at(i), dst, SDL_FLIP_NONE);
    }
    numberSelector.clear();
}

void Hud::setNumberColors(Color colors) {
    numbers.changeColor(colors);
}

Area Hud::areaFromIdxPosition(uint8_t idx) const {
    int offsetWidth = HUD_NUM_W / HUD_NUMS;
    return Area(idx * offsetWidth, 0, offsetWidth, HUD_NUM_H);
}

void Hud::loadNumberVector(int number) {
    std::ostringstream os;
    os << number;
    std::string digits = os.str();
    for (auto& it : digits){
        numberSelector.emplace_back(areaFromIdxPosition(it - '0'));
    }
}
