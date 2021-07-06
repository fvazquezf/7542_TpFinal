#ifndef PICKUPEVENT_H
#define PICKUPEVENT_H


#include "ClientEvent.h"

class PickUpEvent : public ClientEvent {
public:
    explicit PickUpEvent(uint8_t id);

    void updatePlayer(WorldModel &world) override;

    ~PickUpEvent() override;
};


#endif
