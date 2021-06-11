#include "./games.h"

Games::Games() {
}

void Games::newGame(std::string name, Match* m) {
    this->matches[name] = m;
}

Match*& Games::operator[](std::string game_name) {
    return this->matches[game_name];
}

Games::~Games() {
    for(auto match: this->matches){
		delete match.second;
	}
}
