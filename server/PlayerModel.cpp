#include <utility>
#include <math.h>
#include <iostream>
#include "PlayerModel.h"
#include "weapons/Knife.h"

PlayerModel::PlayerModel(){
    this->model = nullptr;
    this->netForce.SetZero();
    angle = 0;
    hp = 100;
}

PlayerModel::PlayerModel(b2Body* body):
model(body),
angle(0),
hp(100){
    this->netForce.SetZero();
}

void PlayerModel::startMove(int dir){
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
    switch (dir) {
        case 0: this->netForce += b2Vec2(0, 15);
                break;
        case 1: this->netForce += b2Vec2(0, -15);
                break;
        case 2: this->netForce += b2Vec2(15, 0);
                break;
        case 3: this->netForce += b2Vec2(-15, 0);
                break;
        default: break;
    }
}

void PlayerModel::reposition(float x, float y){
    b2Vec2 newPos(x, y);
    this->model->SetTransform(newPos, 0);
}


void PlayerModel::step(){
    float vel = this->model->GetLinearVelocity().Length();
    if (vel < 12){
        this->model->ApplyForceToCenter(this->netForce, true);
    }
}

const b2Vec2& PlayerModel::getPosition(){
    return this->model->GetPosition();
}

PlayerModel::PlayerModel(PlayerModel &&other) noexcept
: model(other.model),
  netForce(other.netForce){
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

int16_t PlayerModel::getAngle() const {
    return angle;
}

void PlayerModel::setAngle(int16_t newAngle) {
    this->angle = newAngle;
}

bool PlayerModel::attack(PlayerModel& enemy){
    return armory.attack(model->GetPosition(), angle, enemy.getPosition());
}

std::shared_ptr<Weapon> PlayerModel::hit(){
    return armory.hit();
}

bool PlayerModel::gotHit(std::shared_ptr<Weapon> weapon){
    hp -= weapon->hit();
    std::cout << hp << std::endl;
    if (hp <= 0){
        return true;
    } else {
        return false;
    }
}

bool PlayerModel::tickCooldown(){
    return armory.tickCooldown();
}

void PlayerModel::resetCooldown(){
    armory.resetCooldown();
}

void PlayerModel::equipKnife(){
    armory.equipKnife();
}

int PlayerModel::equipPrimary(){
    armory.equipPrimary();
}

void PlayerModel::equipSecondary(){
    armory.equipSecondary();
}

bool PlayerModel::equipBomb(){
    armory.equipSecondary();
}


