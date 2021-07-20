#include "anim/Animation.h"
#include "commands/Command.h"

// QT:
#include "./qt/LogInWindow.h"
#include <QApplication>
#include <iostream>
#include "Client.h"
#include "MapView.h"
#define CLIENT_CONFIG "/var/cs2d/config/client_config.yaml"

int main(int argc, const char *argv[]) {
    if (argc != 1) {
        std::cout << "Uso: cs2d\n";
        return -1;
    }

    YAML::Node clientConfig;

    try {
        clientConfig = YAML::LoadFile(CLIENT_CONFIG);
    } catch(const std::exception& e) {
        std::cout << e.what();
        return -1;
    }
    QApplication a(argc, nullptr);
    LogInInfo info;
    LogInWindow w(nullptr, 640, 400, info);

    try {
        w.show();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
    /*
    Info es una clase con 4 atributos publicos de tipo std::string
    - port
    - ip
    - username
    - map (nombre del mapa sin .yml)
    */
    try {
        a.exec();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }

    if (info.failed) {
        std::cout << "Failed login in\n";
        return -1;
    }

    try {
        Client clientHandler(info, clientConfig);
        clientHandler.launch();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
    return 0;
}
