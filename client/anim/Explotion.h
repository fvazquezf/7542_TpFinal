#ifndef EXPLOTION_H
#define EXPLOTION_H

#include <SDL2/SDL.h>
#include "Animation.h"
#include "../sdlwrap/Area.h"
#include "../sdlwrap/SdlTexture.h"
#include "../sdlwrap/SdlWindow.h"

class Explotion {
private:
	Animation animation;
	bool shouldBlow;
	int dstX;
	int dstY;
public:
	Explotion(const SdlTexture& texture, int dstX, int dstY);

	void render();

	~Explotion();
};

#endif