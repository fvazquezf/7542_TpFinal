#ifndef STOPPLANTEVENT_H
#define STOPPLANTEVENT_H

#include "ClientEvent.h"
#include "../WorldModel.h"

class StopPlantEvent : public ClientEvent {
    
    public:
    explicit StopPlantEvent(uint8_t id);
    void updatePlayer(WorldModel &world) override;
};


#endif
