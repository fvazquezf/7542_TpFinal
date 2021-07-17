#ifndef TERRORIST_H
#define TERRORIST_H
#include "../Renderizable.h"
#include "../weapons/Weapon.h"
#include "Animation.h"
#include "../SoundManager.h"

class Character : public Renderizable {
private:
    bool player;
    bool bleeding;
    bool wasHit;
    bool moving;
    size_t lastIter;
    Weapon weapon;
    // animacion de movimiento
    Animation movementAnimation;
    // animacion de sangrado
    Animation bloodAnimation;
    // animacion de piernas (si, de piernas)
    Animation legAnimation;

    std::map<uint8_t, uint8_t> weaponCharacterFrameMap;
    size_t currentMovingUpdates;
public:
	Character(SdlTexture& texture,
              float posX,
              float posY,
              bool player,
              std::map<uint8_t, SdlTexture>& weapons,
              SdlTexture& blood,
              SdlTexture& legs);

	Character(const Character& other) = delete;
    Character& operator=(const Character& other) = delete;

    Character(Character&& other) ;
    Character& operator=(Character&& other) ;

    void render(Camera &cam, size_t iteration) override;

    void updatePosition(float x, float y) override;

	void changeWeapon(uint8_t weaponCode);

	void hit(float distanceToCenter);
	void die(float distanceToCenter);
	void move(float distanceToCenter) const;

	~Character() override;

    void attack(float distanceToCenter);

    void pushPositionOffset(std::tuple<float, float, int> positionOffset);

    std::pair<float, float> getPosition();
};

#endif
