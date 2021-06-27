#ifndef EQUIPWEAPONEVENT_H
#define EQUIPWEAPONEVENT_H

#include "ClientEvent.h"
#include "../WorldModel.h"

class EquipWeaponEvent : public ClientEvent{
private:
    uint8_t weaponCode;
public:
    EquipWeaponEvent(uint8_t id, uint8_t code);

    void updatePlayer(WorldModel &world) override;

    ~EquipWeaponEvent() override;
};


#endif
