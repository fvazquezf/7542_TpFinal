#include <vector>
#include <functional>
#include "th_login.h"

ThLogin::ThLogin(Socket peer, GamesMonitor &games)
: games(games),
  peer(std::move(peer)),
  is_logged_in(false) {
}

ThLogin::~ThLogin() {
}

void ThLogin::run() {
    Protocol prot;
    std::function<std::vector<unsigned char>(size_t)>
            receiverCallback = std::bind(&ThLogin::receiveMsgs, this, std::placeholders::_1);
    while(!is_logged_in) {
        char comm;
        size_t received = peer.recv(&comm, 1);
        if (received == 0){
            break;
        }
        std::vector<unsigned char> msgRecv = prot.dispatchReceived(comm, receiverCallback);
        is_logged_in = handleLoginMessage(comm, msgRecv);
    }
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

bool ThLogin::handleLoginMessage(uint8_t msgCode, const std::vector<unsigned char> &msg) {
    std::string gameName(msg.begin(), msg.end());
    switch (msgCode) {
        case CREATE:
            return games.createMatch(std::move(gameName));
        case JOIN:
            return games.joinMatch(std::move(gameName));
        default:
            return false;
    }
}
