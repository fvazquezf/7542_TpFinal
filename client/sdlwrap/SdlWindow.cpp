#include <iostream>
#include "SdlWindow.h"


SdlWindow::SdlWindow(int width, int height, bool full, std::string title){
	int err = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
	if (err){
		//handle
	}

    err = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	if (err){
	    // handle
	}

	err = SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED,
										  &this->windowPtr, &this->rendererPtr);
	if (err){
		// handle
	}

	SDL_SetWindowTitle(this->windowPtr, title.c_str());

	if (full){
		SDL_SetWindowFullscreen(this->windowPtr, SDL_WINDOW_FULLSCREEN);
	}
	this->width = width;
    this->height = height;
}

SdlWindow::~SdlWindow(){
	if (this->rendererPtr){
		SDL_DestroyRenderer(this->rendererPtr);
		rendererPtr = nullptr;
	}

	if (this->windowPtr){
		SDL_DestroyWindow(this->windowPtr);
		windowPtr = nullptr;
	}
    Mix_Quit();
	SDL_Quit();
}

void SdlWindow::fill(uint8_t r, uint8_t g, uint8_t b, int alpha){
	SDL_SetRenderDrawColor(rendererPtr, r, g, b, alpha);
	SDL_RenderClear(rendererPtr);
}

void SdlWindow::fill(){
	fill(0, 0, 0, 0);
}

void SdlWindow::render(){
	SDL_RenderPresent(rendererPtr);
}

SDL_Texture* SdlWindow::createTexture(SDL_Surface* aSurface){
	return SDL_CreateTextureFromSurface(rendererPtr, aSurface);
}

int SdlWindow::handleRender(SDL_Texture* txt,
							const SDL_Rect& src,
							const SDL_Rect& dst,
							float ang,
							SDL_RendererFlip flip){
	return SDL_RenderCopyEx(rendererPtr, txt, &src, &dst, ang, nullptr, flip);
}

SDL_Point SdlWindow::getCenter(){
	SDL_Point p;
	SDL_GetWindowSize(windowPtr, &p.x, &p.y);
	p.x /= 2;
	p.y /= 2;
	return p;
}


int SdlWindow::getWidth(){
	return width;
}

int SdlWindow::getHeight(){
	return height;
}

int SdlWindow::handleRender(SDL_Texture *txt, const SDL_Rect &src, const SDL_Rect &dst, float ang, SDL_Point &center,
                            SDL_RendererFlip flip) {
    return SDL_RenderCopyEx(rendererPtr, txt, &src, &dst, ang, &center, flip);
}

int SdlWindow::handleRender(SDL_Texture *txt, const SDL_Rect &src, const SDL_Rect &dst, uint8_t alpha) {
    SDL_SetTextureAlphaMod(txt, alpha);
    return SDL_RenderCopyEx(rendererPtr, txt, &src, &dst, 0, nullptr, SDL_FLIP_NONE);
}

int SdlWindow::drawCenteredTriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint8_t r, uint8_t g, uint8_t b,
                                    uint8_t alpha) {
    return filledTrigonRGBA(rendererPtr,
                            x1,
                            y1,
                            x2,
                            y2,
                            x3, y3, 0xff, 0xff, 0xff, 25);
}
