#include "./th_sender.h"
#include "../common/Protocol.h"
#define BUFF_SIZE 256

/*ThSender::ThSender(Socket &socket, Protocol& protocol, BlockingQueue<std::map<int, std::pair<float, float>>>& updates)
: is_running(true),
  peer(socket),
  protocol(protocol),
  updates(updates) {
}*/

ThSender::ThSender(Socket &socket, Protocol &protocol, BlockingQueue<Update> &updates)
: peer(socket),
  protocol(protocol),
  updateQueue(updates){
}

ThSender::~ThSender() {
}

void ThSender::run() {
    std::cout <<"Entro a th_sender\n";

    while (!this->isDead()) {
        Update update = updateQueue.pop();
        // update->hacerAlgo();
        // update tiene ref al mundo logico
        // sender no tiene pq conocer nada del mundo!
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
: is_running(other.is_running.operator bool()),
  peer(other.peer),
  protocol(other.protocol),
  updateQueue(other.updateQueue){
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
