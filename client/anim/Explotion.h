#ifndef EXPLOTION_H
#define EXPLOTION_H

#define FRAMERATE 1000000.0f/60.0f
#include <SDL2/SDL.h>
#include "../sdlwrap/Area.h"
#include "../sdlwrap/SdlTexture.h"

class Explotion{
private:
	SdlTexture& texture;
	int numFrames;
	int frameSize;
	float elapsed;
	int currFrame;
	bool shouldBlow;

	void advanceFrame();
public:
	Explotion(SdlTexture& texture);

	void update(float dt);
	void render(const Area& dst, const SDL_RendererFlip& flip);

	~Explotion();
};

#endif