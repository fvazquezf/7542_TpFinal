#include "Sender.h"
#include <functional>

Sender::Sender(BlockingQueue<std::unique_ptr<Command>> &q, const Protocol& protocol)
: commQ(q), prot(protocol){
}

void Sender::run() {
    std::unique_ptr<Command> comm;
    while (commQ.isNotClosedOrNotEmpty()){
        try{
            comm = commQ.pop();
        } catch (const std::invalid_argument& e){
            break;
        }
        std::function<void(std::vector<unsigned char>)> callback =
                std::bind(&Sender::send, this, std::placeholders::_1);
        comm->serialize(callback, prot);
    }
}

Sender::~Sender() {
}

void Sender::send(std::vector<unsigned char> msg) {
    // socket.send(msg.data(), msg.len());
    for (auto& it : msg){
        printf("%02x ", it);
    }
    puts("");
}

