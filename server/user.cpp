#include "user.h"

User::User(Socket socket)
: socket(std::move(socket)),
  receiver(this->socket, protocol),
  playing(false){
}

User::~User() {
}

void User::start() {
    std::cout <<"Entro al start de thSender\n";
    playing = true;
    this->receiver.start();
}

void User::join() {
    //this->thSender.join();
    if (playing){
        this->receiver.join();
    }
}

void User::run() {
    //this->thSender.run();
}

bool User::isDead() {
    //return this->thSender.isDead();
}

void User::stop() {
    //this->thSender.stop();
}

User::User(User &&other) noexcept
: protocol(std::move(other.protocol)),
  socket(std::move(other.socket)),
  receiver(socket, protocol){
}

User &User::operator=(User &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    protocol = std::move(other.protocol);
    socket = std::move(other.socket);
    receiver = std::move(other.receiver);
    return *this;
}
