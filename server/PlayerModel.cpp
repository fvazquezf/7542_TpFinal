#include "PlayerModel.h"

PlayerModel::PlayerModel(){
    this->model = nullptr;
    this->netForce.SetZero();
}

PlayerModel::PlayerModel(b2Body* body): model(body){
    this->netForce.SetZero();
}

void PlayerModel::startMove(int dir){
    switch (dir) {
        case 1: this->netForce += b2Vec2(0, 15);
                break;
        case 2: this->netForce += b2Vec2(0, -15);
                break;
        case 3: this->netForce += b2Vec2(15, 0);
                break;
        case 4: this->netForce += b2Vec2(-15, 0);
                break;
        default: break;
    }
}

void PlayerModel::stopMove(int dir){
    switch (dir) {
        case 1: this->netForce += b2Vec2(0, -15);
                break;
        case 2: this->netForce += b2Vec2(0, 15);
                break;
        case 3: this->netForce += b2Vec2(-15, 0);
                break;
        case 4: this->netForce += b2Vec2(15, 0);
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
