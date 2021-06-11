#include "th_login.h"

ThLogin::ThLogin(Socket &peer, Games &games): peer(std::move(peer)), games(games) {
}

ThLogin::~ThLogin() {
}

void ThLogin::run() {
    Protocol p(this->peer);
    std::string command;
    std::string response;

    while(!this->is_logged_in) {
        command = p.recibirComando();
        if(p.esComandoCrear(command)) {

            std::string game_name = p.recibirNombrePartida();
            std::string nickname = p.recibirNickName();
            
            Game* g  = new Game();
            games.newGame(game_name, g);

            User* user = new User(std::move(peer));
            g->addUser(nickname, user);

            this->is_logged_in = true;
        } else if(p.esComandoUnirse(command)) {

            std::string game_name = p.recibirNombrePartida();
            std::string nickname = p.recibirNickName();

            User* user = new User(std::move(peer));
            games[game_name]->addUser(nickname, user);

            this->is_logged_in = true;
        } else if(p.esComandoListar(command)) {
            break;
        }

    }
}

bool ThLogin::isDead() {
    return this->is_logged_in;
}
void ThLogin::stop() {
    if (this->is_logged_in) {
        peer.close();
    }
}
