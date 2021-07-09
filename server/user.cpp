#include "user.h"
#include "events/ClientEvent.h"

User::User(Socket socket,
           ProtectedQueue<std::unique_ptr<ClientEvent>>& eventQueue,
           BlockingQueue<std::shared_ptr<Update>>& updateQueue,
           uint8_t id,
           std::function<void()>& earlyStartCb)
: socket(std::move(socket)),
  sender(this->socket, protocol, updateQueue),
  receiver(this->socket, protocol, eventQueue, id, earlyStartCb),
  playing(false),
  id(id){
}

User::~User() {
}

void User::start() {
    playing = true;
    this->receiver.start();
    this->sender.start();
}

void User::join() {
    if (playing){
        this->receiver.stop();
        this->receiver.join();
        this->sender.stop();
        this->sender.join();
    }
    playing = false;
}

bool User::isDead() {
    //return this->thSender.isDead();
    return true;
}

void User::stop() {
    sender.stop();
    receiver.stop();
}

// solo llamado por map.emplace
// al momento de construir al user
User::User(User &&other) noexcept
: protocol(std::move(other.protocol)),
  socket(std::move(other.socket)),
  sender(std::move(other.sender)),
  receiver(std::move(other.receiver)),
  playing(other.playing),
  id(other.id){
}

User &User::operator=(User &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    protocol = std::move(other.protocol);
    socket = std::move(other.socket);
    receiver = std::move(other.receiver);
    sender = std::move(other.sender);
    playing = other.playing;
    id = other.id;
    return *this;
}

