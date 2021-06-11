#include <unistd.h>
#include <chrono>
#include "anim/Animation.h"
#include "SdlLoop.h"
#include "commands/Command.h"
#include "Sender.h"
#include "WorldView.h"

// main estaria siendo actualmente el drawer (masomenos, hace muchas cosas)
int main(int argc, char const *argv[]){
	WorldView world;

	world.update();
	world.render();

	world.createTerrorist();
	bool running = true;

	BlockingQueue<std::unique_ptr<Command>> comms;
	// loop de sdl, recibe los inputs y los encola
	SdlLoop l(comms, world);
	// protocolo
	Protocol prot;
	// sender, popea los comandos que pushea sdl
    // y los enviara al serv
    // falta ponerle un socket
	Sender sender(comms, prot);
	sender.start();
	l.start();
	while (running){
		auto start = std::chrono::system_clock::now();
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<float, std::micro> elapsed = (end - start);

        world.update();
        world.render();

        usleep(FRAMERATE + elapsed.count());
        if (l.isDone()){
            running = false;
        }
    }
	l.join();
	sender.join();
	return 0;	
}
