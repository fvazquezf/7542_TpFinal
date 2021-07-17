#include <sstream>
#include <qt/LogInInfo.h>
#include "Client.h"
#include "WorldView.h"
#include "SdlLoop.h"
#include "Drawer.h"
#include "Receiver.h"
#include "MapView.h"


Client::Client(LogInInfo& login, YAML::Node& clientConfig)
: clientSocket(std::move(login.socket)),
  clientConfig(clientConfig),
  window(clientConfig["width"].as<int>(),
         clientConfig["height"].as<int>(),
         clientConfig["fullscreen"].as<bool>(), "CS2D"){
}

void Client::launch() {
    BlockingQueue<std::unique_ptr<Command>> comms;

    SoundManager::start(clientConfig["sound_on"].as<bool>());
    WorldView world(window, clientConfig);
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

Client::Client(Client &&other): clientSocket(std::move(other.clientSocket)),
  clientConfig(other.clientConfig),
  window(clientConfig["width"].as<int>(),
          clientConfig["height"].as<int>(),
                  clientConfig["fullscreen"].as<bool>(), "unaVentana"){
}

Client &Client::operator=(Client &&other) {
    if (this == &other){
        return *this;
    }

    clientSocket = std::move(other.clientSocket);
    return *this;
}

Client::~Client() {
}
