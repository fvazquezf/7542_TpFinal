#ifndef RELOADEVENT_H
#define RELOADEVENT_H


#include "ClientEvent.h"

class ReloadEvent : public ClientEvent {
public:
    ReloadEvent(uint8_t id);

    void updatePlayer(WorldModel &world) override;

    ~ReloadEvent() override;
};


#endif
