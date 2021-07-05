#include <utility>
#include <math.h>
#include <iostream>
#include "PlayerModel.h"
#include "weapons/Knife.h"
#include "../common/ConfigVariables.h"

PlayerModel::PlayerModel(b2Body* body, DroppedWeapons& dropped, const std::map<int, int>& matchConfig):
model(body),
angle(0),
hp(matchConfig.at(PLAYER_HP)),
money(matchConfig.at(STARTING_MONEY)),
isAlive(true),
armory(dropped, matchConfig){
    this->netForce.SetZero();
    dirAmount = 0;
    isCt = false;
}

PlayerModel::PlayerModel(PlayerModel &&other) noexcept
: model(other.model),
  netForce(other.netForce),
  armory(std::move(other.armory)){
    other.model = nullptr;
}

PlayerModel &PlayerModel::operator=(PlayerModel &&other) noexcept {
    if (this == &other){
        return *this;
    }

    model = other.model;
    netForce = other.netForce;
    other.model = nullptr;
    return *this;
}


void PlayerModel::startMove(int dir){
    dirAmount++;
    switch (dir) {
        case 0: this->netForce += b2Vec2(0, -15);
                break;
        case 1: this->netForce += b2Vec2(0, 15);
                break;
        case 2: this->netForce += b2Vec2(-15, 0);
                break;
        case 3: this->netForce += b2Vec2(15, 0);
                break;
        default: break;
    }
}

void PlayerModel::stopMove(int dir){
    if (dirAmount == 0) return;
    dirAmount--;
    switch (dir) {
        case 0: this->netForce += b2Vec2(0, 15);
                break;
        case 1: this->netForce += b2Vec2(0, -15);
                break;
        case 2: this->netForce += b2Vec2(15, 0);
                break;
        case 3: this->netForce += b2Vec2(-15, 0);
                break;
        case 5: this->netForce.SetZero();
                break;
        default: break;
    }
}

void PlayerModel::step(){
    float vel = this->model->GetLinearVelocity().Length();
    armory.tickCooldown();
    if (vel < 12){
        this->model->ApplyForceToCenter(this->netForce, true);
    }
}

void PlayerModel::reposition(MapLayout& mapLayout){
    b2Vec2 newPos;
    if(isCt){
        newPos = mapLayout.placeCt();
    } else {
        newPos = mapLayout.placeTt();
    }
    this->model->SetTransform(newPos, 0);
}

const b2Vec2& PlayerModel::getPosition(){
    return this->model->GetPosition();
}

void PlayerModel::setAngle(int16_t newAngle) {
    if (!isAlive){
        return;
    }
    this->angle = newAngle;
}

int16_t PlayerModel::getAngle() const {
    return angle;
}

bool PlayerModel::attack(PlayerModel& enemy){
    if (!isAlive){
        return false;
    }
    return armory.attack(model->GetPosition(), angle, enemy.getPosition());
}

void PlayerModel::reload(){
    armory.reload();
}

std::shared_ptr<Weapon> PlayerModel::hit(){
    return armory.hit();
}

bool PlayerModel::gotHitAndDied(std::shared_ptr<Weapon> weapon){
    hp -= weapon->hit();
    if (hp <= 0){
        hp = 0;
        return true;
    } else {
        return false;
    }
}

int PlayerModel::getHp(){
    return hp;
}

int PlayerModel::getMoney(){
    return money;
}

bool PlayerModel::canShoot(){
    return armory.canShoot();
}

void PlayerModel::resetCooldown(){
    armory.resetCooldown();
}

int PlayerModel::equipWeapon(int weaponType){
    return armory.equipWeapon(weaponType);
}

// si tenia un arma, la va a droppear en su lugar
bool PlayerModel::buyWeapon(uint8_t weaponCode) {
    return armory.tryBuying(weaponCode, money, model->GetPosition());
}

bool PlayerModel::pickUpWeapon(){
    return armory.pickUpWeapon(model->GetPosition());
}

void PlayerModel::die() {
    isAlive = false;
    armory.dropPrimary(model->GetPosition());
}

void PlayerModel::revive() {
    isAlive = true;
    hp = 100;
    reload();
}


void PlayerModel::changeSide(){
    isCt = !isCt;
}

bool PlayerModel::getSide(){
    return isCt;
}
