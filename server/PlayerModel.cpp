#include <utility>
#include <math.h>
#include <iostream>
#include "PlayerModel.h"
#include "weapons/Knife.h"
#include "../common/ConfigVariables.h"

PlayerModel::PlayerModel(b2Body* body, std::shared_ptr<Bomb> bomb, DroppedWeapons& dropped, const std::map<int, int>& matchConfig):
model(body),
angle(0),
maxHp(matchConfig.at(PLAYER_HP)),
money(matchConfig.at(STARTING_MONEY)),
armory(bomb, dropped, matchConfig){
    hp = maxHp;
    this->netForce.SetZero();
    dirAmount = 0;
    isCt = false;
    isFrozen = true;
    isAttacking = false;
}

PlayerModel::PlayerModel(PlayerModel &&other)
: model(other.model),
  netForce(other.netForce),
  angle(other.angle),
  dirAmount(other.dirAmount),
  hp(other.hp),
  maxHp(other.maxHp),
  money(other.money),
  armory(std::move(other.armory)){
    other.model = nullptr;
}

PlayerModel &PlayerModel::operator=(PlayerModel &&other)  {
    if (this == &other){
        return *this;
    }

    model = other.model;
    netForce = other.netForce;
    angle = other.angle;
    dirAmount = other.dirAmount;
    hp = other.hp;
    maxHp = other.maxHp;
    money = other.money;
    armory = std::move(other.armory);
    other.model = nullptr;
    return *this;
}

void PlayerModel::startMove(int dir){
    if (isFrozen) return;
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
    if (dirAmount == 0 || isFrozen) return;
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
        case 5: this->netForce -= 2 * this->netForce;
                break;
        default: break;
    }
}

void PlayerModel::step(){
    float vel = this->model->GetLinearVelocity().Length();
    if (vel < 11){
        this->model->ApplyForceToCenter(this->netForce, true);
    }
}

void PlayerModel::startAttack(){
    isAttacking = true;
}

void PlayerModel::stopAttack(){
    isAttacking = false;
    armory.resetCooldown();
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

const b2Vec2& PlayerModel::getPosition() const {
    return this->model->GetPosition();
}

void PlayerModel::setAngle(int16_t newAngle) {
    this->angle = newAngle;
}

const int16_t PlayerModel::getAngle() const {
    return angle;
}

bool PlayerModel::attack(const b2Vec2& position){
    if (isFrozen) return false;
    return armory.attack(model->GetPosition(), angle, position);
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
        freeze();
        armory.dropWeapons(model->GetPosition());
        model->SetEnabled(false);
        return true;
    } else {
        return false;
    }
}

bool PlayerModel::canShoot(){
    if (isFrozen) return false;
    armory.tickCooldown();
    return armory.canShoot(isAttacking);
}

void PlayerModel::giveBomb(){
    // chequeo inecesario pero por si acaso
    if (!isCt){
        armory.giveBomb();
    }
}

bool PlayerModel::startBombHandling(MapLayout& mapLayout, int id){
    if (!mapLayout.isInSite(model->GetPosition())) return false;
    freeze();
    if (isCt) {
        return armory.startDefusing();
    } else {
        return armory.startPlanting(id);
    }
}

bool PlayerModel::stopBombHandling(){
    unfreeze();
    if (isCt) {
        return armory.stopDefusing();;
    } else {
        return armory.stopPlanting();
    }
}

int PlayerModel::equipWeapon(int weaponType){
    return armory.equipWeapon(weaponType);
}

// si tenia un arma, la va a droppear en su lugar
bool PlayerModel::buyWeapon(uint8_t weaponCode) {
    return armory.tryBuying(weaponCode, money, model->GetPosition());
}

int PlayerModel::pickUpWeapon(){
    return armory.pickUpWeapon(model->GetPosition(), isCt);
}

void PlayerModel::kill() {
    money += armory.bounty();
}

void PlayerModel::revive() {
    unfreeze();
    model->SetEnabled(true);
    hp = maxHp;
}


void PlayerModel::changeSide(){
    isCt = !isCt;
}

bool PlayerModel::getSide() const {
    return isCt;
}

int PlayerModel::getHp() const {
    return hp;
}

int PlayerModel::getMoney() const {
    return money;
}

int PlayerModel::getClip() const {
    return armory.getClip();
}

void PlayerModel::freeze(){
    isFrozen = true;
    netForce.SetZero();
    dirAmount = 0;
}

void PlayerModel::unfreeze(){
    isFrozen = false;
}
