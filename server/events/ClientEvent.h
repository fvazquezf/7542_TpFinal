#ifndef CLIENTEVENT_H
#define CLIENTEVENT_H


#include <cstdint>
#include <map>
#include "../PlayerModel.h"

// forward declaration
class WorldModel;

class ClientEvent {
protected:
    uint8_t clientId;
public:
    explicit ClientEvent(uint8_t clientId);

    virtual void updatePlayer(WorldModel &world) = 0;

    virtual ~ClientEvent();
};


#endif
