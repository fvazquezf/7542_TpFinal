#ifndef EXPLOTION_H
#define EXPLOTION_H

#include <SDL2/SDL.h>
#include "Animation.h"
#include "../sdlwrap/Area.h"
#include "../sdlwrap/SdlTexture.h"
#include "../sdlwrap/SdlWindow.h"
#include "PositionVector.h"
#include <vector>
#include <utility>

class Explosion {
private:
    // viendo el juego original
    // llegamos a la conclusion de que la explosion de la bomba
    // en realidad tiene varias animaciones (todas iguales)
    // que se reproducen en distinto tiempo y con distintos tamanios
    SdlTexture explosionTexture;
	std::vector<std::pair<Animation, PositionVector>> miniExplosions;
	bool shouldBlow;
	float dstX;
	float dstY;
	int maxMiniExplosions;
	int currentExplosions;
public:
	explicit Explosion(SdlWindow& window);

	void setExplosion(float posX, float posY);
	void render(Camera& cam, size_t iteration);

	~Explosion();
};

#endif