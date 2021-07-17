#ifndef BROADCASTER_H
#define BROADCASTER_H

#include "../common/BlockingQueue.h"
#include "updates/Update.h"
#include <map>
#include <memory>


class Broadcaster{
private:
    std::map<uint8_t, BlockingQueue<std::shared_ptr<Update>>> clientsQueues;
    std::mutex broadcasterMutex; // puede ser accedido por main y por el world
public:
    Broadcaster();
    BlockingQueue<std::shared_ptr<Update>>& addPlayer(uint8_t id);

    Broadcaster(const Broadcaster& other) = delete;
    Broadcaster& operator=(const Broadcaster& other) = delete;

    Broadcaster(Broadcaster&& other) ;
    Broadcaster& operator=(Broadcaster&& other) ;

    void pushAll(const std::shared_ptr<Update>& update);
    void push(uint8_t id, std::shared_ptr<Update> update);

    ~Broadcaster();

    void closePlayerQueue(uint8_t id);

    void closeAllQueues();
};

#endif
