#ifndef AREA_H
#define AREA_H

#include <SDL2/SDL.h>

class Area{
private:
	int x;
	int y;
	int width;
	int height;
public:
	Area(int x, int y, int width, int height);

	Area(const Area& other) = delete;
	const Area& operator=(const Area& other) = delete;
	
	SDL_Rect buildRectangle() const;

	~Area();
};


#endif