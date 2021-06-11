#include "./th_sender.h"
#define BUFF_SIZE 256

ThSender::ThSender(Socket &socket): peer(std::move(socket)) {
    this->is_running = true;
}

ThSender::~ThSender() {
}

void ThSender::run() {
    std::string mensaje = "";
    Protocol p(this->peer);
    while (!this->isDead()) {
        mensaje = p.recibirComando();
        p.enviarRespuesta("Restpuesta a comando: " + mensaje + ".");
        if (mensaje == "q") {
            break;
        }
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
