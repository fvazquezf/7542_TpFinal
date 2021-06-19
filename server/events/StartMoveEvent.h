#ifndef STARTMOVEEVENT_H
#define STARTMOVEEVENT_H

#include "ClientEvent.h"

class StartMoveEvent : public ClientEvent {
    int dir;

    public:
    explicit StartMoveEvent(int id, int dir);
    void updatePlayer(std::map<int, PlayerModel>& players);
};


#endif
