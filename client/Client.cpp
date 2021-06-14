#include "Client.h"
#include "WorldView.h"
#include "SdlLoop.h"


Client::Client()
: window(800, 600, false, "unaVentana"){
}

void Client::launch(const char *host, const char *serv) {
    clientSocket.connect(host, serv);
    WorldView world(window);
    BlockingQueue<std::unique_ptr<Command>> comms;
    SdlLoop commandLoop(comms, world);

    commandLoop.start();
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
