#ifndef CLIENTEVENT_H
#define CLIENTEVENT_H


#include <cstdint>
#include <map>
//#include "../WorldModel.h"
#include "../PlayerModel.h"

// forward declaration
// class WorldModel;

class ClientEvent {
protected:
    uint8_t clientId;
public:
    ClientEvent(uint8_t clientId);

    virtual void updatePlayer(std::map<int, PlayerModel>& players) = 0;

    virtual ~ClientEvent();
};


#endif
