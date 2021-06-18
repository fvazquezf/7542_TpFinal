#include "./th_sender.h"
#include "../common/Protocol.h"
#define BUFF_SIZE 256

ThSender::ThSender(Socket &socket, Protocol& protocol, BlockingQueue<std::map<int, std::pair<float, float>>>& updates)
: is_running(true),
  peer(socket),
  protocol(protocol),
  updates(updates) {
}

ThSender::~ThSender() {
}

void ThSender::run() {
    std::cout <<"Entro a th_sender\n";

    while (!this->isDead()) {
        updates.pop();
    }
    this->stop();
    this->is_running = false;
}

bool ThSender::isDead() {
    return is_running == false;
}

void ThSender::stop() {
    this->is_running = false;
    this->peer.close();
}

ThSender::ThSender(ThSender &&other) noexcept
: peer(other.peer),
  is_running(other.is_running.operator bool()),
  protocol(other.protocol),
  updates(other.updates){
    // no hay que hacerle stop
    // si a other le hacemos stop matamos al peer (el rd)
    other.is_running = false;
}

ThSender &ThSender::operator=(ThSender &&other) noexcept {
    if (this == &other){
        return *this;
    }

    is_running = other.is_running.operator bool();
    other.is_running = false;

    return *this;
}
