#include "WorldModel.h"
#include "PlayerModel.h"
#include <cstdlib>
#include <chrono>
#include <unistd.h>
#include <utility>

#define FRAMERATE 1000000/60.0f

#include "../libs/box2d/include/box2d/box2d.h"
#include "updates/PositionUpdate.h"
#include "updates/AngleUpdate.h"
#include "updates/AttackUpdate.h"
#include "updates/HitUpdate.h"
#include "updates/DeadUpdate.h"
#include "updates/WeaponUpdate.h"
#include "updates/BuyTimeUpdate.h"
#include "updates/TeamsUpdate.h"

WorldModel::WorldModel(Broadcaster& updates, const std::map<int, float>& matchConfig)
: world (b2Vec2(0.0f, 0.0f)),
  matchConfig(matchConfig),
  updates (updates),
  droppedWeapons(updates){
	this->timeStep = 1.0f / 60.0f;
	this->velocityIterations = 6;
	this->positionIterations = 2;


    b2BodyDef anchorDef;
	anchorDef.position.Set(0.0f, -10.0f);
	
	this->anchor = world.CreateBody(&anchorDef);

	is_running = false;
	purchaseFase = true;
}

WorldModel::~WorldModel() {

}

WorldModel::WorldModel(WorldModel &&other) noexcept
: world(b2Vec2(0.0f, 0.0f)),
  matchConfig(other.matchConfig),
  playerModels(std::move(other.playerModels)),
  usersEvents(std::move(other.usersEvents)),
  updates(other.updates),
  droppedWeapons(std::move(other.droppedWeapons)),
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

void WorldModel::stop() {
    is_running = false;
}

ProtectedQueue<std::unique_ptr<ClientEvent>>& WorldModel::addPlayer(int clave){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(std::rand()%50, std::rand()%50);
	b2Body* body = world.CreateBody(&bodyDef);

	b2CircleShape bodyCircle;
	bodyCircle.m_radius = 0.25f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &bodyCircle;
	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	b2FrictionJointDef fJointDef;
	fJointDef.bodyA = this->anchor;
	fJointDef.bodyB = body;

	b2FrictionJoint* fJoint = (b2FrictionJoint*)world.CreateJoint(&fJointDef);
	fJoint->SetMaxForce(10);

	playerModels.emplace(std::piecewise_construct,
                         std::forward_as_tuple(clave),
                         std::forward_as_tuple(body, droppedWeapons));

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
    for (int i = 0; i < (int)playerModels.size()/2; i++){
        playerModels.at(i).changeSide();
    }
    updateTeams();
    for (auto & playerModel : this->playerModels){
		tally.placeInTeam(playerModel.first, playerModel.second.getSide());
	}
    while (is_running){
		purchaseFase = true;
        roundBegin();
		purchaseFase = false;
        roundPlay();
		stopAllPlayers();
        // checkGameDone() -> checkea si termino la partida, si termino, is_running = false
    }
    // roundEnd() -> envia info de la partida, cierra a los clientes, etc etc
}

void WorldModel::roundBegin() {
    // 600 ticks, 10 segundos a 60 ticks cada segundo
    updateBuying(true);
    // sleep ? esperamos un poquitito antes de contar
    for (auto & playerModel : this->playerModels){
		playerModel.second.reposition(mapLayout);
	}
    updatePositions();
    usleep(FRAMERATE);
    for (size_t i = 0; i < 600; ++i){
        roundCommon();
    }
    updateBuying(false);

}

// checkea si termino la ronda
// x casos:
// 1 - murieron todos los cts -> ganan tts
// 2 - murieron todos los tts (y no plantaron) -> ganan cts
// 3 - se termino el tiempo (ganan los cts pq es de plantar la bomba)
// 4 - exploto la bomba -> ganan tts
// 5 - defusearon la bomba -> ganan cts
bool WorldModel::roundDone() {
    return false;
}

void WorldModel::roundPlay() {
    // no queremos ningun evento residual
    usersEvents.clear();
    for (size_t i = 0; i < 3600 && !roundDone(); ++i){
        roundCommon();
    }
}

void WorldModel::roundCommon() {
    auto start = std::chrono::system_clock::now();
    for (int j = 0; j < 50; ++j){
        try {
            std::unique_ptr<ClientEvent> event = usersEvents.pop();
            event->updatePlayer(*this);
        }
        catch (const std::invalid_argument& e){
            continue;
        }
    }
    this->step();
    
    updatePositions();
    
    updateAngles();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<float, std::micro> elapsed = (end - start);
    usleep(FRAMERATE + elapsed.count());
}

