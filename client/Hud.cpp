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
    showMoney();
    showClock();
    showLife();
}

// Si un día trabajás con un diseñador, meté estas constantes en un archivo de configuración así
// las toca él. Tienen el talento de ponerse intensos con "poné esto dos pixeles más a la izquierda".
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
}

void Hud::updateHealth(uint8_t healthPoints) {
    health = healthPoints;
}

void Hud::updateTime(uint8_t clockTick) {
    currentClockTick = clockTick;
}

void Hud::showLife() {
    loadNumberVector(health);
    Area srcHealth(0, 0, HUD_SYMBOL_W / HUD_SYMBOLS, HUD_SYMBOL_H);
    Area dstHealth(10, h - HUD_SYMBOL_H + 20,
                  HUD_SYMBOL_W / HUD_SYMBOLS, HUD_SYMBOL_H * 2/3);

    if (health >= 70){
        setNumberColors({0, 255, 0});
    } else if (health > 30 && health < 70){
        setNumberColors({255, 255, 0});
    } else {
        setNumberColors({255, 0, 0});
    }

    for (size_t i = 0; i < numberSelector.size(); ++i){
        Area dst(HUD_SYMBOL_W / HUD_SYMBOLS +  i * 48, h - HUD_NUM_H + 20,
                 HUD_NUM_W / HUD_NUMS * 2/3, HUD_NUM_H * 2/3);
        numbers.render(numberSelector.at(i), dst, SDL_FLIP_NONE);
    }
    symbols.render(srcHealth, dstHealth, SDL_FLIP_NONE);
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

void Hud::updateMoney(uint16_t newMoney) {
    money = newMoney;
}

void Hud::showMoney() {
    loadNumberVector(money);
    setNumberColors({0xff, 0xff, 0});
    Area srcMoney(7 * HUD_SYMBOL_W / HUD_SYMBOLS + 1, 0, HUD_SYMBOL_W / HUD_SYMBOLS, HUD_SYMBOL_H);
    Area dstMoney(w - numberSelector.size() * 48, 20, HUD_SYMBOL_W / HUD_SYMBOLS, HUD_SYMBOL_H * 2/3);
    for (size_t i = 0; i < numberSelector.size(); ++i) {
        Area dst(w - (numberSelector.size() - i) * 36, 20, HUD_NUM_W / HUD_NUMS * 2 / 3,
                 HUD_NUM_H * 2 / 3);
        numbers.render(numberSelector.at(i), dst, SDL_FLIP_NONE);
    }
    symbols.render(srcMoney, dstMoney, SDL_FLIP_NONE);
    numberSelector.clear();
}

