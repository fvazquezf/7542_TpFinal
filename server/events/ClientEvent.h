#ifndef CLIENTEVENT_H
#define CLIENTEVENT_H


#include <cstdint>
//#include "../WorldModel.h"

// forward declaration
class WorldModel;

class ClientEvent {
private:
    uint8_t clientId;
public:
    ClientEvent(uint8_t clientId);

    virtual void updateWorld(WorldModel& world) = 0;

    virtual ~ClientEvent();
};


#endif
