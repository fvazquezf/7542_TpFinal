#ifndef WEAPON_H
#define WEAPON_H
#include "../sdlwrap/SdlTexture.h"
#include "../sdlwrap/Area.h"

class Weapon {
protected:
    SdlTexture& texture;
public:
    explicit Weapon(SdlTexture& texture);

    void draw(int posX, int posY);
    virtual void draw(int posX, int posY, float angle) = 0;
    virtual void makeSound() = 0;

    virtual ~Weapon();
};


#endif
