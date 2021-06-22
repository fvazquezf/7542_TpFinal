#ifndef ROTATEEVENT_H
#define ROTATEEVENT_H

#include "ClientEvent.h"

class RotateEvent : public ClientEvent{
private:
    int16_t angle;
public:
    RotateEvent(uint8_t id, int16_t angle);

    void updatePlayer(std::map<int, PlayerModel> &players) override;

    ~RotateEvent() override;
};


#endif
