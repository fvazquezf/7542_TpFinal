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
    auto start = std::chrono::steady_clock::now();
    uint8_t it = 0;
	while (running){
        world.render(0);
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
