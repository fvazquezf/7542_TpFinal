#ifndef WEAPONUPDATE_H
#define WEAPONUPDATE_H

#include "Update.h"

class WeaponUpdate : public Update{
private:
    int id;
    int weaponId;
public:
    explicit WeaponUpdate(int id, int weaponId);

    void serialize(std::function<void(std::vector<unsigned char>)>& callback) override;

    ~WeaponUpdate() override;
};


#endif
