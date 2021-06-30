#include "match.h"

Match::Match()
: maxUsers(0),
  updates(),
  world(updates)
{
}

Match::Match(int playerAmount)
: maxUsers(playerAmount),
  world(updates)
{
}

void Match::removeUser() {
    //this->users.erase(nickname);
}

void Match::removeUsers() {
    /*for(auto user : this->users){
        user.second->stop();
		delete user.second;
	}*/
}

Match::~Match() {
}

Match::Match(Match &&other) noexcept
: maxUsers(other.maxUsers),
  users(std::move(other.users)),
  updates(std::move(other.updates)),
  world(std::move(other.world))
  //users(std::move(other.users)),
//   world(std::move(other.world))
  //updates(std::move(other.updates))
{
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
    uint8_t userId = id;
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
