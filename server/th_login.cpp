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
    std::function<std::vector<unsigned char>(size_t)>
            receiverCallback = std::bind(&ThLogin::receiveMsgs,
                                         this,
                                         std::placeholders::_1);
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
        peer.close();
    }
}

std::vector<unsigned char> ThLogin::receiveMsgs(size_t msgSize) {
    std::vector<unsigned char> msg(msgSize);
    peer.recv(reinterpret_cast<char *>(msg.data()), msgSize);
    return msg;
}

bool ThLogin::handleLoginMessage(uint8_t msgCode, const std::vector<unsigned char> &msg) {
    std::string gameName(msg.begin(), msg.end());
    std::function<Socket()> socketHander = std::bind(&ThLogin::handOver, this);
    std::function<void(int8_t id)> response = std::bind(&ThLogin::loginResponse,
                                                        this,
                                                        std::placeholders::_1);
    switch (msgCode) {
        case CREATE: {
            std::pair<std::string, std::string> gamePair = prot.deserializeCreateGame(msg);
            return games.createMatch(std::move(gamePair.first), gamePair.second, socketHander, response);
        }
        case JOIN:
            return games.joinMatch(gameName,
                                   socketHander,
                                   response);
        default:
            return false;
    }
}

Socket ThLogin::handOver() {
    return std::move(peer);
}

void ThLogin::loginResponse(int8_t id) {
    std::function<void(std::vector<unsigned char>)> sender =
            std::bind(&ThLogin::sendMsgs, this, std::placeholders::_1);
    if (id < 0){
        prot.loginResponse(LOGIN_BAD, sender);
    } else {
        prot.loginResponse(LOGIN_OK, sender, id);
    }
}

void ThLogin::sendMsgs(std::vector<unsigned char> msg) {
    peer.send(reinterpret_cast<const char *>(msg.data()), msg.size());
}
