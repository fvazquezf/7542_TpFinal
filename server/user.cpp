#include "user.h"
#include "events/ClientEvent.h"

/*User::User(Socket socket, PlayerModel& modelRef, BlockingQueue<std::map<int, std::pair<float, float>>>& updates)
: socket(std::move(socket)),
  receiver(this->socket, protocol),
  sender(this->socket, protocol, updates),
  playing(false),
  model(modelRef){
}*/

User::User(Socket socket,
           ProtectedQueue<std::unique_ptr<ClientEvent>>& eventQueue,
           BlockingQueue<Update>& updateQueue,
           uint8_t id)
: socket(std::move(socket)),
  sender(this->socket, protocol, updateQueue),
  receiver(this->socket, protocol, eventQueue),
  id(id){
}

User::~User() {
}

void User::start() {
    std::cout <<"Entro al start de thSender\n";
    playing = true;
    this->receiver.start();
    this->sender.start();
}

void User::join() {
    //this->thSender.join();
    if (playing){
        this->receiver.join();
        this->sender.join();
    }
}

void User::run() {
    //this->thSender.run();
}

bool User::isDead() {
    //return this->thSender.isDead();
    return true;
}

void User::stop() {
    //this->thSender.stop();
}

// solo llamado por map.emplace
// al momento de construir al user
User::User(User &&other) noexcept
: protocol(std::move(other.protocol)),
  socket(std::move(other.socket)),
  sender(std::move(other.sender)),
  receiver(std::move(other.receiver)),
  id(other.id)
  //model(other.model)
{
}

User &User::operator=(User &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    protocol = std::move(other.protocol);
    socket = std::move(other.socket);
    receiver = std::move(other.receiver);
    sender = (std::move(other.sender));
    //model = other.model;
    return *this;
}

