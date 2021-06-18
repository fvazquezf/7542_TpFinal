#ifndef BROADCASTER_H
#define BROADCASTER_H

#include "../common/BlockingQueue.h"

#include <map>


class Broadcaster{
    std::map<int, BlockingQueue<std::map<int, std::pair<float, float>>>> clientsQues;

    public:
        BlockingQueue<std::map<int, std::pair<float, float>>>& addClient(int id);
        void pushAll(std::map<int, std::pair<float, float>> update);


};

#endif
