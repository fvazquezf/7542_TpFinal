#include <updates/MapUpdate.h>
#include "yaml-cpp/yaml.h"
#include "match.h"
#include "../common/ConfigVariables.h"

Match::Match(const std::map<int, int>& matchConfig, const std::string& mapName)
: matchConfig(matchConfig),
  maxUsers(matchConfig.at(ConfigVariables::MAX_PLAYERS)),
  world(updates, matchConfig),
  gameStarted(false){
    try {
        mapInfo = YAML::LoadFile(mapName);
        world.loadMap(mapInfo);
    } catch(const std::exception& e){
        throw;
    }
    startEarlyCallback = std::bind(&Match::start, this);
}

Match::~Match() {
}

Match::Match(Match &&other) noexcept
: users(std::move(other.users)),
  matchConfig(other.matchConfig),
  maxUsers(other.maxUsers),
  updates(std::move(other.updates)),
  world(std::move(other.world)),
  gameStarted(false){
    startEarlyCallback = std::bind(&Match::start, this);
}

Match &Match::operator=(Match &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    users = std::move(other.users);
    maxUsers = other.maxUsers;
    updates = std::move(other.updates);
    world = std::move(other.world);
    gameStarted = other.gameStarted.operator bool();
    startEarlyCallback = std::bind(&Match::start, this);
    return *this;
}

void Match::stop() {
    std::lock_guard<std::mutex> lock(matchMutex);
    updates.closeAllQueues();
    for (auto& u : users) {
        u.second.stop();
        u.second.join();
    }
    if (!world.isDead()){
        world.stop();
        world.join();
    }
}

// earlyStartCallback
void Match::start() {
    std::lock_guard<std::mutex> lock(matchMutex);
    // si justo se unio el ultimo jugador antes del earlyStart
    // y logro empezar la partida
    // entonces no tengo que hacer nada
    // en el caso de sacar esta condicion podria darse ese caso
    // y romper el servidor por tratar de iniciar al world 2 veces
    if (gameStarted){
        return;
    }
    world.start();
    gameStarted = true;
}

bool Match::isGameStarted() {
    return gameStarted;
}

// ejecutado por el hilo login
bool Match::tryAddingUserAndStartIfShould(const std::function<Socket(void)> &socketHandIn,
                                          const std::function<void(int8_t)> &loginResponse) {
    std::lock_guard<std::mutex> lock(matchMutex);
    if (gameStarted){
        loginResponse(-1);
        return false; // si el juego comenzo, chau
    }
    uint8_t id = this->users.size();

    loginResponse(id);

    auto userPair = users.emplace(std::piecewise_construct,
                                  std::forward_as_tuple(id),
                                  std::forward_as_tuple(std::move(socketHandIn()),
                                                        world.addPlayer(id),
                                                        updates.addPlayer(id),
                                                        id,
                                                        startEarlyCallback));
    // empezamos al receiver y al sender
    // recordar que el callback puede iniciar la partida antes de que se llene
    userPair.first->second.start();

    // enviamos informacion del mapa al cliente que se acaba de unir
    // de esa manera ya puede ir cargando las texturas
    std::string map = Dump(mapInfo);
    updates.push(id, std::unique_ptr<Update>(new MapUpdate(std::move(map))));

    if (this->users.size() == this->maxUsers) {
        world.start();
        gameStarted = true;
    }
    return true;
}
