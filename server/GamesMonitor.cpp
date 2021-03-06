#include <iostream>
#include <dirent.h>
#include "GamesMonitor.h"
#include "yaml-cpp/yaml.h"
#include "../common/ConfigVariables.h"

GamesMonitor::GamesMonitor(YAML::Node& config) {
    matchesConfig.emplace(ConfigVariables::PLAYER_HP, config["player_hp"].as<int>());
    matchesConfig.emplace(ConfigVariables::STARTING_MONEY, config["starting_money"].as<int>());
    matchesConfig.emplace(ConfigVariables::MONEY_ROUND_LOST, config["money_round_lost"].as<int>());
    matchesConfig.emplace(ConfigVariables::MONEY_ROUND_WON, config["money_round_won"].as<int>());
    matchesConfig.emplace(ConfigVariables::MAX_PLAYERS, config["match_max_players"].as<int>());
    matchesConfig.emplace(ConfigVariables::PISTOL_AMMO, config["pistol_ammo"].as<int>());
    matchesConfig.emplace(ConfigVariables::PISTOL_RANGE, config["pistol_range"].as<int>());
    matchesConfig.emplace(ConfigVariables::PISTOL_ACCURACY, config["pistol_accuracy"].as<int>());
    matchesConfig.emplace(ConfigVariables::PISTOL_DAMAGE, config["pistol_damage"].as<int>());
    matchesConfig.emplace(ConfigVariables::PISTOL_BOUNTY, config["pistol_bounty"].as<int>());
    matchesConfig.emplace(ConfigVariables::AWP_PRICE, config["awp_price"].as<int>());
    matchesConfig.emplace(ConfigVariables::AWP_AMMO, config["awp_ammo"].as<int>());
    matchesConfig.emplace(ConfigVariables::AWP_RANGE, config["awp_range"].as<int>());
    matchesConfig.emplace(ConfigVariables::AWP_ACCURACY, config["awp_accuracy"].as<int>());
    matchesConfig.emplace(ConfigVariables::AWP_DAMAGE, config["awp_damage"].as<int>());
    matchesConfig.emplace(ConfigVariables::AWP_FIRERATE, config["awp_firerate"].as<int>());
    matchesConfig.emplace(ConfigVariables::AWP_BOUNTY, config["awp_bounty"].as<int>());
    matchesConfig.emplace(ConfigVariables::RIFLE_PRICE, config["rifle_price"].as<int>());
    matchesConfig.emplace(ConfigVariables::RIFLE_AMMO, config["rifle_ammo"].as<int>());
    matchesConfig.emplace(ConfigVariables::RIFLE_RANGE, config["rifle_range"].as<int>());
    matchesConfig.emplace(ConfigVariables::RIFLE_ACCURACY, config["rifle_accuracy"].as<int>());
    matchesConfig.emplace(ConfigVariables::RIFLE_DAMAGE, config["rifle_damage"].as<int>());
    matchesConfig.emplace(ConfigVariables::RIFLE_FIRERATE, config["rifle_firerate"].as<int>());
    matchesConfig.emplace(ConfigVariables::RIFLE_BOUNTY, config["rifle_bounty"].as<int>());
    matchesConfig.emplace(ConfigVariables::SHOTGUN_PRICE, config["shotgun_price"].as<int>());
    matchesConfig.emplace(ConfigVariables::SHOTGUN_AMMO, config["shotgun_ammo"].as<int>());
    matchesConfig.emplace(ConfigVariables::SHOTGUN_RANGE, config["shotgun_range"].as<int>());
    matchesConfig.emplace(ConfigVariables::SHOTGUN_ACCURACY, config["shotgun_accuracy"].as<int>());
    matchesConfig.emplace(ConfigVariables::SHOTGUN_DAMAGE, config["shotgun_damage"].as<int>());     
    matchesConfig.emplace(ConfigVariables::SHOTGUN_BOUNTY, config["shotgun_bounty"].as<int>());     
    matchesConfig.emplace(ConfigVariables::KNIFE_RANGE, config["knife_range"].as<int>());
    matchesConfig.emplace(ConfigVariables::KNIFE_ACCURACY, config["knife_accuracy"].as<int>());
    matchesConfig.emplace(ConfigVariables::KNIFE_DAMAGE, config["knife_damage"].as<int>());
    matchesConfig.emplace(ConfigVariables::KNIFE_FIRERATE, config["knife_firerate"].as<int>());
    matchesConfig.emplace(ConfigVariables::KNIFE_BOUNTY, config["knife_bounty"].as<int>());
    matchesConfig.emplace(ConfigVariables::MONEY_ROUND_WON, config["money_round_won"].as<int>());
    matchesConfig.emplace(ConfigVariables::MONEY_ROUND_LOST, config["money_round_lost"].as<int>());
    matchesConfig.emplace(ConfigVariables::MONEY_ROUND_LOST, config["money_round_lost"].as<int>());
    matchesConfig.emplace(ConfigVariables::BOMB_RANGE, config["bomb_range"].as<int>());
    matchesConfig.emplace(ConfigVariables::BOMB_ACCURACY, config["bomb_accuracy"].as<int>());
    matchesConfig.emplace(ConfigVariables::BOMB_DAMAGE, config["bomb_damage"].as<int>());
    matchesConfig.emplace(ConfigVariables::BOMB_FIRERATE, config["bomb_firerate"].as<int>());
    matchesConfig.emplace(ConfigVariables::BOMB_FUSE, config["bomb_fuse"].as<int>());
    matchesConfig.emplace(ConfigVariables::BOMB_ACTIVATE_TIME, config["bomb_activate_time"].as<int>());
    matchesConfig.emplace(ConfigVariables::BOMB_BOUNTY, config["bomb_bounty"].as<int>());


    // iterando el filesytem para cargar los nombres de los mapas
    // no hay un header de filesystem en c++11 asi que lo hago estilo C
    // codigo obtenido de un ejemplo de la library dirent.h
    // https://stackoverflow.com/a/12240511
    struct dirent *entry;
    DIR *dp = opendir(MAP_PATH_PREFIX);
    if (dp == nullptr) {
        throw std::exception();
    }

    while ((entry = readdir(dp))) {
        std::string mapName(entry->d_name);
        if (mapName == ".." || mapName == ".") {
            continue;
        }
        mapNames.insert(mapName);
    }

    closedir(dp);
}

