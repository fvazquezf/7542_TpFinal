#include <tuple>
#include <iostream>
#include "Hud.h"

Hud::Hud(SdlWindow &window)
: symbols(HUD_SYMBOL_PATH, window, Color{0, 0, 0}),
  numbers(HUD_NUM_PATH, window, Color{0, 0, 0}),
  currentClockTick(0),
  w(window.getWidth()),
  h(window.getHeight()){
    // RELOJ, aprovechamos que los numeros estan ordenados bellamente
    // conversiones super basicas que no cualquiera sabe (?
    // estos los usamos para indexar
    // en caso de que el numero sea de mas de una cifra
    // le hacemos % 10
    int wNumber = HUD_NUM_W / (HUD_NUMS);
    int hNumber = HUD_NUM_H;
    for (int i = TICKS + 1; i >= 0; --i){
        int minutesIdx = std::floor(i / 60); // primer numero (minutos)
        int seconds = i % 60; // segundo numero (segundos)
        int secondsIdxH = std::floor(seconds / 10);
        int secondsIdxL = seconds % 10;
        auto tuple = std::make_tuple(Area(minutesIdx * wNumber, 0, wNumber, hNumber),
                Area(secondsIdxH * wNumber, 0, wNumber, hNumber),
                Area(secondsIdxL * wNumber, 0, wNumber, hNumber));
        clock.emplace_back(std::move(tuple));
    }
}

Hud::~Hud() {
}

void Hud::show() {
    showClock();
}

void Hud::showClock() {
    ++currentClockTick;
    auto clockTuple = clock.at(currentClockTick);
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
    numbers.render(std::get<0>(clockTuple), dst, SDL_FLIP_NONE);
    numbers.render(src1, dst1, SDL_FLIP_NONE);
    numbers.render(std::get<1>(clockTuple), dst2, SDL_FLIP_NONE);
    numbers.render(std::get<2>(clockTuple), dst3, SDL_FLIP_NONE);
}