#include "ThReceiver.h"
#include "events/ClientEvent.h"
#include "events/StartMoveEvent.h"
#include "events/StopMoveEvent.h"

ThReceiver::ThReceiver(Socket &peer,
                       Protocol &protocol,
                       ProtectedQueue<std::unique_ptr<ClientEvent>>& eventQueue,
                       uint8_t userId)
: peer(peer),
  is_running(true),
  protocol(protocol),
  eventQueue(eventQueue),
  userId(userId){
}

void ThReceiver::run() {
    std::function<std::vector<unsigned char>(size_t)>
    receiverCallback = std::bind(&ThReceiver::receive,
                             this,
                                 std::placeholders::_1);
    std::vector<unsigned char> msg;
    while (is_running){
        char comm;
        int r = peer.recv(&comm, 1);
        if (r < 1){
            break;
        }
        msg = protocol.dispatchReceived(comm, receiverCallback);
        handleReceived(comm, msg);
    }
    is_running = false;
}

ThReceiver::~ThReceiver() {
}

std::vector<unsigned char> ThReceiver::receive(size_t size) {
    std::vector<unsigned char> msg(size);
    peer.recv(reinterpret_cast<char *>(msg.data()), size);
    return msg;
}

void ThReceiver::stop() {
    peer.shutdown(SHUT_RD);
    is_running = false;
}

ThReceiver::ThReceiver(ThReceiver &&other) noexcept
: peer(other.peer),
  is_running(other.is_running.operator bool()),
  protocol(other.protocol),
  eventQueue(other.eventQueue){
    // no hay que hacerle stop
    // si a other le hacemos stop matamos al peer (el rd)
    other.is_running = false;
}

ThReceiver &ThReceiver::operator=(ThReceiver &&other) noexcept {
    if (this == &other){
        return *this;
    }

    is_running = other.is_running.operator bool();
    other.is_running = false;

    return *this;
}

void ThReceiver::handleReceived(uint8_t code, std::vector<unsigned char> &msg) {
    switch (code){
        case MOVE:
            eventQueue.push(std::unique_ptr<ClientEvent>(new StartMoveEvent(userId, msg.at(0))));
            break;
        case STOP_MOVE:
            eventQueue.push(std::unique_ptr<ClientEvent>(new StopMoveEvent(userId, msg.at(0))));
            break;
        default:
            break;
    }
}
