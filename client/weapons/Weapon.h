#ifndef WEAPON_H
#define WEAPON_H

#include <map>
#include "../sdlwrap/SdlTexture.h"
#include "../sdlwrap/Area.h"
#include "../Camera.h"
//#include "../anim/Character.h"
#define MAX_ROT_KNIFE 90.0f

// clase que representa a todas las armas
// pasamos un mapa de id de arma
// y sus texturas
// al cambiar de arma
// cambiamos la textura que utiliza

#define AK47 0
#define M3 1
#define AWP 2
#define KNIFE 3
#define PISTOL 4
#define BOMB 5

#define WEAPON_WIDTH 32
#define WEAPON_HEIGHT 32

class Character;

class Weapon {
private:
    std::map<uint8_t, SdlTexture>& weaponTextureMap;
    uint8_t currentWeapon;

    // usado para animacion de recoil
    // y rotacion del cuchillo
    // describe una parabola que va desde
    // un angulo 0, hasta un maximo
    // y de vuelta a 0
    float parabolicMotion(int nFrame);
public:
    explicit Weapon(std::map<uint8_t, SdlTexture>& weaponTextureMap);

    Weapon(const Weapon& other) = delete;
    Weapon& operator=(const Weapon& other) = delete;

    Weapon(Weapon&& other) noexcept;
    Weapon& operator=(Weapon&& other) noexcept;

    void draw(float x, float y, float angle, Camera& cam);
    bool changeWeapon(uint8_t id);

    virtual ~Weapon();

    void animate(Character &character, float distanceToCenter, float angle);

    void manageSound(float distanceToCenter) const;
};


#endif
