#include "match.h"

Match::Match() {
}

void Match::addUser(const std::string &nickname, User* user) {
    this->users[nickname] = user;
    this->users[nickname]->start();
    std::cout <<"llegamos aca antes del start\n";
}

void Match::removeUser(const std::string &nickname) {
    this->users.erase(nickname);
}

void Match::removeUsers() {
    for(auto user : this->users){
        user.second->stop();
		delete user.second;
	}
}

Match::~Match() {
}