GamesMonitor::GamesMonitor(GamesMonitor &&other)
: matches(std::move(other.matches)),
  matchesConfig(std::move(other.matchesConfig)) {
}

GamesMonitor &GamesMonitor::operator=(GamesMonitor &&other) {
    if (this == &other) {
        return *this;
    }

    matches = std::move(other.matches);
    matchesConfig = std::move(other.matchesConfig);
    return *this;
}

bool GamesMonitor::createMatch(std::string gameName,
                               const std::string& mapName,
                               const std::function<Socket(void)> &handIn,
                               const std::function<void(int8_t)>& response) {
    std::lock_guard<std::mutex> lock(gamesMonitorLock);
    std::string mapPath = MAP_PATH_PREFIX + mapName + MAP_EXTENSION;
    YAML::Node map;

    // si el mapa no existe
    // me voy
    if (!mapNames.count(mapName + MAP_EXTENSION)) {
        response(-1);
        return false;
    }

    // si hay un juego con ese nombre, no puedo crear partida
    if (matches.count(gameName)) {
        response(-1);
        return false;
    }

    // si el nombre del mapa es invalido, matches tira runtimeException
    try {
        matches.emplace(std::piecewise_construct,
                        std::forward_as_tuple(gameName),
                        std::forward_as_tuple(matchesConfig, mapPath));
    } catch(const std::exception& e) {
        response(-1); // agregar al callback un codigo de tipo de error, bad file, game exists etc etc
        return false;
    }

    return matches.at(gameName).tryAddingUserAndStartIfShould(handIn, response);
}

bool GamesMonitor::joinMatch(const std::string &gameName,
                             const std::function<Socket(void)> &handIn,
                             const std::function<void(int8_t)> &response) {
    std::lock_guard<std::mutex> lock(gamesMonitorLock);
    // si no hay un juego con ese nombre, no puedo unirme
    if (!matches.count(gameName)) {
        response(-1);
        return false;
    }

    // si el juego ya comenzo, bye bye
    if (matches.at(gameName).isGameStarted()) {
        response(-1);
        return false;
    }
    // zona peligrosa
    // algun receiver podria estar tratando de empezar la partida cuando nosotros estamos aca
    // hay que checkear si la partida se puede crear no solo aca afuera sino tambien adentro del match
    return matches.at(gameName).tryAddingUserAndStartIfShould(handIn, response);
}

GamesMonitor::~GamesMonitor() {
}

void GamesMonitor::stopGames() {
    std::lock_guard<std::mutex> lock(gamesMonitorLock);
    for (auto& m : matches) {
        m.second.stop();
    }
}

// devuelvo por movimiento
// pq si devuelvo por ref
// puede que otro login cree un game
// modifique a la variable referenciada
// y nos arruine el string
std::string GamesMonitor::listGames() {
    std::lock_guard<std::mutex> lock(gamesMonitorLock);
    std::string games;
    // simil muy simil tp3
    auto match = matches.begin();
    while (match != matches.end()) {
        games += (*match).first + "\n";
        ++match;
    }
    return games;
}

std::string GamesMonitor::listMaps() {
    std::lock_guard<std::mutex> lock(gamesMonitorLock);
    std::string maps;
    auto mapIt = mapNames.begin();
    while (mapIt != mapNames.end()) {
        auto mapName = mapIt->substr(0, mapIt->size() - 4); // resto el tama??o de la extension para no enviarla
        maps += (mapName + "\n");
        ++mapIt;
    }
    return maps;
}
