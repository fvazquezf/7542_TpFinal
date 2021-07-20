#include "Sender.h"
#include <functional>

Sender::Sender(BlockingQueue<std::unique_ptr<Command>> &q, Socket& peer, const Protocol& protocol)
: commQ(q), peer(peer), prot(protocol) {
}

void Sender::run() {
    std::unique_ptr<Command> comm;
    while (commQ.isNotClosedOrNotEmpty()) {
        try{
            comm = commQ.pop();
        } catch (const std::exception& e) {
            break;
        }
        std::function<void(std::vector<unsigned char>)> callback =
                std::bind(&Sender::send, this, std::placeholders::_1);
        comm->serialize(callback, prot);
    }
    peer.close(); // mata a receive
}

Sender::~Sender() {
}

void Sender::send(std::vector<unsigned char> msg) {
    try {
        peer.send(reinterpret_cast<const char *>(msg.data()), msg.size());
    } catch (const std::exception& e) {
        commQ.signalClosed();
    }
}

