#ifndef SDLTEXTURE_H
#define SDLTEXTURE_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include "SdlWindow.h"
#include "Area.h"

class SdlTexture {
private:
	SdlWindow& window;
	SDL_Texture* texture;

	int width;
	int height;

public:
	SdlTexture(const std::string& filename, SdlWindow& window);

	int render(const Area& src, const Area& dest, const SDL_RendererFlip& flipType) const;
    int render(const Area& src, const Area& dest, float angle, const SDL_RendererFlip& flip) const;
    
	~SdlTexture();
};


#endif