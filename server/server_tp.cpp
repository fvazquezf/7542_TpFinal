#include "./server_tp.h"

#include <string>
#include <iostream>

TpServer::TpServer() {
}

void TpServer::operator()(char *port) {
    ThAcceptor listener(port);
    std::string input;
    listener.start();
    while (input != "q") {
        std::cin >> input;
    }
    listener.stop();
}

TpServer::~TpServer() {}
