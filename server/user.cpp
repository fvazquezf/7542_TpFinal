#include "user.h"

User::User(Socket socket): thSender(socket) {
}

User::~User() {
}

void User::start() {
    this->thSender.start();
}

void User::join() {
    this->thSender.join();
}

void User::run() {
    this->thSender.run();
}

bool User::isDead() {
    return this->thSender.isDead();
}

void User::stop() {
    this->thSender.stop();
}