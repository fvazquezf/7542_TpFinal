#include "Broadcaster.h"
#include "../common/BlockingQueue.h"

#include <map>

BlockingQueue<std::map<int, std::pair<float, float>>>& Broadcaster::addClient(int id){
    clientsQues[id] = BlockingQueue<std::map<int, std::pair<float, float>>>();
    return clientsQues[id];
}

void Broadcaster::pushAll(std::map<int, std::pair<float, float>> update){
    for (auto it = clientsQues.begin(); it != clientsQues.end(); it++){
        it->second.push(update);
    }
}