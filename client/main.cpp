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
#include "sdlwrap/SdlSound.h"
//#include "editor/Editor.h"

// main estaria siendo actualmente el drawer (masomenos, hace muchas cosas)
int main(int argc, const char *argv[]){
    //Editor in QT
    //Editor editor;
    //editor.run(argc, argv);

    Socket cli;
    try {
        cli.connect(argv[1], argv[2]);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    } catch (...) {
        std::cerr << "Error desconocido en el hilo main" << std::endl;
        return -1;
    }

	bool running = true;

	BlockingQueue<std::unique_ptr<Command>> comms;

	// Desde aca hasta el proximo comentario, esta seccion es temporal, hasta que tengamos qt
	std::string s;
    do {
        std::cout << "Crea o unite a una partida escribiendo Crear <nombre> o Unirse <nombre>\n";
        std::getline(std::cin, s);
        std::cout << s;
    }
	while (s.find("Unirse") == std::string::npos && s.find("Crear" ) == std::string::npos);

	std::stringstream stream(s);
	std::string comando;
	std::string nombre;
	stream >> comando;
    stream >> nombre;
    if (comando == "Crear"){
        comms.push(std::unique_ptr<Command>(new CreateGame(nombre, "mapa")));
    } else {
        comms.push(std::unique_ptr<Command>(new JoinGame(nombre)));
    }
    // End seccion

    SdlWindow window(800, 600, false, "unaVentana");
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
	return 0;
}
