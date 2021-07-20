#include <common/Protocol.h>
#include <memory>
#include <client/commands/Command.h>
#include <client/commands/JoinGame.h>
#include <client/commands/CreateGame.h>
#include "LogInInfo.h"

LogInInfo::LogInInfo() {}

LogInInfo::~LogInInfo() {}

void LogInInfo::send(std::vector<unsigned char> msg) {
    this->socket.send(reinterpret_cast<const char *>(msg.data()), msg.size());
}

std::vector<unsigned char> LogInInfo::receive(size_t size) {
    std::vector<unsigned char> msg(size);
    this->socket.recv(reinterpret_cast<char *>(msg.data()), size);
    return msg;
}

std::vector<std::string> LogInInfo::receiveGameInformation() {
    Protocol prot;
    char comm;
    this->socket.recv(&comm, 1);
    std::function<std::vector<unsigned char>(size_t)> receiver =
            std::bind(&LogInInfo::receive, this, std::placeholders::_1);
    auto listSerialized = prot.handleStringMsg(receiver);
    auto gameListInformation = prot.deserializeLoginListMessage(listSerialized);
    return gameListInformation;
}

// envia informacion de join game al servidor y finaliza
void LogInInfo::sendJoinGameInfo(std::string selectedGame) {
    std::function<void(std::vector<unsigned char>)> sender =
            std::bind(&LogInInfo::send, this, std::placeholders::_1);
    Protocol prot;
    std::unique_ptr<Command> join = std::unique_ptr<Command>(new JoinGame(std::move(selectedGame)));
    join->serialize(sender, prot);
}

// envia informacion de create game y finaliza
void LogInInfo::sendCreateGameInfo(std::string gameName, std::string mapName) {
    std::function<void(std::vector<unsigned char>)> sender =
            std::bind(&LogInInfo::send, this, std::placeholders::_1);
    Protocol prot;
    std::unique_ptr<Command> create = std::unique_ptr<Command>(new CreateGame(std::move(gameName), std::move(mapName)));
    create->serialize(sender, prot);
}
