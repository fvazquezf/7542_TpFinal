#ifndef BUYEVENT_H
#define BUYEVENT_H


#include "ClientEvent.h"

class BuyEvent : public ClientEvent {
private:
    uint8_t weaponCode;
public:
    BuyEvent(uint8_t id, uint8_t weaponCode);

    void updatePlayer(WorldModel &world) override;

    ~BuyEvent() override;
};


#endif
