#include <vector>
#include "Protocol.h"
#include <arpa/inet.h>

Protocol::Protocol() {
}

void Protocol::createGame(const std::string& gameName,
                          std::function<void(std::vector<unsigned char>)>&callback) const {
    std::vector<unsigned char> msg;
    msg.push_back(CREATE);
    serializeGameName(msg, gameName);
    callback(std::move(msg));
}

void Protocol::joinGame(const std::string &gameName,
                        std::function<void(std::vector<unsigned char>)>&callback) const {
    std::vector<unsigned char> msg;
    msg.push_back(JOIN);
    serializeGameName(msg, gameName);
    callback(std::move(msg));
}

void Protocol::listGames(std::function<void(std::vector<unsigned char>)>&callback) const {
    std::vector<unsigned char> msg;
    msg.push_back(LIST);
    callback(std::move(msg));
}

Protocol::~Protocol() {
}

// client side
void Protocol::serializeGameName(std::vector<unsigned char> &msg, const std::string& gameName) const {
    uint16_t gameSize = gameName.size();
    gameSize = htons(gameSize);
    msg.push_back((gameSize >> 8) & 0xff);
    msg.push_back(gameSize & 0xff);
    std::copy(gameName.begin(), gameName.end(), std::back_inserter(msg));
}

uint16_t Protocol::deserializeGameNameSize(std::vector<unsigned char> &msg) const {
    return ntohs((msg.at(1) << 8) | msg.at(2));
}

void Protocol::move(uint8_t dir, bool isDone,
                    std::function<void(std::vector<unsigned char>)>& callback) const {
    std::vector<unsigned char> msg;
    msg.push_back(isDone ? STOP_MOVE : MOVE);
    msg.push_back(dir);
    callback(std::move(msg));
}
