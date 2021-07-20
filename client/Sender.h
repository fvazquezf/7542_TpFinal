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
    void run() override;
    // nuestro callback
    void send(std::vector<unsigned char> msg);
public:
    Sender(BlockingQueue<std::unique_ptr<Command>>& q, Socket& peer, const Protocol& protocol);
    ~Sender() override;
};


#endif
