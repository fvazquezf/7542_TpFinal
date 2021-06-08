#include "SdlWindow.h"


SdlWindow::SdlWindow(int width, int height, bool full, std::string title){
	int err = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if (err){
		//handle
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
	SDL_Quit();
}

void SdlWindow::fill(uint8_t r, uint8_t g, uint8_t b, int alpha){
	SDL_SetRenderDrawColor(rendererPtr, r, g, b, alpha);
	SDL_RenderClear(rendererPtr);
}

void SdlWindow::fill(){
	fill(0x33, 0x33, 0x33, 0);
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
