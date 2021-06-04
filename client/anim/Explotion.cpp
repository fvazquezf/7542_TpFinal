#include "Explotion.h"
#include <iostream>


Explotion::Explotion(SdlTexture& texture)
: texture(texture),
  numFrames(23), 
  frameSize(64), 
  elapsed(0.0),
  currFrame(0),
  shouldBlow(true){
}

void Explotion::advanceFrame(){
	++currFrame;	
	currFrame %= numFrames;
}

Explotion::~Explotion(){
}

void Explotion::render(const Area& dst, const SDL_RendererFlip& flip){
	if (shouldBlow){
		int y = 0;
		y = (currFrame / 5) * frameSize;
		Area src((frameSize * (currFrame % 5)), y, frameSize, frameSize);
		texture.render(src, dst, SDL_FLIP_NONE);
	}
}

void Explotion::update(float dt){
	elapsed += dt;	
	if (elapsed > FRAMERATE){
		advanceFrame();
		elapsed -= FRAMERATE;
	}
}
