#ifndef BROADCASTER_H
#define BROADCASTER_H

#include "../common/BlockingQueue.h"
#include "updates/Update.h"
#include <map>


class Broadcaster{
private:
    std::map<uint8_t, BlockingQueue<Update>>& clientsQueues;
public:
    explicit Broadcaster(std::map<uint8_t, BlockingQueue<Update>>& clientQueueMap);
    //BlockingQueue<std::map<int, std::pair<float, float>>>& addClient(int id);
    // void pushAll(std::map<int, std::pair<float, float>> update);
    void push(Update update);


};

#endif