void WorldModel::step(){
	for (auto & playerModel : this->playerModels){
		playerModel.second.step();
	}
	for (auto id: attackingPlayers){
	    // el atacante
	    auto& attacker = playerModels.at(id);
		for (auto& it : playerModels){
		    // esta condicion es para que no se ataque a si mismo
		    if (&it.second != &attacker){
                if ( playerModels.at(id).attack(it.second) ){
                    if (it.second.gotHit(playerModels.at(id).hit())){
                        it.second.die();
                        updateDead(it.first);
                    } else {
                        updateHit(it.first);
                    }
                }
		    }
		}
		if (playerModels.at(id).tickCooldown()){
			updateAttack(id);
		}
	}
	this->world.Step(this->timeStep, this->velocityIterations, this->positionIterations);
}

void WorldModel::updatePositions() {
    std::map<uint8_t, std::pair<float, float>> newPos;
    for (auto & playerModel : playerModels){
        int id = playerModel.first;
        b2Vec2 pos = playerModel.second.getPosition();
        newPos[id] = std::pair<float, float>(pos.x, pos.y);
    }
    std::shared_ptr<Update> updatePtr(new PositionUpdate(std::move(newPos)));
    updates.pushAll(updatePtr);
}

void WorldModel::updateAngles() {
    std::map<uint8_t, int16_t> angles;
    for (auto& it : playerModels){
        angles.insert({it.first, it.second.getAngle()});
    }
    std::shared_ptr<Update> updatePtr(std::shared_ptr<Update>(new AngleUpdate(std::move(angles))));
    updates.pushAll(updatePtr);
}

void WorldModel::updateAttack(int id){
	std::shared_ptr<Update> updatePtr(new AttackUpdate(id));
    updates.pushAll(updatePtr);
}

void WorldModel::updateHit(int id){
	std::shared_ptr<Update> updatePtr(new HitUpdate(id));
    updates.pushAll(updatePtr);
}

void WorldModel::updateDead(int id){
	std::shared_ptr<Update> updatePtr(new DeadUpdate(id));
    updates.pushAll(updatePtr);
}

void WorldModel::updateWeapon(uint8_t id, uint8_t weaponType){
	std::shared_ptr<Update> updatePtr(new WeaponUpdate(id, weaponType));
    updates.pushAll(updatePtr);
}

void WorldModel::updateBuying(bool buying) {
    updates.pushAll(std::shared_ptr<Update>(new BuyTimeUpdate(buying)));
}

void WorldModel::updateTeams(){
    std::map<uint8_t, bool> teams;
    for (auto & playerModel : playerModels){
        int id = playerModel.first;
        bool team = playerModel.second.getSide();
        teams[id] = team;
    }
    std::shared_ptr<Update> updatePtr(new TeamsUpdate(std::move(teams)));
    updates.pushAll(updatePtr);
}

void WorldModel::movePlayer(uint8_t id, uint8_t dir) {
	if (purchaseFase) return;
    playerModels.at(id).startMove(dir);
}

void WorldModel::stopMovingPlayer(uint8_t id, uint8_t dir) {
	if (purchaseFase) return;
    playerModels.at(id).stopMove(dir);
}

void WorldModel::stopAllPlayers(){
	for (auto& it : playerModels){
        it.second.stopMove(5);
    }
	attackingPlayers.clear();
}

void WorldModel::rotatePlayer(uint8_t id, int16_t angle) {
    playerModels.at(id).setAngle(angle);
}

void WorldModel::startAttack(uint8_t id){
	if (purchaseFase) return;
	attackingPlayers.insert(id);
}

void WorldModel::stopAttack(uint8_t id){
	if (purchaseFase) return;
	attackingPlayers.erase(id);
	playerModels.at(id).resetCooldown();
}

void WorldModel::equipWeapon(uint8_t id, uint8_t weaponType){
    int weaponId = -1;
	if ((weaponId = playerModels.at(id).equipWeapon(weaponType)) != -1){
		updateWeapon(id, weaponId);
	}
}

void WorldModel::buyWeapon(uint8_t id, uint8_t weaponCode) {
    if (playerModels.at(id).buyWeapon(weaponCode)){
		// el weaponType = 0 es el de arma primaria
		// solo podes comprar armas primarias, asi que si compraste equipas la primaria
		equipWeapon(id, 0);
    }
}

void WorldModel::pickUpWeapon(uint8_t id){
	if (playerModels.at(id).pickUpWeapon()){
		// el weaponType = 0 es el de arma primaria
		// solo podes comprar armas primarias, asi que si compraste equipas la primaria
		equipWeapon(id, 0);
    }
}

void WorldModel::disconnectPlayer(uint8_t id) {
    // primero, hacemos que haga drop de todas sus armas
    // aca vendria el drop si estuviese implementado
    // luego, le decimos al broadcaster que cierre su q
    // de esa manera mata al sender
    // hasta este punto del recorrido, receiver murio, sender esta vivo
    updates.closePlayerQueue(id);
    // una vez cerrado, se lo borra de aca
    // deberia mandarse un update al resto de los jugadores
}
