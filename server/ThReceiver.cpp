#include "ThReceiver.h"
#include "events/ClientEvent.h"
#include "events/StartMoveEvent.h"
#include "events/StopMoveEvent.h"
#include "events/RotateEvent.h"
#include "events/StartAttackEvent.h"
#include "events/StopAttackEvent.h"
#include "events/EquipWeaponEvent.h"
#include "events/BuyEvent.h"
#include "events/DisconnectEvent.h"
#include "events/PickUpEvent.h"
#include "events/ReloadEvent.h"
#include "events/StartPlantEvent.h"
#include "events/StopPlantEvent.h"

ThReceiver::ThReceiver(Socket &peer,
                       Protocol &protocol,
                       ProtectedQueue<std::unique_ptr<ClientEvent>>& eventQueue,
                       uint8_t userId,
                       std::function<void()>& earlyStartCallback)
: peer(peer),
  is_running(true),
  protocol(protocol),
  eventQueue(eventQueue),
  userId(userId),
  earlyStartCallback(earlyStartCallback){
}

void ThReceiver::run() {
    std::function<std::vector<unsigned char>(size_t)>
    receiverCallback = std::bind(&ThReceiver::receive,
                             this,
                                 std::placeholders::_1);
    std::vector<unsigned char> msg;
    while (is_running){
        char comm;
        try {
            if (!peer.recv(&comm, 1)){
                break;
            }
        } catch (const std::exception& e){
            break;
        }
        msg = protocol.dispatchReceived(comm, receiverCallback);
        handleReceived(comm, msg);
    }
    stop();
    eventQueue.push(std::unique_ptr<ClientEvent>(new DisconnectEvent(userId)));
}

ThReceiver::~ThReceiver() {
}

std::vector<unsigned char> ThReceiver::receive(size_t size) {
    std::vector<unsigned char> msg(size);
    try {
        if (!peer.recv(reinterpret_cast<char *>(msg.data()), size)){
            is_running = false;
            return msg;
        }
    } catch (const std::exception& e){
        is_running = false;
    }
    return msg;
}

// si un user se desconecta
// recv deja de estar bloqueada
// en ese caso, cerramos el reading
// luego, para terminar la conexion
// resta matar la q del sender
// desde el broadcaster
void ThReceiver::stop() {
    if (is_running){
        peer.shutdown(SHUT_RD);
        is_running = false;
    }
}

ThReceiver::ThReceiver(ThReceiver &&other)
: peer(other.peer),
  is_running(other.is_running.operator bool()),
  protocol(other.protocol),
  eventQueue(other.eventQueue),
  userId(other.userId),
  earlyStartCallback(other.earlyStartCallback){
    // no hay que hacerle stop
    // si a other le hacemos stop matamos al peer (el rd)
    other.is_running = false;
}

ThReceiver &ThReceiver::operator=(ThReceiver &&other)  {
    if (this == &other){
        return *this;
    }

    is_running = other.is_running.operator bool();
    other.is_running = false;
    userId = other.userId;

    return *this;
}

void ThReceiver::handleReceived(uint8_t code, std::vector<unsigned char> &msg) {
    switch (code){
        case MOVE:
            eventQueue.push(std::unique_ptr<ClientEvent>(new StartMoveEvent(userId, msg.at(0))));
            break;
        case STOP_MOVE:
            eventQueue.push(std::unique_ptr<ClientEvent>(new StopMoveEvent(userId, msg.at(0))));
            break;
        case ROTATE: {
            auto angle = static_cast<int16_t>(protocol.deserializeMsgLenShort(msg));
            eventQueue.push(std::unique_ptr<ClientEvent>(new RotateEvent(userId, angle)));
            break;
        }
        case ATTACK:
            eventQueue.push(std::unique_ptr<ClientEvent>(new StartAttackEvent(userId)));
            break;
        case STOP_ATTACK:
            eventQueue.push(std::unique_ptr<ClientEvent>(new StopAttackEvent(userId)));
            break;
        case CHANGE_WEAPON:
            eventQueue.push(std::unique_ptr<ClientEvent>(new EquipWeaponEvent(userId, msg.at(0))));
            break;
        case BUY:
            eventQueue.push(std::unique_ptr<ClientEvent>(new BuyEvent(userId, msg.at(0))));
            break;
        case PICKUP:
            eventQueue.push(std::unique_ptr<ClientEvent>(new PickUpEvent(userId)));
            break;
        case RELOAD:
            eventQueue.push(std::unique_ptr<ClientEvent>(new ReloadEvent(userId)));
            break;
        case PLANT:
            eventQueue.push(std::unique_ptr<ClientEvent>(new StartPlantEvent(userId)));
            break;
        case STOP_PLANT:
            eventQueue.push(std::unique_ptr<ClientEvent>(new StopPlantEvent(userId)));
            break;
        case EARLY_START:
            earlyStartCallback();
            break;
        default:
            break;
    }
}
