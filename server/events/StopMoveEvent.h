#ifndef STOPMOVEEVENT_H
#define STOPMOVEEVENT_H

#include "ClientEvent.h"
#include "../WorldModel.h"

class StopMoveEvent : public ClientEvent {
    int dir;

    public:
    explicit StopMoveEvent(int id, int dir);
    void updatePlayer(WorldModel &world) override;
};


#endif
