#include "./th_acceptor.h"

ThAcceptor::ThAcceptor(char* port, Games games) {
    this->server.bind(port);
    this->server.listen();
    this->keep_running = true;
}

ThAcceptor::~ThAcceptor() {
    this->join();
    std::list<ThLogin *>::iterator it = this->clients.begin();
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
            ThLogin *client = new ThLogin(peer, games);
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
}

void ThAcceptor::cleanTheads() {
    std::list<ThLogin *>::iterator it = this->clients.begin();
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
