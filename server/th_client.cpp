#include "./th_client.h"
#include "../common/ta_te_ti_logica.h"
#include <atomic>
#include <string>
#include <string.h>

#define BUFF_SIZE 256

ThClient::ThClient(Socket &socket, PartidasDisponibles &partidas,
                    RepositorioDeTableros &repo):
                    thSender(socket, partidas, repo) {
}

ThClient::~ThClient() {
}

void ThClient::start() {
    this->thSender.start();
}

void ThClient::join() {
    this->thSender.join();
}

void ThClient::run() {
    this->thSender.run();
}

bool ThClient::isDead() {
    return this->thSender.isDead();
}

void ThClient::stop() {
    this->thSender.stop();
}
