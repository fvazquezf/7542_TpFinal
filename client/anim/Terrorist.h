#ifndef TERRORIST_H
#define TERRORIST_H
#include "Renderizable.h"

class Terrorist : public Renderizable {
private:
    bool player;
public:
	Terrorist(SdlTexture& texture, float posX, float posY, bool player);

    void render(Camera& cam) override;
	void update() override;
	~Terrorist() override;
};

#endif
