#include "match.h"

Match::Match()
: maxUsers(0){
}

Match::Match(int playerAmount){
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
  users(std::move(other.users)){
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
    //User user(std::move(socket));
    int id = this->users.size();
    id++;
    users.emplace(id, std::move(socket), this->world.addPlayer(std::to_string(id)));
    // this->world.addPlayer(std::to_string(id));
    std::cout << "Users ammount: " << users.size() << "\n";
}

void Match::startIfShould() {
    if (maxUsers == 2){
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
