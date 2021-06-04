#include <iostream>
#include <string>
#include <unistd.h>

#include "sdlwrap/SdlWindow.h"
#include "sdlwrap/SdlTexture.h"
#include "sdlwrap/Area.h"
#include "anim/Explotion.h"


int main(int argc, char const *argv[]){
	SdlWindow w(800, 600, false, "unaVentana");
	SdlTexture t("../../sprites/gfx/explosion.png", w);
	Explotion exp(t);

	bool running = true;

	Area dest(200, 200, 64, 64);

	w.fill();
	w.render();

	float ft = 0;
	SDL_Event e;
	while (running){
		// wait event, poll event nos va a quemar la cpu
		while (SDL_WaitEvent(&e)){
			if (e.type == SDL_MOUSEBUTTONUP){
				while (ft < 22 * FRAMERATE){
					int x, y;
					SDL_GetMouseState(&x, &y);
					Area dest(x - 32, y - 32, 64, 64);
					w.fill();
					exp.render(dest, SDL_FLIP_NONE);
					exp.update(FRAMERATE);
					w.render();
					ft += FRAMERATE;
					usleep(FRAMERATE);
				}
				ft = 0;
				w.fill();
				w.render();
			}
			if (e.type == SDL_QUIT){
				running = false;
				break;
			}
		}
	}

	SDL_Quit();
	return 0;	
}

