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
    Socket cli = std::move(info.socket);
    Client clientHandler(std::move(cli));
    clientHandler.launch();
    return 0;
}
