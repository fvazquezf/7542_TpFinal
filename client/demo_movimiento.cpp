#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>

#include "../libs/box2d/include/box2d/box2d.h"

#include "sdlwrap/SdlWindow.h"
#include "sdlwrap/SdlTexture.h"
#include "sdlwrap/Area.h"
#include "anim/Explotion.h"

b2Body* createBody(b2World& world){
    b2BodyDef anchorDef;
	anchorDef.position.Set(0.0f, -10.0f);
	
	b2Body* anchor = world.CreateBody(&anchorDef);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	b2Body* body = world.CreateBody(&bodyDef);

	b2PolygonShape bodyBox;
	bodyBox.SetAsBox(0.25f, 0.25f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &bodyBox;
	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	b2FrictionJointDef fJointDef;
	fJointDef.bodyA = anchor;
	fJointDef.bodyB = body;

	b2FrictionJoint* fJoint = (b2FrictionJoint*)world.CreateJoint(&fJointDef);
	fJoint->SetMaxForce(15);

    return body;
}


int main(int argc, char const *argv[]){
	SdlWindow w(800, 600, false, "unaVentana");
	SdlTexture t("../sprites/gfx/player/ct1.bmp", w);
	// Explotion exp(t);

	bool running = true;
	
	Area src(0, 0, 64, 64);
	Area dest(200, 200, 64, 64);
	w.fill();
	t.render(src, dest, SDL_FLIP_NONE);
	w.render();
	SDL_Event e;

	b2Vec2 gravity(0.0f, 0.0f);
	b2World world(gravity);

    b2Body* body = createBody(world);

	b2Vec2 f1(0, -100);

    // Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	while (running){
		while (SDL_WaitEvent(&e)){
			if (e.type == SDL_MOUSEBUTTONUP){
				body->ApplyForceToCenter(f1, true);			 
			}
			if (e.type == SDL_QUIT){
				running = false;
				break;
			}
		}
        world.Step(timeStep, velocityIterations, positionIterations);
        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle();

        Area src(0, 0, 64, 64);
        Area dest(position.x + 150, position.y + 150, 64, 64);

        w.fill();
        t.render(src, dest, SDL_FLIP_NONE);
        w.render();

        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);	
	}
	SDL_Quit();
	return 0;	
}

