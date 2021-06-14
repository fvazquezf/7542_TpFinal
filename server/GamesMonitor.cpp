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

bool GamesMonitor::createMatch(std::string gameName, const std::function<Socket(void)>& handIn) {
    std::lock_guard<std::mutex> lock(gamesMonitorLock);
    // si hay un juego con ese nombre, no puedo crear partida
    if (matches.count(gameName)){
        return false;
    }
    matches.emplace(gameName, Match{});
    matches.at(gameName).addUser(handIn());
    return true;
}

bool GamesMonitor::joinMatch(const std::string& gameName, const std::function<Socket(void)>& handIn) {
    std::lock_guard<std::mutex> lock(gamesMonitorLock);
    // si no hay un juego con ese nombre, no puedo unirme
    if (!matches.count(gameName)){
        return false;
    }
    std::cout << "DEBUG: JOINED MATCH!\n";
    std::cout << gameName << std::endl;
    matches.at(gameName).addUser(handIn());
    return true;
}

GamesMonitor::~GamesMonitor() {
}
