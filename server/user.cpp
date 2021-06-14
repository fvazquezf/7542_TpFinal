#include "user.h"

User::User(Socket socket)
: socket(std::move(socket)){
}

User::~User() {
    this->join();
    this->stop();
}

void User::start() {
    std::cout <<"Entro al start de thSender\n";
    //this->thSender.start();
}

void User::join() {
    //this->thSender.join();
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
  socket(std::move(other.socket)){
}

User &User::operator=(User &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    protocol = std::move(other.protocol);
    socket = std::move(other.socket);
    return *this;
}
