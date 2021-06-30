#include "Broadcaster.h"

#include <map>
#include <utility>

void Broadcaster::pushAll(const std::shared_ptr<Update>& update){
    for (auto& queuePair : clientsQueues) {
        queuePair.second.push(update);
    }
}

BlockingQueue<std::shared_ptr<Update>> &Broadcaster::addPlayer(uint8_t id) {
    clientsQueues.emplace(std::piecewise_construct,
                          std::forward_as_tuple(id),
                          std::forward_as_tuple());
    return clientsQueues.at(id);
}

void Broadcaster::push(uint8_t id, std::shared_ptr<Update> update) {
    clientsQueues.at(id).push(std::move(update));
}

Broadcaster::Broadcaster(Broadcaster &&other) noexcept
: clientsQueues(std::move(other.clientsQueues)){
}

Broadcaster &Broadcaster::operator=(Broadcaster &&other) noexcept {
    if (this == &other){
        return *this;
    }

    clientsQueues = std::move(other.clientsQueues);
    return *this;
}

Broadcaster::Broadcaster() {
}

Broadcaster::~Broadcaster() {

}
