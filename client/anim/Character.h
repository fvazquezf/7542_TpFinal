#ifndef TERRORIST_H
#define TERRORIST_H
#include "Renderizable.h"
#include "../weapons/Weapon.h"
#include "Animation.h"

class Character : public Renderizable {
private:
    bool player;
    Weapon weapon;
    bool bleeding = false;
    bool wasHit = false;
    Animation bloodAnimation;
    int currentBleedIteration;
public:
	Character(SdlTexture& texture,
              float posX,
              float posY,
              bool player,
              std::map<uint8_t, SdlTexture>& weapons,
              SdlTexture& blood);

	Character(const Character& other) = delete;
    Character& operator=(const Character& other) = delete;

    Character(Character&& other) noexcept;
    Character& operator=(Character&& other) noexcept;

    void render(Camera &cam, uint8_t iteration) override;
	void update() override;

	void hit();
	void die();

	~Character() override;
};

#endif
