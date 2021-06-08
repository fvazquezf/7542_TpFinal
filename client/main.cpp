#include <unistd.h>

#include "sdlwrap/SdlWindow.h"
#include "sdlwrap/SdlTexture.h"
#include "sdlwrap/Area.h"
#include <chrono>
#include "anim/Terrorist.h"
#include "anim/Animation.h"


int main(int argc, char const *argv[]){
	SdlWindow w(800, 600, false, "unaVentana");
	SdlTexture terroristTex("../sprites/gfx/player/t1.bmp", w);
	Terrorist terrorist(terroristTex, 200, 200);

	bool running = true;

	w.fill();
	terrorist.render();
	w.render();

	SDL_Event e;
	while (running){
		auto start = std::chrono::system_clock::now();
		while (SDL_PollEvent(&e)){
			switch(e.type){
                case SDL_MOUSEMOTION:
                    terrorist.scroll();
                    break;
			    case SDL_MOUSEBUTTONDOWN:
                    terrorist.gunAction();
                    break;
			    case SDL_MOUSEBUTTONUP:
			        terrorist.stopGunAction();
			        break;
				case SDL_KEYDOWN:{
					auto& keyEvent = (SDL_KeyboardEvent&) e;
		            switch (keyEvent.keysym.sym) {
		                case SDLK_LEFT:
		                    terrorist.moveLeft();
		                    break;
		                case SDLK_RIGHT:
		                    terrorist.moveRight();
		                    break;
		                case SDLK_UP:
		               		terrorist.moveUp(); 
		               		break;
		               	case SDLK_DOWN:
		               		terrorist.moveDown();
		               		break;
		               	}
	                break;
	            } // Fin KEY_DOWN
                case SDL_KEYUP:{
                	terrorist.stopMoving();
	               	break;
 				}
				case SDL_QUIT:
					running = false;
					break;
            }
        }
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<float, std::micro> elapsed = (end - start);

		w.fill();
        terrorist.update(FRAMERATE + elapsed.count());
        terrorist.render();
        w.render();

        usleep(FRAMERATE + elapsed.count());
    }
	return 0;	
}
