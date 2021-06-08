#ifndef TERRORIST_H
#define TERRORIST_H
#include "../sdlwrap/SdlTexture.h"
#include "Animation.h"


class Terrorist {
private:
    Animation animation;
	int posX;
	int posY;
	bool movingLeft;
	bool movingRight;
	bool movingUp;
	bool movingDown;
	bool scrolling;
	bool shooting;
	float angle;
	float knifeAngle;
public:
	Terrorist(SdlTexture& texture, int posX, int posY);

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void scroll();
    void gunAction();
	void stopMoving();

	void render();
	void update(float dt);
	~Terrorist();

    void stopGunAction();
};

#endif