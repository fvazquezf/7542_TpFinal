#include "Animation.h"

Animation::Animation(const SdlTexture &texture, int numFrames, int size)
: texture(texture),
  currentFrame(0),
  numFrames(numFrames),
  size(size),
  elapsed(0.0){
}

Animation::~Animation(){

}

void Animation::update(float dt){
	elapsed += dt;

	while (elapsed > FRAMERATE){
		advanceFrame();
		elapsed -= FRAMERATE;
	}
}

void Animation::advanceFrame(){
	++currentFrame;
	currentFrame %= numFrames;
}

void Animation::render(const Area &src, const Area &dst, const SDL_RendererFlip &flipType) {
    render(src, dst, 0, flipType);
}

void Animation::render(const Area &src, const Area &dst, float angle, const SDL_RendererFlip &flipType) {
    texture.render(src, dst, angle, flipType);
}
