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
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

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
    if (this->texture != nullptr){
        SDL_DestroyTexture(this->texture);
    }
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

int SdlTexture::render(const Area &src, const Area &dest, float angle, SDL_Point &center,
                       const SDL_RendererFlip &flip) const {
    const SDL_Rect srcRect = src.buildRectangle();
    const SDL_Rect destRect = dest.buildRectangle();
    return window.handleRender(texture, srcRect, destRect, angle, center, flip);
}

SdlTexture::SdlTexture(SdlTexture &&other)
: window(other.window),
  texture(other.texture){
    other.texture = nullptr;
    this->width = other.width;
    this->height = other.height;
}

SdlTexture::SdlTexture(const std::string &filename, SdlWindow &window, Color key, Color surfaceColor)
: window(window),
  texture(nullptr){
    SDL_Surface* tmp = IMG_Load(filename.c_str());
    if (!tmp){
        return;
    }

    SDL_SetSurfaceColorMod(tmp, surfaceColor.r, surfaceColor.g, surfaceColor.b);
    SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, key.r, key.g, key.b));

    this->texture = window.createTexture(tmp);

    width = tmp->w;
    height = tmp->h;

    SDL_FreeSurface(tmp);

}

int SdlTexture::render(const Area &src, const Area &dest, uint8_t alpha) const {
    return window.handleRender(texture, src.buildRectangle(), dest.buildRectangle(), alpha);
}

void SdlTexture::changeColor(Color color) {
    SDL_SetTextureColorMod(this->texture, color.r, color.g, color.b);
}

SdlTexture &SdlTexture::operator=(SdlTexture &&other)  {
    if (this == &other){
        return *this;
    }

    if (texture != nullptr){
        SDL_DestroyTexture(texture);
    }

    texture = other.texture;
    other.texture = nullptr;

    this->width = other.width;
    this->height = other.height;
    return *this;
}
