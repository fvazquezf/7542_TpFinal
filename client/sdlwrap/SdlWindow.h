#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfxPrimitives.h>

class SdlWindow {
private:
	int width;
	int height;
	SDL_Window* windowPtr;
	SDL_Renderer* rendererPtr;

public:
	SdlWindow(int width, int height, bool full, std::string title);

	SdlWindow(const SdlWindow& other) = delete;
	SdlWindow& operator=(const SdlWindow& other) = delete;

	void fill();
	void fill(uint8_t r, uint8_t g, uint8_t b, int alpha);

	void render();

	SDL_Texture* createTexture(SDL_Surface* aSurface);
	int handleRender(SDL_Texture* txt, const SDL_Rect& src,
					 const SDL_Rect& dst, float ang,
					 SDL_RendererFlip flip);

    int handleRender(SDL_Texture* txt, const SDL_Rect& src,
                     const SDL_Rect& dst, float ang,
                     SDL_Point& center,
                     SDL_RendererFlip flip);

    int handleRender(SDL_Texture* txt,
                     const SDL_Rect& src,
                     const SDL_Rect& dst,
                     uint8_t alpha);

    //int drawCircle(std::pair<int16_t, int16_t> x1, );
    int drawCenteredTriangle(int16_t x1,
                             int16_t y1,
                             int16_t x2,
                             int16_t y2,
                             int16_t x3,
                             int16_t y3,
                             uint8_t r,
                             uint8_t g,
                             uint8_t b,
                             uint8_t alpha);

	SDL_Point getCenter();

	int getWidth();
	int getHeight();

	~SdlWindow();
};

#endif
