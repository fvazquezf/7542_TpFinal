#ifndef TERRORIST_H
#define TERRORIST_H
#include "Renderizable.h"
#include "../weapons/Weapon.h"

class Terrorist : public Renderizable {
private:
    bool player;
    Weapon weapon;
public:
	Terrorist(SdlTexture& texture,
              float posX,
              float posY,
              bool player,
              std::map<uint8_t, SdlTexture>& weapons);

    void render(Camera &cam, uint8_t iteration) override;
	void update() override;
	~Terrorist() override;
};

#endif
