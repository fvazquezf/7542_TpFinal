#include <vector>
#include <functional>
#include "th_login.h"

ThLogin::ThLogin(Socket &peer, Games &games): games(games),
        peer(std::move(peer)), is_logged_in(false) {
}

ThLogin::~ThLogin() {
}

void ThLogin::run() {
    //Protocol p(this->peer);
    Protocol prot;
    //std::string command;
    //std::string response;

    std::function<std::vector<unsigned char>(size_t)>
            receiverCallback = std::bind(&ThLogin::receiveMsgs, this, std::placeholders::_1);
    while(!this->is_logged_in) {
        char comm;
        size_t received = peer.recv(&comm, 1);
        if (received == 0){
            break;
        }
        std::vector<unsigned char> msgRecv = prot.dispatchReceived(comm, receiverCallback);
        for (auto &it : msgRecv){
            printf("%02x ", it);
        }
        puts("");
        /*command = p.recibirComando();
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
        }
    }*/
    }
    this->is_logged_in = true;
}

bool ThLogin::isDead() {
    return this->is_logged_in;
}
void ThLogin::stop() {
    if (this->is_logged_in) {
        //peer.close();
    }
}

std::vector<unsigned char> ThLogin::receiveMsgs(size_t msgSize) {
    std::vector<unsigned char> msg(msgSize);
    peer.recv(reinterpret_cast<char *>(msg.data()), msgSize);
    return msg;
}
