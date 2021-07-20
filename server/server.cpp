#include "./server.h"
#include "GamesMonitor.h"
#include "yaml-cpp/yaml.h"

#include <string>
#include <iostream>

Server::Server() {
}

void Server::operator()(char *port) {
    YAML::Node config;
    try {
        config = YAML::LoadFile(SERV_CONFIG_PATH);
    } catch (const std::exception& e) {
        throw;
    }
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
