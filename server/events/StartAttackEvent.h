#ifndef STARTATTACKEVENT_H
#define STARTATTACKEVENT_H

#include "ClientEvent.h"
#include "../WorldModel.h"

class StartAttackEvent : public ClientEvent {
    
    public:
    explicit StartAttackEvent(uint8_t id);
    void updatePlayer(WorldModel &world) override;
};


#endif
