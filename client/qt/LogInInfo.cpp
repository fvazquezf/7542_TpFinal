#include <common/Protocol.h>
#include "LogInInfo.h"

LogInInfo::LogInInfo(){}

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
