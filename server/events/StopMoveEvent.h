#ifndef STOPMOVEEVENT_H
#define STOPMOVEEVENT_H

#include "ClientEvent.h"

class StopMoveEvent : public ClientEvent {
    int dir;

    public:
    explicit StopMoveEvent(int id, int dir);
    void updatePlayer(std::map<int, PlayerModel>& players);
};


#endif
