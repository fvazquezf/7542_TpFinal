#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>

#include "../libs/box2d/include/box2d/box2d.h"

#include "sdlwrap/SdlWindow.h"
#include "sdlwrap/SdlTexture.h"
#include "sdlwrap/Area.h"
#include "anim/Explotion.h"


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

	// float ft = 0;
	SDL_Event e;

		// wait event, poll event nos va a quemar la cpu
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	// Define the gravity vector.
	b2Vec2 gravity(0.0f, 0.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(gravity);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	
	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(50.0f, 10.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	b2Body* body = world.CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.25f, 0.25f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	b2FrictionJointDef fJointDef;
	fJointDef.bodyA = groundBody;
	fJointDef.bodyB = body;

	b2FrictionJoint* fJoint = (b2FrictionJoint*)world.CreateJoint(&fJointDef);
	
	
	fJoint->SetMaxForce(15);

	b2Vec2 f1(0, -20.25);

	int i = 0;
	while (running){
		while (SDL_WaitEvent(&e)){
			if (i < 240){
				if (i < 120)	body->ApplyForceToCenter(f1, true);
				// Instruct the world to perform a single step of simulation.
				// It is generally best to keep the time step and iterations fixed.
				world.Step(timeStep, velocityIterations, positionIterations);

				// Now print the position and angle of the body.
				b2Vec2 position = body->GetPosition();
				float angle = body->GetAngle();

				Area src(0, 0, 64, 64);
				Area dest(position.x + 150, position.y + 150, 64, 64);

				w.fill();
				t.render(src, dest, SDL_FLIP_NONE);
				w.render();

				printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
				
				if (e.type == SDL_QUIT){
					running = false;
					break;
				}
				 
			}
			i++;
			if (e.type == SDL_QUIT){
				running = false;
				break;
			}
		}
	}
	SDL_Quit();
	return 0;	
}

