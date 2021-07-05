#ifndef STARTPLANTEVENT_H
#define STARTPLANTEVENT_H

#include "ClientEvent.h"
#include "../WorldModel.h"

class StartPlantEvent : public ClientEvent {
    
    public:
    explicit StartPlantEvent(uint8_t id);
    void updatePlayer(WorldModel &world) override;
};


#endif
