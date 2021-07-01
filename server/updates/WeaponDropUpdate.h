#ifndef WEAPONDROPUPDATE_H
#define WEAPONDROPUPDATE_H


#include "Update.h"

class WeaponDropUpdate : public Update{
private:
    uint8_t weaponCode;
    float x;
    float y;
    // si drop = true -> dropea, sino pickea
    bool drop;
public:
    WeaponDropUpdate(uint8_t code, float posX, float posY, bool drop = true);

    void serialize(std::function<void (std::vector<unsigned char>)> &callback) override;

    ~WeaponDropUpdate() override;
};


#endif
