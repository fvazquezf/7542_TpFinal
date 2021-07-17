#include "./th_sender.h"
#include "../common/Protocol.h"

ThSender::ThSender(Socket &socket, Protocol &protocol, BlockingQueue<std::shared_ptr<Update>> &updates)
: is_running(true),
  peer(socket),
  protocol(protocol),
  updateQueue(updates){
}

ThSender::~ThSender() {
}

void ThSender::run() {
    std::function<void(std::vector<unsigned char>)> cb =
            std::bind(&ThSender::send, this, std::placeholders::_1);
    while (updateQueue.isNotClosedOrNotEmpty()) {
        try {
            std::shared_ptr<Update> update = updateQueue.pop();
            update->serialize(cb);
        } catch (const std::invalid_argument& e){
            break;
        }
    }
    this->stop();
}

void ThSender::stop() {
    if (is_running){
        this->is_running = false;
        this->peer.close();
    }
}

ThSender::ThSender(ThSender &&other)
: is_running(other.is_running.operator bool()),
  peer(other.peer),
  protocol(other.protocol),
  updateQueue(other.updateQueue){
    // no hay que hacerle stop
    // si a other le hacemos stop matamos al peer (el rd)
    other.is_running = false;
}

ThSender &ThSender::operator=(ThSender &&other)  {
    if (this == &other){
        return *this;
    }

    is_running = other.is_running.operator bool();
    other.is_running = false;
    return *this;
}

void ThSender::send(std::vector<unsigned char> msg) {
    peer.send(reinterpret_cast<const char *>(msg.data()), msg.size());
}
