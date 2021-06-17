#include "WorldModel.h"
#include "PlayerModel.h"
#include <stdlib.h>

#include "../libs/box2d/include/box2d/box2d.h"

WorldModel::WorldModel(): world (b2Vec2(0.0f, 0.0f)){
	this->timeStep = 1.0f / 60.0f;
	this->velocityIterations = 6;
	this->positionIterations = 2;


    b2BodyDef anchorDef;
	anchorDef.position.Set(0.0f, -10.0f);
	
	this->anchor = world.CreateBody(&anchorDef);
}

PlayerModel& WorldModel::createPlayer(float x, float y, std::string clave){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
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
	fJointDef.bodyA = this->anchor;
	fJointDef.bodyB = body;

	b2FrictionJoint* fJoint = (b2FrictionJoint*)world.CreateJoint(&fJointDef);
	fJoint->SetMaxForce(10);

    PlayerModel player(body);

	this->playerModels[clave] = player; 

	return this->playerModels[clave];
}

PlayerModel& WorldModel::addPlayer(std::string clave){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(std::rand()%50, std::rand()%50);
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
	fJointDef.bodyA = this->anchor;
	fJointDef.bodyB = body;

	b2FrictionJoint* fJoint = (b2FrictionJoint*)world.CreateJoint(&fJointDef);
	fJoint->SetMaxForce(10);

    PlayerModel player(body);

	this->playerModels[clave] = player; 

	return this->playerModels[clave];
}


void WorldModel::createBox(b2BodyDef& boxDef){
	b2Body* box = this->world.CreateBody(&boxDef);
    b2PolygonShape bodyBox;
	bodyBox.SetAsBox(1.0f, 1.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &bodyBox;
    box->CreateFixture(&fixtureDef);
}

void WorldModel::loadMap(){
	b2BodyDef boxDef;
	boxDef.type = b2_staticBody;
	float x = -20;
	float y = 20;

	for (int i = 0; i<20 ; i++){
		boxDef.position.Set(x, y);
		this->createBox(boxDef);

		boxDef.position.Set(x, -y);
		this->createBox(boxDef);

		x = x + 2;
	}
	y = y - 2;
	for (int i = 0; i<19 ; i++){
		boxDef.position.Set(x, y);
		this->createBox(boxDef);

		boxDef.position.Set(-x, y);
		this->createBox(boxDef);

		y = y - 2;
	}
}


void WorldModel::step(){
	for (auto it = this->playerModels.begin(); it != this->playerModels.end(); it++){
		it->second.step();
	}
	this->world.Step(this->timeStep, this->velocityIterations, this->positionIterations);
}

