#include "./th_acceptor.h"

ThAcceptor::ThAcceptor(char* port, GamesMonitor& games)
: games(games),
  keep_running(true) {
    this->server.bind(port);
    this->server.listen();
}

ThAcceptor::~ThAcceptor() {
    this->join();
    auto it = this->clients.begin();
    while (it != this->clients.end()) {
        (*it)->stop();
        (*it)->join();
        delete (*it);
        it = this->clients.erase(it);
    }
}

void ThAcceptor::run() {
    while (keep_running) {
        try {
            Socket peer = std::move(server.accept());
            auto *client = new ThLogin(std::move(peer), games);
            clients.push_back(client);
            client->start();
            this->cleanTheads();
        } catch (std::invalid_argument &e) {
            return;
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Error desconocido en el hilo client\n";
        }
    }
    keep_running = false;
}

void ThAcceptor::cleanTheads() {
    auto it = this->clients.begin();
    while (it != this->clients.end()) {
        if ((*it)->isDead()) {
            (*it)->join();
            delete (*it);
            it = this->clients.erase(it);
        } else {
            ++it;
        }
    }
}

void ThAcceptor::stop() {
    this->keep_running = false;
    this->server.close();
}
