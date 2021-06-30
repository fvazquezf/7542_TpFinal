#ifndef DISCONNECTEVENT_H
#define DISCONNECTEVENT_H


#include "ClientEvent.h"

class DisconnectEvent : public ClientEvent {
public:
    explicit DisconnectEvent(uint8_t id);

    void updatePlayer(WorldModel &world) override;

    ~DisconnectEvent() override;
};


#endif
