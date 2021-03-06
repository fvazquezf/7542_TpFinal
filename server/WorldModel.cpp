#include "WorldModel.h"
#include "PlayerModel.h"
#include "weapons/Armory.h"
#include <cstdlib>
#include <chrono>
#include <unistd.h>
#include <utility>
#include <updates/GameDoneUpdate.h>
#include "yaml-cpp/yaml.h"

#define FRAMERATE 1000000/60.0f

#include "../libs/box2d/include/box2d/box2d.h"

#include "../common/ConfigVariables.h"

WorldModel::WorldModel(Broadcaster& updates, const std::map<int, int>& matchConfig)
: world (b2Vec2(0.0f, 0.0f)),
  matchConfig(matchConfig),
  bomb (std::shared_ptr<Bomb> (new Bomb(matchConfig.at(BOMB_RANGE),
                                        matchConfig.at(BOMB_ACCURACY),
                                        matchConfig.at(BOMB_DAMAGE),
                                        matchConfig.at(BOMB_FIRERATE),
                                        matchConfig.at(BOMB_FUSE),
                                        matchConfig.at(BOMB_ACTIVATE_TIME),
                                        matchConfig.at(BOMB_BOUNTY)))),
  tally(bomb),
  updates (updates),
  updatesM(updates, playerModels),
  droppedWeapons(updates) {
	this->timeStep = 1.0f / 60.0f;
	this->velocityIterations = 6;
	this->positionIterations = 2;


    b2BodyDef anchorDef;
	anchorDef.position.Set(0.0f, -10.0f);

	this->anchor = world.CreateBody(&anchorDef);

	is_running = false;
	purchaseFase = true;
    roundMoneyLost = matchConfig.at(MONEY_ROUND_LOST);
    roundMoneyWon = matchConfig.at(MONEY_ROUND_WON);
}

WorldModel::~WorldModel() {

}

WorldModel::WorldModel(WorldModel &&other)
: world(b2Vec2(0.0f, 0.0f)),
  anchor(nullptr),
  matchConfig(other.matchConfig),
  playerModels(std::move(other.playerModels)),
  bomb(other.bomb),
  tally(other.tally),
  usersEvents(std::move(other.usersEvents)),
  updates(other.updates),
  updatesM(other.updatesM),
  droppedWeapons(std::move(other.droppedWeapons)),
  timeStep(other.timeStep),
  velocityIterations(other.velocityIterations),
  positionIterations(other.positionIterations),
  is_running(other.is_running) {
    // tengo que crearlo asi pq
    // en box2d el world
    // no tiene construccion por movimiento
    // ni por copia
    b2BodyDef anchorDef;
    anchorDef.position.Set(0.0f, -10.0f);
    this->anchor = world.CreateBody(&anchorDef);
}

WorldModel &WorldModel::operator=(WorldModel &&other)  {
    if (this == &other) {
        return *this;
    }

    return *this;
}

void WorldModel::stop() {
    is_running = false;
}

ProtectedQueue<std::unique_ptr<ClientEvent>>& WorldModel::addPlayer(int clave) {
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(std::rand()%50, std::rand()%50);
	b2Body* body = world.CreateBody(&bodyDef);

	b2CircleShape bodyCircle;
	bodyCircle.m_radius = 0.2f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &bodyCircle;
	fixtureDef.density = 1.0f;

	body->CreateFixture(&fixtureDef);

	b2FrictionJointDef fJointDef;
	fJointDef.bodyA = this->anchor;
	fJointDef.bodyB = body;

	b2FrictionJoint* fJoint = (b2FrictionJoint*)world.CreateJoint(&fJointDef);
	fJoint->SetMaxForce(12);

	playerModels.emplace(std::piecewise_construct,
                         std::forward_as_tuple(clave),
                         std::forward_as_tuple(body, bomb, droppedWeapons, matchConfig));

	return std::ref(this->usersEvents);
}

void WorldModel::loadMap(YAML::Node& mapInfo) {
    mapLayout.loadMap(world, mapInfo);
}

