#include <unistd.h>
#include <chrono>
#include "anim/Animation.h"
#include "SdlLoop.h"
#include "commands/Command.h"
#include "Sender.h"
#include "WorldView.h"
#include "sdlwrap/SdlWindow.h"
#include "Receiver.h"

// main estaria siendo actualmente el drawer (masomenos, hace muchas cosas)
int main(int argc, const char *argv[]){
    Socket cli;
    cli.connect(argv[1], argv[2]);
    SdlWindow window(800, 600, false, "unaVentana");
	WorldView world(window);

	bool running = true;

	BlockingQueue<std::unique_ptr<Command>> comms;

	SdlLoop l(comms, world);

	Protocol prot;

	Sender sender(comms, cli, prot);
	sender.start();
	Receiver receiver(world, cli, prot);
	receiver.start();

	l.start();
	while (running){
		auto start = std::chrono::system_clock::now();

        world.render();

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<float, std::micro> elapsed = (end - start);
        usleep(FRAMERATE + elapsed.count());
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
