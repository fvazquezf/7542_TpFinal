#ifndef CHANGEWEAPON_H
#define CHANGEWEAPON_H

#include "Command.h"

class ChangeWeapon : public Command{
public:
    ChangeWeapon();

    void serialize(std::function<void (std::vector<unsigned char>)> &callback, const Protocol &protocol) override;

    ~ChangeWeapon();
};


#endif
