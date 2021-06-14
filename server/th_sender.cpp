#include "./th_sender.h"
#include "../common/Protocol.h"
#define BUFF_SIZE 256

ThSender::ThSender(Socket &socket)
: is_running(true),
  peer(socket) {
}

ThSender::~ThSender() {
}

void ThSender::run() {
    std::cout <<"Entro a th_sender\n";
    std::string mensaje = "";
    Protocol p;
        std::cout <<"Entro al while\n";

    while (!this->isDead()) {
        //char comm;
        //peer.recv(&comm, 1);
        //p.dispatchReceived();
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
