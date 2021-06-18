#include <unistd.h>
#include <chrono>
#include "anim/Animation.h"
#include "SdlLoop.h"
#include "commands/Command.h"
#include "Sender.h"
#include "WorldView.h"
#include "../common/socket.h"
#include "sdlwrap/SdlWindow.h"

// main estaria siendo actualmente el drawer (masomenos, hace muchas cosas)
int main(int argc, const char *argv[]){
    Socket cli;
    cli.connect(argv[1], argv[2]);
    SdlWindow window(800, 600, false, "unaVentana");
	WorldView world(window);

	world.update();
	world.render();

	world.createTerrorist(true, 5.0f, 5.0f);
	world.createTerrorist(false, 3.0f, 4.0f);
	bool running = true;

	BlockingQueue<std::unique_ptr<Command>> comms;
	// loop de sdl, recibe los inputs y los encola
	SdlLoop l(comms, world);
	// protocolo
	Protocol prot;
	// sender, popea los comandos que pushea sdl
    // y los enviara al serv
    // falta ponerle un socket
	Sender sender(comms, cli, prot);
	sender.start();
	l.start();
	while (running){
		auto start = std::chrono::system_clock::now();

        world.update();
        world.render();

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<float, std::micro> elapsed = (end - start);
        usleep(FRAMERATE + elapsed.count());
        if (l.isDone()){
            running = false;
        }
    }
	l.join();
	sender.join();
	return 0;
}
