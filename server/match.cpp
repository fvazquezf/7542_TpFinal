#include "match.h"

Match::Match()
: maxUsers(0),
  world(updates)
{
}

Match::Match(int playerAmount)
: world(updates)
{
    maxUsers = playerAmount;
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
  users(std::move(other.users))
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

void Match::addUser(Socket socket) {
    uint8_t id = this->users.size();
    if (maxUsers == id){
        return;
    }


    // crea el user dentro del mapa
    users.emplace(std::piecewise_construct,
                  std::forward_as_tuple(id),
           std::forward_as_tuple(std::move(socket),
                                        updates.addPlayer(id),
                                        world.addPlayer(id),
                                        id));
    id++;
    std::cout << "Users ammount: " << users.size() << "\n";
}

void Match::startIfShould() {
    if (this->users.size() == this->maxUsers){
        for (auto& u : users) {

            u.second.start();
        }
    }
}

void Match::stop() {
    for (auto& u : users) {
        u.second.join();
    }
}
