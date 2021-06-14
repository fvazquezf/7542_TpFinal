#include "match.h"

Match::Match()
: currUserId(0){
}

/*void Match::addUser(const std::string &nickname, User* user) {
    //this->users[nickname] = user;
    //this->users[nickname]->start();
    //std::cout <<"llegamos aca antes del start\n";
}*/

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

void Match::addUser(Socket socket) {
    users.emplace(currUserId++, std::move(socket));
    std::cout << "User added with id: " << (int) currUserId << "\n";
}

Match::Match(Match &&other) noexcept
: currUserId(other.currUserId),
  users(std::move(other.users)){
}

Match &Match::operator=(Match &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    currUserId = other.currUserId;
    users = std::move(other.users);
    return *this;
}
