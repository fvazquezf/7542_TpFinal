#ifndef KNIFE_H
#define KNIFE_H

#include "Weapon.h"

class Knife : public Weapon{
public:
    explicit Knife(SdlTexture& knifeTex);

    void draw(int posX, int posY, float angle) override;
    void makeSound() override;

    ~Knife() override;
};


#endif
