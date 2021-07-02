#include <iostream>
#include "GamesMonitor.h"
#include "yaml-cpp/yaml.h"
#include "../common/ConfigVariables.h"

GamesMonitor::GamesMonitor(YAML::Node& config) {
    matchesConfig.emplace(ConfigVariables::VIDA_JUGADORES, config["vida_jugadores"].as<int>());
    matchesConfig.emplace(ConfigVariables::DINERO_INICIAL, config["dinero_inicial"].as<int>());
    matchesConfig.emplace(ConfigVariables::MAX_JUGADORES, config["match_max_players"].as<int>());
    matchesConfig.emplace(ConfigVariables::GLOCK_BULLETS, config["glock_max_bullets"].as<int>());
    matchesConfig.emplace(ConfigVariables::AK47_BULLETS, config["ak47_max_bullets"].as<int>());
    matchesConfig.emplace(ConfigVariables::M3_BULLETS, config["m3_max_bullets"].as<int>());
    matchesConfig.emplace(ConfigVariables::AWP_BULLETS, config["awp_max_bullets"].as<int>());
    matchesConfig.emplace(ConfigVariables::MONEY_KILL_ENEMY, config["money_kill_enemy"].as<int>());
    matchesConfig.emplace(ConfigVariables::MONEY_ROUND_WON, config["money_round_won"].as<int>());
    matchesConfig.emplace(ConfigVariables::MONEY_ROUND_LOST, config["money_round_lost"].as<int>());
    matchesConfig.emplace(ConfigVariables::MIN_DMG_KNF, config["min_dmg_knife"].as<int>());
    matchesConfig.emplace(ConfigVariables::MAX_DMG_KNF, config["max_dmg_knife"].as<int>());
    matchesConfig.emplace(ConfigVariables::MIN_DMG_GLK, config["min_dmg_glock"].as<int>());
    matchesConfig.emplace(ConfigVariables::MAX_DMG_GLK, config["max_dmg_glock"].as<int>());
    matchesConfig.emplace(ConfigVariables::MIN_DMG_M3, config["min_dmg_m3"].as<int>());
    matchesConfig.emplace(ConfigVariables::MAX_DMG_M3, config["max_dmg_m3"].as<int>());
    matchesConfig.emplace(ConfigVariables::FR_KNF, config["fire_rate_knife"].as<float>());
    matchesConfig.emplace(ConfigVariables::FR_AWP, config["fire_rate_awp"].as<float>());
    matchesConfig.emplace(ConfigVariables::FR_AK47, config["fire_rate_ak47"].as<float>());
    matchesConfig.emplace(ConfigVariables::FR_GLK, config["fire_rate_glock"].as<float>());
    matchesConfig.emplace(ConfigVariables::FR_M3, config["fire_rate_m3"].as<float>());
}

GamesMonitor::GamesMonitor(GamesMonitor &&other) noexcept
: matches(std::move(other.matches)),
  matchesConfig(std::move(other.matchesConfig)){
}

GamesMonitor &GamesMonitor::operator=(GamesMonitor &&other) noexcept {
    if (this == &other){
        return *this;
    }

    matches = std::move(other.matches);
    matchesConfig = std::move(other.matchesConfig);
    return *this;
}

bool GamesMonitor::createMatch(std::string gameName,
                               const std::function<Socket(void)> &handIn,
                               const std::function<void(int8_t)>& response) {
    std::lock_guard<std::mutex> lock(gamesMonitorLock);
    // si hay un juego con ese nombre, no puedo crear partida
    if (matches.count(gameName)){
        response(-1);
        return false;
    }
    matches.emplace(std::piecewise_construct,
                    std::forward_as_tuple(gameName),
                    std::forward_as_tuple(matchesConfig));
    // si creo el jeugo es id 0
    response(0);
    matches.at(gameName).addUser(handIn());
    return true;
}

bool GamesMonitor::joinMatch(const std::string &gameName,
                             const std::function<Socket(void)> &handIn,
                             const std::function<void(int8_t)> &response) {
    std::lock_guard<std::mutex> lock(gamesMonitorLock);
    // si no hay un juego con ese nombre, no puedo unirme
    if (!matches.count(gameName)){
        response(-1);
        return false;
    }
    response(matches.at(gameName).getCurrentPlayerId());
    matches.at(gameName).addUser(handIn());
    matches.at(gameName).startIfShould();
    return true;
}

GamesMonitor::~GamesMonitor() {
}

void GamesMonitor::stopGames() {
    std::lock_guard<std::mutex> lock(gamesMonitorLock);
    for (auto& m : matches){
        m.second.stop();
    }
}
