#include <vector>
#include "Protocol.h"
#include <arpa/inet.h>

Protocol::Protocol() {
}

void Protocol::createGame(const std::string& gameName) {
    std::vector<unsigned char> msg;
    msg.push_back(CREATE);
    serializeGameName(msg, gameName);
    // callback
}

void Protocol::joinGame(const std::string &gameName) {
    std::vector<unsigned char> msg;
    msg.push_back(JOIN);
    serializeGameName(msg, gameName);
    // callback
}

void Protocol::listGames() {
    // callback
}

Protocol::~Protocol() {

}

// client side
void Protocol::serializeGameName(std::vector<unsigned char> &msg, const std::string& gameName) {
    uint16_t gameSize = gameName.size();
    gameSize = htons(gameSize);
    msg.resize(3 + gameSize); // 1 por comando, 2 por largo nombre, gamesize
    msg.push_back((gameSize >> 8) & 0xff);
    msg.push_back(gameSize & 0xff);
    std::copy(gameName.begin(), gameName.end(), std::back_inserter(msg));
}

uint16_t Protocol::deserializeGameNameSize(std::vector<unsigned char> &msg) {
    return ntohs((msg.at(1) << 8) | msg.at(2));
}

void Protocol::move(Protocol::Direction dir, bool isDone) {
    std::vector<unsigned char> msg(2);
    msg.push_back(isDone ? STOP_MOVE : MOVE);
    msg.push_back(dir);
}
