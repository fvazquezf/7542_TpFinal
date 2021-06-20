#include "Receiver.h"

Receiver::Receiver(WorldView &world, Socket& peer, Protocol& protocol)
: world(world),
  peer(peer),
  prot(protocol),
  running(true){
}

Receiver::~Receiver() {
}

void Receiver::run() {
    std::function<std::vector<unsigned char>(size_t)> cb =
            std::bind(&Receiver::receive, this, std::placeholders::_1);
    while (running){
        char update;
        peer.recv(&update, 1);
        std::vector<unsigned char> msg = prot.dispatchReceived(update, cb);
        handleReceived(update, msg);
    }
}

void Receiver::stop() {
    running = false;
}

std::vector<unsigned char> Receiver::receive(size_t size) {
    std::vector<unsigned char> msg(size);
    peer.recv(reinterpret_cast<char *>(msg.data()), size);
    return msg;
}

void Receiver::handleReceived(uint8_t code, std::vector<unsigned char> &msg) {
    switch (code) {
        case POS_UPDATE: {
            auto map = prot.deserializePositions(msg);
            world.updatePositions(map);
            break;
        }
        default:
            break;
    }
}
