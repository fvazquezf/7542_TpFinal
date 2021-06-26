#ifndef WEAPON_H
#define WEAPON_H

#include <map>
#include "../sdlwrap/SdlTexture.h"
#include "../sdlwrap/Area.h"
#include "../Camera.h"

// clase que representa a todas las armas
// pasamos un mapa de id de arma
// y sus texturas
// al cambiar de arma
// cambiamos la textura que utiliza

#define KNIFE 0
class Weapon {
protected:
    std::map<uint8_t, SdlTexture>& weaponTextureMap;
    uint8_t currentWeapon;
public:
    explicit Weapon(std::map<uint8_t, SdlTexture>& weaponTextureMap);

    Weapon(const Weapon& other) = delete;
    Weapon& operator=(const Weapon& other) = delete;

    Weapon(Weapon&& other) noexcept;
    Weapon& operator=(Weapon&& other) noexcept;

    void draw(float x, float y, float angle, Camera& cam);
    void changeWeapon(uint8_t id);

    virtual ~Weapon();
};


#endif
