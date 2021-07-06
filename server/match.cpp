#include <updates/MapUpdate.h>
#include "yaml-cpp/yaml.h"
#include "match.h"
#include "../common/ConfigVariables.h"

Match::Match(const std::map<int, int>& matchConfig, const std::string& mapName)
: matchConfig(matchConfig),
  maxUsers(matchConfig.at(ConfigVariables::MAX_PLAYERS)),
  world(updates, matchConfig){
    try {
        mapInfo = YAML::LoadFile(mapName);
        world.loadMap(mapInfo);
    } catch(const std::exception& e){
        throw e;
    }
}

Match::~Match() {
}

Match::Match(Match &&other) noexcept
: users(std::move(other.users)),
  matchConfig(other.matchConfig),
  maxUsers(other.maxUsers),
  updates(std::move(other.updates)),
  world(std::move(other.world)){
}

Match &Match::operator=(Match &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    maxUsers = other.maxUsers;
    users = std::move(other.users);
    return *this;
}

int8_t Match::addUser(Socket socket) {
    uint8_t id = this->users.size();
    if (maxUsers == id){
        return -1;
    }

    // crea el user dentro del mapa
    // world le pasa la cola no bloqueante de eventos
    // el broadcaster le pasa la cola bloqueante de updates
    users.emplace(std::piecewise_construct,
                  std::forward_as_tuple(id),
                  std::forward_as_tuple(std::move(socket),
                                        world.addPlayer(id),
                                        updates.addPlayer(id),
                                        id));
    std::string map = Dump(mapInfo);
    // enviamos informacion del mapa al cliente que se acaba de unir
    // de esa manera ya puede ir cargando las texturas
    uint8_t userId = id;
    updates.push(userId, std::unique_ptr<Update>(new MapUpdate(std::move(map))));
    id++;
    std::cout << "Users ammount: " << users.size() << "\n";
    return userId;
}

void Match::startIfShould() {
    if (this->users.size() == this->maxUsers){
        for (auto& u : users) {
            u.second.start();
        }
        world.start();
    }
}

void Match::stop() {
    for (auto& u : users) {
        u.second.join();
    }
    world.stop();
    world.join();
}

int8_t Match::getCurrentPlayerId() {
    return this->users.size();
}