void WorldModel::run() {
	is_running = true;
    // division en equipos
    for (int i = 0; i < (int)playerModels.size()/2; i++) {
        playerModels.at(i).changeSide();
    }
    updatesM.updateTeams();  
    updatesM.updateTime(tally);
    // Setup inicial
    for (auto & playerModel : this->playerModels) {
		tally.placeInTeam(playerModel.first, playerModel.second.getSide());
        updatesM.updateMoney(playerModel.first);
        updatesM.updateHp(playerModel.first);
        updatesM.updateWeapon(playerModel.first, KNIFE);
	}
    // Ciclo de juego, 10 rondas
    for (int i = 0; i < 10 && is_running; i++) {
		if (i == 5) swapTeams();
        resetRound();
        purchaseFase = true;
        playerModels.at(tally.getTerrorist()).giveBomb();
        roundPurchase();
		purchaseFase = false;
        roundPlay();
    }
    if (!is_running) {
        return;
    }
    updatesM.updateScore(tally);
    usleep(FRAMERATE * 600);
    updates.pushAll(std::unique_ptr<Update>(new GameDoneUpdate()));
}

void WorldModel::resetRound() {
    reviveAll();
    for (auto & playerModel : this->playerModels) {
		playerModel.second.reposition(mapLayout);
	}
    bomb->reset();
    droppedWeapons.removeBomb();
    tally.resetRound();
}

void WorldModel::roundPurchase() {
    updatesM.updateBuying(true);
    updatesM.updatePositions();
    usleep(FRAMERATE);
    // 600 ticks, 10 segundos
    for (size_t i = 0; i < 600 && is_running; ++i) {
        roundCommon();
    }
    updatesM.updateBuying(false);
}

void WorldModel::roundPlay() {
    // no queremos ningun evento residual
    usersEvents.clear();
    while (!tally.isRoundOver() && is_running) {
        roundCommon();
    }

    if (!is_running) {
        return;
    }

    if (tally.isRoundOver() == 1) {
        updatesM.updateCtWinRound();
        // ciclo agregado a ultimo momento
        for (auto& player: this->playerModels) {
            player.second.gibRoundMoney(true, roundMoneyWon);
            player.second.gibRoundMoney(false, roundMoneyLost);
            updatesM.updateMoney(player.first);
        }
    } else if (tally.isRoundOver() == -1) {
        updatesM.updateTtWinRound();
        // ciclo agregado a ultimo momento
        for (auto& player: this->playerModels) {
            player.second.gibRoundMoney(false, roundMoneyWon);
            player.second.gibRoundMoney(true, roundMoneyLost);
            updatesM.updateMoney(player.first);
        }
    }
    usleep(FRAMERATE * 120);
}

void WorldModel::roundCommon() {
    auto start = std::chrono::system_clock::now();
    for (int j = 0; j < 50 && is_running; ++j) {
        try {
            std::unique_ptr<ClientEvent> event = usersEvents.pop();
            event->updatePlayer(*this);
        }
        catch (const std::exception& e) {
            continue;
        }
    }

    if (!is_running) {
        return;
    }
    
    this->step();

    if (tally.tickTime()) {
        updatesM.updateTime(tally);
    }
    updatesM.updatePositions();
    updatesM.updateAngles();

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<float, std::micro> elapsed = (end - start);
    usleep(FRAMERATE + elapsed.count());
}

void WorldModel::bombStep() {
    int state = bomb->tic();
    switch (state) {
        case ACTIVATE: {
            stopBombHandling(bomb->getPlanter());
            updatesM.updateBombPlanted(bomb->getPlanter());
            tally.startBombTiming();
            break;
        }
        case EXPLODED: {
            updatesM.updateBombExplode();
            for (auto& victim: this->playerModels) {
                if (bomb->explosionDamage(victim.second.getPosition())) {
                    tally.addDeath(victim.first);
                    victim.second.die();
                    updatesM.updateDead(victim.first);
                    updatesM.updateWeapon(victim.first, KNIFE);
                }
            }
            break;
        }
    }
}

