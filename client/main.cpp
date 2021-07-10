#include <unistd.h>
#include <chrono>
#include <sstream>
#include "anim/Animation.h"
#include "SdlLoop.h"
#include "commands/Command.h"
#include "Sender.h"
#include "WorldView.h"
#include "sdlwrap/SdlWindow.h"
#include "Receiver.h"
#include "commands/CreateGame.h"
#include "commands/JoinGame.h"

// QT:
#include "./qt/LogInWindow.h"
#include "./qt/IntroWindow.h"
#include "./qt/LogInInfo.h"
#include <QApplication>
#include <iostream>
#include "sdlwrap/SdlSound.h"
#include "commands/ListGame.h"
#include "Client.h"
#include "MapView.h"

int main(int argc, const char *argv[]){
    //Editor in QT
    if (argc != 2){
        std::cout << "Cantidad invalida de argumentos, "
                     "ingrese por favor un archivo de configuracion valido\n";
        return -1;
    }

    YAML::Node clientConfig;

    try {
        clientConfig = YAML::LoadFile(argv[1]);
    } catch(const std::exception& e){
        std::cout << e.what();
        return -1;
    }

    QApplication a(argc, nullptr);
    LogInInfo info;
    LogInWindow w(nullptr, 640, 400, info);
    w.show();
    /*
    Info es una clase con 4 atributos publicos de tipo std::string
    - port
    - ip
    - username
    - map (nombre del mapa sin .yml)
    */
    try {
        a.exec();
    } catch (const std::exception& e){
        std::cout << e.what() << std::endl;
        return -1;
    }

    // Por qué no pasarle la LogInInfo al client handler? Así no tendrían un socket
    // suelto en el main. 
    Socket cli = std::move(info.socket);
    Client clientHandler(std::move(cli), clientConfig);
    clientHandler.launch();
    return 0;
}
