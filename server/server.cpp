#include "./server.h"
#include "GamesMonitor.h"

#include <string>
#include <iostream>

Server::Server() {
}

void Server::operator()(char *port) {
    GamesMonitor games;
    ThAcceptor acceptor(port, games);
    acceptor.start();
    std::string input;
    while (input != "q") {
        std::cin >> input;
    }
    acceptor.stop();
    games.stopGames();
}

Server::~Server() {}