void WorldModel::step() {
	for (auto& attacker : this->playerModels) {
        attacker.second.step();
        if (!attacker.second.canShoot()) continue;
        updatesM.updateAttack(attacker.first);
		for (auto& victim : playerModels) {
		    // esta condicion es para que no se ataque a si mismo
		    if (&victim.second == &attacker.second) continue;
            // esta condicion chequea que haya un hit
            if (attacker.second.attack(victim.second.getPosition())) {
                // esta condicion chequea que no se atraviesen paredes
                if (mapLayout.checkTunneling(attacker.second.getPosition(), victim.second.getPosition())) continue;
                // esta condicion chequea si murio, o si solo hubo impacto
                if (victim.second.gotHitAndDied(attacker.second.hit())) {
                    tally.playerKilledOther(attacker.first, victim.first);
                    victim.second.die();
                    attacker.second.kill();
                    updatesM.updateMoney(attacker.first);
                    updatesM.updateDead(victim.first);
                    updatesM.updateWeapon(victim.first, KNIFE);
                } else {
                    updatesM.updateHit(victim.first);
                }
                updatesM.updateHp(victim.first);
            }
		}
	}
    bombStep();
	this->world.Step(this->timeStep, this->velocityIterations, this->positionIterations);
}

void WorldModel::movePlayer(uint8_t id, uint8_t dir) {
	if (purchaseFase) return;
    playerModels.at(id).startMove(dir);
}

void WorldModel::stopMovingPlayer(uint8_t id, uint8_t dir) {
	if (purchaseFase) return;
    playerModels.at(id).stopMove(dir);
}

void WorldModel::rotatePlayer(uint8_t id, int16_t angle) {
    playerModels.at(id).setAngle(angle);
}

void WorldModel::startAttack(uint8_t id) {
	if (purchaseFase) return;
    playerModels.at(id).startAttack();
}

void WorldModel::stopAttack(uint8_t id) {
	if (purchaseFase) return;
    playerModels.at(id).stopAttack();
}

void WorldModel::startBombHandling(uint8_t id) {
	if (purchaseFase) return;
    if (playerModels.at(id).startBombHandling(mapLayout, id)) {
        equipWeapon(id, EXPLOSIVE);
    }
}

void WorldModel::stopBombHandling(uint8_t id) {
    if (purchaseFase) return;
	if (playerModels.at(id).stopBombHandling()) {
        equipWeapon(id, MELEE);
    }
}

void WorldModel::equipWeapon(uint8_t id, uint8_t weaponType) {
    int weaponId = -1;
	if ((weaponId = playerModels.at(id).equipWeapon(weaponType)) != -1) {
		updatesM.updateWeapon(id, weaponId);
	}
}

void WorldModel::buyWeapon(uint8_t id, uint8_t weaponCode) {
    if (playerModels.at(id).buyWeapon(weaponCode)) {
		// el weaponType = 0 es el de arma primaria
		// solo podes comprar armas primarias, asi que si compraste equipas la primaria
		equipWeapon(id, PRIMARY);
        updatesM.updateMoney(id);
    }
}

void WorldModel::pickUpWeapon(uint8_t id) {
    int weaponCode = playerModels.at(id).pickUpWeapon();
	if (weaponCode == BOMB) {
		equipWeapon(id, EXPLOSIVE);
    } else if (weaponCode == -1) {
        return;
    } else {
        equipWeapon(id, PRIMARY);
    }
}

void WorldModel::reloadWeapon(uint8_t id) {
    playerModels.at(id).reload();
    updatesM.updateClip(id);
}

void WorldModel::disconnectPlayer(uint8_t id) {
    // luego, le decimos al broadcaster que cierre su q
    // de esa manera mata al sender
    // hasta este punto del recorrido, receiver murio, sender esta vivo
    updates.closePlayerQueue(id);
    // una vez cerrado, se lo borra de aca
    // deberia mandarse un update al resto de los jugadores
}

void WorldModel::swapTeams() {
    for (auto & playerModel : this->playerModels) {
        playerModel.second.changeSide();
        playerModel.second.die();
    }
    tally.swapTeams();
    updatesM.updateTeams();
    droppedWeapons.clear();
}

void WorldModel::reviveAll() {
    for (auto& it : playerModels) {
        it.second.revive();
        updatesM.updateHp(it.first);
    }
}

bool WorldModel::isDead() {
    return !is_running;
} 
