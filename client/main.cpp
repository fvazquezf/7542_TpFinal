#include <unistd.h>
#include "sdlwrap/SdlWindow.h"
#include "sdlwrap/SdlTexture.h"
#include <chrono>
#include "anim/Terrorist.h"
#include "anim/Animation.h"
#include "SdlLoop.h"
#include "commands/Command.h"
#include "Sender.h"

// main estaria siendo actualmente el drawer
int main(int argc, char const *argv[]){
	SdlWindow w(800, 600, false, "unaVentana");
	SdlTexture terroristTex("../sprites/gfx/player/t1.bmp", w);
	Terrorist terrorist(terroristTex, 200, 200);

	bool running = true;

	w.fill();
	terrorist.render();
	w.render();

	BlockingQueue<std::unique_ptr<Command>> comms;
	// loop de sdl, recibe los inputs y los encola
	SdlLoop l(comms);
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

		w.fill();
        terrorist.update(FRAMERATE + elapsed.count());
        terrorist.render();
        w.render();

        usleep(FRAMERATE + elapsed.count());
        if (l.isDone()){
            running = false;
        }
    }
	l.join();
	sender.join();
	return 0;	
}
