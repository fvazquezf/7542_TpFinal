#ifndef ROTATEEVENT_H
#define ROTATEEVENT_H

#include "ClientEvent.h"
#include "../WorldModel.h"

class RotateEvent : public ClientEvent{
private:
    int16_t angle;
public:
    RotateEvent(uint8_t id, int16_t angle);

    void updatePlayer(WorldModel &world) override;

    ~RotateEvent() override;
};


#endif
