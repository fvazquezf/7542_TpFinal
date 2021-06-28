#ifndef WEAPONUPDATE_H
#define WEAPONUPDATE_H

#include "Update.h"

class WeaponUpdate : public Update{
private:
    uint8_t id;
    uint8_t weaponId;
public:
    explicit WeaponUpdate(uint8_t id, uint8_t weaponId);

    void serialize(std::function<void(std::vector<unsigned char>)>& callback) override;

    ~WeaponUpdate() override;
};


#endif
