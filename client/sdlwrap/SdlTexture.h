#ifndef SDLTEXTURE_H
#define SDLTEXTURE_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include "SdlWindow.h"
#include "Area.h"
#include "common/Exception.h"

struct Color {
    uint8_t r, g, b;
};

class SdlTexture {
private:
	SdlWindow& window;
	SDL_Texture* texture;

	int width;
	int height;

public:
	SdlTexture(const std::string& filename, SdlWindow& window);
    SdlTexture(const std::string &filename,
               SdlWindow& window,
               Color key);

    SdlTexture(const std::string &filename,
               SdlWindow& window,
               Color key,
               SDL_BlendMode blending,
               uint8_t alpha);

    SdlTexture(const std::string& filename,
               SdlWindow& window,
               Color key,
               Color surfaceColor);


    SdlTexture(const SdlTexture& other) = delete;
    SdlTexture& operator=(const SdlTexture& other) = delete;

    SdlTexture(SdlTexture&& other) ;
    SdlTexture& operator=(SdlTexture&& other) ;

	int render(const Area& src, const Area& dest, const SDL_RendererFlip& flipType) const;
    int render(const Area& src, const Area& dest, uint8_t alpha) const;
    int render(const Area& src, const Area& dest, float angle, const SDL_RendererFlip& flip) const;
    int render(const Area& src, const Area& dest, float angle, SDL_Point& center, const SDL_RendererFlip& flip) const;
    void changeColor(Color color);

	~SdlTexture();
};

#endif
