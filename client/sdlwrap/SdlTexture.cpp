#include "SdlTexture.h"
#include "Area.h"


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
	const SDL_Rect srcRect = src.buildRectangle();
	const SDL_Rect destRect = dest.buildRectangle();
	return window.handleRender(texture, srcRect, destRect, angle, flipType);
}


SdlTexture::~SdlTexture(){
	SDL_DestroyTexture(this->texture);
}

SdlTexture::SdlTexture(const std::string &filename, SdlWindow &window, Color key)
: window(window),
  texture(nullptr){
    SDL_Surface* tmp = IMG_Load(filename.c_str());
    if (!tmp){
        return;
    }

    SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, key.r, key.g, key.b));

    this->texture = window.createTexture(tmp);

    width = tmp->w;
    height = tmp->h;

    SDL_FreeSurface(tmp);
}

SdlTexture::SdlTexture(const std::string &filename, SdlWindow &window, Color key, SDL_BlendMode blending,
                       uint8_t alpha)
: SdlTexture(filename, window, key){
    SDL_SetTextureBlendMode(this->texture, blending);
    SDL_SetTextureAlphaMod(this->texture, alpha);
}
