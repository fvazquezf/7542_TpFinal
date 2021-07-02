#include "./server.h"
#include "GamesMonitor.h"
#include "yaml-cpp/yaml.h"

#include <string>
#include <iostream>

Server::Server() {
}

void Server::operator()(char *port, char* configPath) {
    YAML::Node config = YAML::LoadFile(std::string(configPath));
    GamesMonitor games(config);
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
