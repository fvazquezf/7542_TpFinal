#ifndef STOPATTACKEVENT_H
#define STOPATTACKEVENT_H

#include "ClientEvent.h"
#include "../WorldModel.h"

class StopAttackEvent : public ClientEvent {
    
    public:
    explicit StopAttackEvent(uint8_t id);
    void updatePlayer(WorldModel &world) override;
};


#endif
