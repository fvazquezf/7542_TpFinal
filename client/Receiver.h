#ifndef RECEIVER_H
#define RECEIVER_H

#include <atomic>
#include "../common/Thread.h"
#include "WorldView.h"
#include "../common/socket.h"
#include "../common/Protocol.h"


// recibe los updates
// modifica al mundo visible
class Receiver : public Thread{
private:
    WorldView& world;
    Socket& peer;
    Protocol& prot;
    std::atomic_bool running;

    void run() override;

    std::vector<unsigned char> receive(size_t size);

    void handleReceived(uint8_t code, std::vector<unsigned char>& msg);
public:
    explicit Receiver(WorldView& world, Socket& peer, Protocol& protocol);

    void stop();

    ~Receiver() override;
};


#endif
