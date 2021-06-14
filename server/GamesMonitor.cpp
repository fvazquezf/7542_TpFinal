#include <iostream>
#include "GamesMonitor.h"

GamesMonitor::GamesMonitor() {
}

GamesMonitor::GamesMonitor(GamesMonitor &&other) noexcept
: matches(std::move(other.matches)){
}

GamesMonitor &GamesMonitor::operator=(GamesMonitor &&other) noexcept {
    if (this == &other){
        return *this;
    }

    matches = std::move(other.matches);
    return *this;
}

bool GamesMonitor::createMatch(std::string gameName) {
    std::lock_guard<std::mutex> lock(gamesMonitorLock);

    // si hay un juego con ese nombre, no puedo crear partida
    if (matches.count(gameName)){
        return false;
    }
    std::cout << "DEBUG: CREATED MATCH!\n";
    std::cout << gameName << std::endl;
    Match match;
    matches.insert({std::move(gameName), match});
    return true;
}

bool GamesMonitor::joinMatch(std::string gameName) {
    std::lock_guard<std::mutex> lock(gamesMonitorLock);
    // si no hay un juego con ese nombre, no puedo unirme
    if (!matches.count(gameName)){
        return false;
    }
    std::cout << "DEBUG: JOINED MATCH!\n";
    std::cout << gameName << std::endl;
    return true;
}

GamesMonitor::~GamesMonitor() {
}
