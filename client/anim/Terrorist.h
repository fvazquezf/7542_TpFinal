#ifndef TERRORIST_H
#define TERRORIST_H
#include "Renderizable.h"

class Terrorist : public Renderizable {
private:
    //Animation animation;
	float posX;
	float posY;
    bool player;
	/*bool movingLeft;
	bool movingRight;
	bool movingUp;
	bool movingDown;
	bool scrolling;
	bool shooting;*/
	float angle;
	//float knifeAngle;
public:
	Terrorist(SdlTexture& texture, float posX, float posY, bool player);

	//void moveLeft();
	//void moveRight();
	//void moveUp();
	//void moveDown();
	//void scroll();
    //void gunAction();
	//void stopMoving();

	void render();
    void render(Camera& cam) override;
	//void update(float dt);
	void update() override;
	~Terrorist() override;

    //void stopGunAction();
};

#endif
