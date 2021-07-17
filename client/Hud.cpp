#include <iostream>
#include <sstream>
#include "Hud.h"

Hud::Hud(SdlWindow &window, YAML::Node& config)
: symbols(config["hud_symbols"].as<std::string>(), window, {0, 0, 0}),
  numbers(config["hud_numbers"].as<std::string>(), window, {0, 0, 0}),
  ctWin(config["ct_win"].as<std::string>(), window),
  ttWin(config["tt_win"].as<std::string>(), window),
  ctRoundsTex(config["ct_rounds"].as<std::string>(), window),
  ttRoundsTex(config["tt_rounds"].as<std::string>(), window),
  bar(config["bar"].as<std::string>(), window, {0xff, 0xff, 0xff}),
  health(0),
  currentClockTick(0),
  clip(0),
  ttRounds(0),
  ctRounds(0),
  winnerTime(false),
  ctWon(false),
  w(window.getWidth()),
  h(window.getHeight()){
}

Hud::~Hud() {
}

void Hud::show() {
    showMoney();
    showClock();
    showLife();
    showClip();
    showRounds();
    if (winnerTime){
        showWinner();
    }
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

void Hud::showClip() {
    loadNumberVector(clip);
    setNumberColors({0, 0xff, 0});
    for (size_t i = 0; i < numberSelector.size(); ++i) {
        Area dst(w - (numberSelector.size() - i) * 36,
                 h - HUD_NUM_H + 20,
                 HUD_NUM_W / HUD_NUMS * 2 / 3,
                 HUD_NUM_H * 2 / 3);
        numbers.render(numberSelector.at(i), dst, SDL_FLIP_NONE);
    }
    numberSelector.clear();
}

void Hud::updateClip(uint8_t newClip) {
    clip = newClip;
}

void Hud::showWinner() {
    if (ctWon) {
        Area srcCt(0, 0, CT_W, CT_H);
        Area dstCt(w/2 - CT_W / 8, h/2, CT_W / 4, CT_H / 4);
        ctWin.render(srcCt, dstCt, SDL_FLIP_NONE);
    } else {
        Area srcTT(0, 0, TT_W, TT_H);
        Area dstTT(w/2 - TT_W / 8, h/2, TT_W / 4, TT_H / 4);
        ttWin.render(srcTT, dstTT, SDL_FLIP_NONE);
    }
}

void Hud::updateWinner(bool ctIsWinner) {
    winnerTime = true;
    ctWon = ctIsWinner;
    if (ctWon){
        ++ctRounds;
        SoundManager::playSound(SoundManager::soundRepertoire::CT_WIN, 0);
    } else {
        ++ttRounds;
        SoundManager::playSound(SoundManager::soundRepertoire::TT_WIN, 0);
    }
}

void Hud::resetHud() {
    winnerTime = false;
    ctWon = false;
}

void Hud::showRounds() {
    loadNumberVector(ttRounds);
    Area srcTT(0, 0, TT_ROUND_W, TT_ROUND_H);
    Area dstTT(w/3, 0, TT_ROUND_W/4, TT_ROUND_H/4);
    Area roundsTT(w/3 + TT_ROUND_W/4 + HUD_NUM_W / HUD_NUMS * 1/3, 0, HUD_NUM_W / HUD_NUMS * 2/3,
             HUD_NUM_H * 2/3);
    ttRoundsTex.render(srcTT, dstTT, SDL_FLIP_NONE);
    numbers.render(numberSelector.at(0), roundsTT, SDL_FLIP_NONE);
    Area srcBar(0, 0, BAR_W, BAR_H);
    Area dstBar(w/2, 0, BAR_W/3, BAR_H/3);
    bar.render(srcBar, dstBar, SDL_FLIP_NONE);
    numberSelector.clear();

    loadNumberVector(ctRounds);
    Area srcCT(0, 0, TT_ROUND_W, TT_ROUND_H);
    Area dstCT(w/2 + BAR_W/3, 0, TT_ROUND_W/4, TT_ROUND_H/4);
    Area roundsCT(w/2 + BAR_W/3 + TT_ROUND_W/4 + HUD_NUM_W / HUD_NUMS * 1/3, 0, HUD_NUM_W / HUD_NUMS * 2/3,
                  HUD_NUM_H * 2/3);
    ctRoundsTex.render(srcCT, dstCT, SDL_FLIP_NONE);
    numbers.render(numberSelector.at(0), roundsCT, SDL_FLIP_NONE);
    numberSelector.clear();
}

void Hud::swapTeamScores() {
    std::swap(ttRounds, ctRounds);
}

