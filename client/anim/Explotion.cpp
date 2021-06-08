#include "Explotion.h"
#include <iostream>


Explotion::Explotion(const SdlTexture& texture, int dstX, int dstY)
: animation(texture, 23, 64),
  shouldBlow(true),
  dstX(dstX),
  dstY(dstY){

}

Explotion::~Explotion(){
}

void Explotion::render(){
	if (shouldBlow){
	    /*animation.render();
		Area src((64 * (currentFrame % 5)), (currentFrame / 5) * size, size, size);
		Area dest(dstx, dsty, size, size);
		texture.render(src, dest, flipType);
		if (numFrames == currentFrame){
			shouldBlow = false;
		}*/
	}
}