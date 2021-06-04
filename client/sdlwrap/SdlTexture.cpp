#include "SdlTexture.h"
#include "Area.h"
#include <utility>


SdlTexture::SdlTexture(const std::string& filename, SdlWindow& window)
: window(window), 
  texture(nullptr){
	SDL_Surface* tmp = IMG_Load(filename.c_str());
	if (!tmp){
		return;
	}

	this->texture = window.createTexture(tmp);

	width = tmp->w;
	height = tmp->h;

	SDL_FreeSurface(tmp);
}

int SdlTexture::render(const Area& src, const Area& dest, const SDL_RendererFlip& flipType) const{
	return render(src, dest, 0, flipType);
}

int SdlTexture::render(const Area& src, const Area& dest, float angle, const SDL_RendererFlip& flipType) const{
	const SDL_Rect srcRect = std::move(src.buildRectangle());
	const SDL_Rect destRect = std::move(dest.buildRectangle());
	return window.handleRender(texture, srcRect, destRect, angle, flipType);
}


SdlTexture::~SdlTexture(){
	SDL_DestroyTexture(this->texture);
}
