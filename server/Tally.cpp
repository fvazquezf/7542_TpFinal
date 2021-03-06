#include "Tally.h"
#include <algorithm>
#include <utility>

Tally::Tally(std::shared_ptr<Bomb> bomb): 
 bomb (std::move(bomb)) {
    time = 130;
    ticks = 59;
    score = {0, 0};
}

void Tally::placeInTeam(int id, bool team) {
    if (team) {
        ctSide[id] = {0, 0};
    } else {
        ttSide[id] = {0, 0};
    }
}

void Tally::swapTeams() {
    ctSide.swap(ttSide);
}

void Tally::playerKilledOther(int id, int other) {
    deaths.insert(other);
    // si el player esta en ctSide, el ct mato a un tt
    if (ctSide.find(id) != ctSide.end()) {
        // el ct gana 1 kill
        ctSide[id].first++;
        // el tt gana 1 muerte
        ttSide[other].second++;
    } else {
        // si id no esta en ctSide, esta en el ttSide, entonces el tt mato al ct
        ttSide[id].first++;
        // le sumo muerte al ct y kill al tt
        ctSide[other].second++;
    }
}

void Tally::addDeath(int id) {
    if (ctSide.find(id) != ctSide.end()) {
        ctSide[id].second++;
    } else {
        ttSide[id].second++;
    }
}


void Tally::startBombTiming() {
    time = bomb->getFuse();
}

bool Tally::tickTime() {
    ticks++;
    if ((ticks % 60) == 0) {
        time--;
        return true;
    }
    return false;
}

int Tally::getTime() const {
    return time;
}

void Tally::resetRound() {
    deaths.clear();
    time = 130;
}

int Tally::getTerrorist() {
    auto it = ttSide.begin();
    std::advance(it, rand() % ttSide.size());
    return it->first;
}

// checkea si termino la ronda
// x casos:
// 1 - murieron todos los cts -> ganan tts
// 2 - murieron todos los tts (y no plantaron) -> ganan cts
// 3 - se termino el tiempo (ganan los cts pq es de plantar la bomba)
// 4 - exploto la bomba -> ganan tts
// 5 - defusearon la bomba -> ganan cts

int Tally::isRoundOver() {
    // cambiar bool por int diciendo quien gano
    if (ctWon()) return 1;
    if (ttWon()) return -1;
    return 0;
}

bool Tally::ctWon() {
    int state = bomb->getState();
    if (state == DEFUSED) return true;
    if (state == ACTIVE || state == EXPLODED) return false;
    if (state == INACTIVE && time == 0) return true;
    
    bool allTtDead = true;
    for (auto it = ttSide.begin(); it != ttSide.end() && allTtDead; it++) {
        allTtDead = (deaths.find(it->first) != deaths.end());
    }
    return allTtDead;
}

bool Tally::ttWon() {
    if (bomb->getState() == EXPLODED) return true;
    bool allCtDead = true;
    for (auto it = ctSide.begin(); it != ctSide.end() && allCtDead; it++) {
        allCtDead = (deaths.find(it->first) != deaths.end());
    }
    return allCtDead;
} 

std::vector<std::tuple<uint8_t, uint8_t, uint8_t, uint16_t, bool>> Tally::getScores(const std::map<int, PlayerModel>& playerModels) {
    std::vector<std::tuple<uint8_t, uint8_t, uint8_t, uint16_t, bool>> scores;
    for (auto player: ctSide) {
        int id = player.first;
        int kills = player.second.first;
        int deaths = player.second.second;
        int money = playerModels.at(id).getTotalMoney();
        bool side = true; // es Ct
        scores.emplace_back(id, kills, deaths, money, side);
    }  
    for (auto player: ttSide) {
        int id = player.first;
        int kills = player.second.first;
        int deaths = player.second.second;
        int money = playerModels.at(id).getTotalMoney();
        bool side = false; // es Tt
        scores.emplace_back(id, kills, deaths, money, side);
    }
    std::sort(scores.begin(), scores.end(), [&](const std::tuple<uint8_t, uint8_t, uint8_t, uint16_t, bool>& player1, 
                                                const std::tuple<uint8_t, uint8_t, uint8_t, uint16_t, bool>& player2){
        return (std::get<1>(player1) > std::get<1>(player2));
    });
    return scores;
}
