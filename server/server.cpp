#include "./server.h"
#include "GamesMonitor.h"

#include <string>
#include <iostream>

Server::Server() {
}

void Server::operator()(char *port) {
    //Games games;
    GamesMonitor games;
    ThAcceptor acceptor(port, games);
    //ThLoop loop(games);
    acceptor.start();
    //loop.start();
    std::string input;
    while (input != "q") {
        std::cin >> input;
    }
    acceptor.stop();
    games.stopGames();
    //loop.stop();
}

Server::~Server() {}
