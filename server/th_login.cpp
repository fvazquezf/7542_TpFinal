#include "th_login.h"

ThLogin::ThLogin(Socket &peer, Games &games): games(games),
        peer(std::move(peer)), is_logged_in(false) {
}

ThLogin::~ThLogin() {
}

void ThLogin::run() {
    Protocol p(this->peer);
    std::string command;
    std::string response;

    while(!this->is_logged_in) {
        command = p.recibirComando();
        std::string nickname("");
        if(p.esComandoCrear(command)) {

            std::string game_name = p.recibirNombrePartida();
            p.enviarRespuesta("Partdia creada.\n");

            Match* m  = new Match();
            games.newGame(game_name, m);

        } else if(p.esComandoNickname(command)) {

            std::string nickname = p.recibirNickName();
            p.enviarRespuesta("Nickname es " + nickname + ".\n");

        } else if(p.esComandoUnirse(command)) {

            std::string game_name = p.recibirNombrePartida();
            p.enviarRespuesta("Nombre partida es " + game_name + ".\n");

            User* user = new User(peer);
            this->is_logged_in = true;
            games[game_name]->addUser(nickname, user);
            break;
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
