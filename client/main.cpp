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

    /* // SDL
	bool running = true;

	BlockingQueue<std::unique_ptr<Command>> comms;

    SdlWindow window(600, 400, false, "unaVentana");
    SoundManager::start();
    WorldView world(window);

    SdlLoop l(comms, world);

	Protocol prot;

	Sender sender(comms, cli, prot);
	sender.start();
	Receiver receiver(world, cli, prot);
	receiver.start();

	l.start();
    auto start = std::chrono::steady_clock::now();
    size_t it = 0;
	while (running){
        world.render(it);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<float, std::micro> elapsed = (end - start);
        int rest = FRAMERATE - std::ceil(elapsed.count());

        // me comi unos ricos frames
        if (rest < 0){
            int behind = - rest;
            rest = FRAMERATE - behind % FRAMERATE;
            int lost = behind + rest;
            start += std::chrono::microseconds(lost);
            it += lost / FRAMERATE;
        }
        usleep(rest);
        start += std::chrono::microseconds(FRAMERATE);
        ++it;
        if (l.isDone()){
            running = false;
            receiver.stop();
            cli.close();
        }
    }
	l.join();
	sender.join();
	receiver.join();
	return 0;*/
    return 0;
}
