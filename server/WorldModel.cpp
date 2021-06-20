#include "WorldModel.h"
#include "PlayerModel.h"
#include "updates/PositionUpdate.h"
#include <cstdlib>
#include <chrono>
#include <unistd.h>

#define FRAMERATE 1000000/60.0f

#include "../libs/box2d/include/box2d/box2d.h"

WorldModel::WorldModel(Broadcaster& updates): world (b2Vec2(0.0f, 0.0f)),
updates (updates){
	this->timeStep = 1.0f / 60.0f;
	this->velocityIterations = 6;
	this->positionIterations = 2;


    b2BodyDef anchorDef;
	anchorDef.position.Set(0.0f, -10.0f);
	
	this->anchor = world.CreateBody(&anchorDef);

	is_running = false;
}

PlayerModel& WorldModel::createPlayer(float x, float y, int clave){
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

    //PlayerModel player(body);

    playerModels.emplace(std::piecewise_construct,
                         std::forward_as_tuple(clave),
                         std::forward_as_tuple(body));

	return this->playerModels[clave];
}

ProtectedQueue<std::unique_ptr<ClientEvent>>& WorldModel::addPlayer(int clave){
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

    //PlayerModel player(body);

	//this->playerModels[clave] = player;

	// crea un player model asi
	playerModels.emplace(std::piecewise_construct,
                         std::forward_as_tuple(clave),
                         std::forward_as_tuple(body));

	return std::ref(this->usersEvents);
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

void WorldModel::run(){
	is_running = true;
	playerModels.at(0).reposition(50.0f, 50.0f);
    playerModels.at(1).reposition(51.0f, 51.0f);


	while (is_running){
        auto start = std::chrono::system_clock::now();
		for (int i = 0; i<10; i++){
			try {
				std::unique_ptr<ClientEvent> event = usersEvents.pop();
				event->updatePlayer(this->playerModels);
			}
			catch (const std::invalid_argument& e){
				continue;
			}
		}
		this->step();
		
		std::map<uint8_t, std::pair<float, float>> newPos;
		for (auto it = this->playerModels.begin(); it != this->playerModels.end(); it++){
			int id = it->first;
			b2Vec2 pos = it->second.getPosition();
			newPos[id] = std::pair<float, float>(pos.x, pos.y);
		}
		std::shared_ptr<PositionUpdate> updatePtr(new PositionUpdate(newPos));
		updates.pushAll(updatePtr);
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<float, std::micro> elapsed = (end - start);
        usleep(FRAMERATE + elapsed.count());
    }
}


void WorldModel::step(){
	for (auto it = this->playerModels.begin(); it != this->playerModels.end(); it++){
		it->second.step();
	}
	this->world.Step(this->timeStep, this->velocityIterations, this->positionIterations);
}

WorldModel::~WorldModel() {

}

WorldModel::WorldModel(WorldModel &&other) noexcept
: world(b2Vec2(0.0f, 0.0f)),
  playerModels(std::move(other.playerModels)),
  usersEvents(std::move(other.usersEvents)),
  updates(other.updates),
  timeStep(other.timeStep),
  velocityIterations(other.velocityIterations),
  positionIterations(other.positionIterations),
  is_running(other.is_running){
    // tengo que crearlo asi pq
    // en box2d el world
    // no tiene construccion por movimiento
    // ni por copia
    b2BodyDef anchorDef;
    anchorDef.position.Set(0.0f, -10.0f);
    this->anchor = world.CreateBody(&anchorDef);
}

WorldModel &WorldModel::operator=(WorldModel &&other) noexcept {
    if (this == &other){
        return *this;
    }

    return *this;
}

