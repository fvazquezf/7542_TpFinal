#ifndef SENDER_H
#define SENDER_H


#include "../common/Thread.h"
#include "commands/Command.h"
#include "../common/BlockingQueue.h"
#include "../common/socket.h"

class Sender : public Thread {
private:
    BlockingQueue<std::unique_ptr<Command>>& commQ;
    Socket& peer;
    const Protocol& prot;
public:
    // recibe una referencia a un socket tambien
    // solo que por el momento no mergeamos
    Sender(BlockingQueue<std::unique_ptr<Command>>& q, Socket& peer, const Protocol& protocol);

    void run() override;

    // nuestro callback
    void send(std::vector<unsigned char> msg);

    ~Sender() override;
};


#endif
