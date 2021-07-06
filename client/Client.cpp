#include <sstream>
#include "Client.h"
#include "WorldView.h"
#include "SdlLoop.h"
#include "Drawer.h"
#include "Receiver.h"


Client::Client(Socket clientSocket)
: clientSocket(std::move(clientSocket)),
  window(600, 400, false, "unaVentana"){
}

void Client::launch() {
    BlockingQueue<std::unique_ptr<Command>> comms;

    //SdlWindow window(600, 400, false, "unaVentana");
    SoundManager::start();
    WorldView world(window);
    Drawer drawer(world);
    drawer.start();

    Protocol prot;

    Receiver receiver(world, clientSocket, prot);
    receiver.start();

    Sender sender(comms, clientSocket, prot);
    sender.start();

    SdlLoop sdlLoop(comms, world);
    sdlLoop.start();

    receiver.join();
    sdlLoop.join();
    sender.join();
    drawer.join();
}

Client::Client(Client &&other) noexcept
: clientSocket(std::move(other.clientSocket)),
  window(800, 600, false, "unaVentana"){
}

Client &Client::operator=(Client &&other) noexcept {
    if (this == &other){
        return *this;
    }

    clientSocket = std::move(other.clientSocket);
    return *this;
}

Client::~Client() {
}
