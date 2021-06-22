#ifndef STARTMOVEEVENT_H
#define STARTMOVEEVENT_H

#include "ClientEvent.h"
#include "../WorldModel.h"

class StartMoveEvent : public ClientEvent {
    int dir;

    public:
    explicit StartMoveEvent(int id, int dir);
    void updatePlayer(WorldModel &world) override;
};


#endif
