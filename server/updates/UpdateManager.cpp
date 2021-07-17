#include "UpdateManager.h"

#include "PositionUpdate.h"
#include "AngleUpdate.h"
#include "AttackUpdate.h"
#include "HitUpdate.h"
#include "DeadUpdate.h"
#include "WeaponUpdate.h"
#include "BuyTimeUpdate.h"
#include "HpUpdate.h"
#include "MoneyUpdate.h"
#include "TimeUpdate.h"
#include "TeamsUpdate.h"
#include "BombPlantUpdate.h"
#include "ClipUpdate.h"
#include "CtWinRoundUpdate.h"
#include "TtWinRoundUpdate.h"
#include "BombExplodeUpdate.h"


UpdateManager::UpdateManager(Broadcaster& broadcaster, const std::map<int, PlayerModel>& playerModels):
 updatesQ(broadcaster), playerModels(playerModels){

}

void UpdateManager::updatePositions() {
    std::map<uint8_t, std::pair<float, float>> newPos;
    for (auto& playerModel : playerModels) {
        int id = playerModel.first;
        b2Vec2 pos = playerModel.second.getPosition();
        newPos[id] = std::pair<float, float>(pos.x, pos.y);
    }
    std::shared_ptr<Update> updatePtr(new PositionUpdate(std::move(newPos)));
    updatesQ.pushAll(updatePtr);
}

void UpdateManager::updateAngles() {
    std::map<uint8_t, int16_t> angles;
    for (auto& it : playerModels){
        angles.insert({it.first, it.second.getAngle()});
    }
    std::shared_ptr<Update> updatePtr(std::shared_ptr<Update>(new AngleUpdate(std::move(angles))));
    updatesQ.pushAll(updatePtr);
}

void UpdateManager::updateAttack(int id){
	std::shared_ptr<Update> updatePtr(new AttackUpdate(id));
    updatesQ.pushAll(updatePtr);
    updateClip(id);
}

void UpdateManager::updateHit(int id){
	std::shared_ptr<Update> updatePtr(new HitUpdate(id));
    updatesQ.pushAll(updatePtr);
}

void UpdateManager::updateDead(int id){
	std::shared_ptr<Update> updatePtr(new DeadUpdate(id));
    updatesQ.pushAll(updatePtr);
}

void UpdateManager::updateWeapon(uint8_t id, uint8_t weaponCode){
	std::shared_ptr<Update> updatePtr(new WeaponUpdate(id, weaponCode));
    updatesQ.pushAll(updatePtr);
    updateClip(id);
}

void UpdateManager::updateBuying(bool buying) {
    updatesQ.pushAll(std::shared_ptr<Update>(new BuyTimeUpdate(buying)));
}

void UpdateManager::updateTeams(){
    std::map<uint8_t, bool> teams;
    for (auto & playerModel : playerModels){
        int id = playerModel.first;
        bool team = playerModel.second.getSide();
        teams[id] = team;
    }
    std::shared_ptr<Update> updatePtr(new TeamsUpdate(std::move(teams)));
    updatesQ.pushAll(updatePtr);
}

void UpdateManager::updateHp(int id){
    int hp = playerModels.at(id).getHp();
    std::shared_ptr<Update> updatePtr(new HpUpdate(hp));
    updatesQ.push(id, updatePtr);
}

void UpdateManager::updateMoney(int id){
    int money = playerModels.at(id).getMoney();
    std::shared_ptr<Update> updatePtr(new MoneyUpdate(money));
    updatesQ.push(id, updatePtr);
}

void UpdateManager::updateTime(Tally& tally){
    int time = tally.getTime();
    std::shared_ptr<Update> updatePtr(new TimeUpdate(time));
    updatesQ.pushAll(updatePtr);
}

void UpdateManager::updateBombPlanted(int id){
    std::shared_ptr<Update> updatePtr(new BombPlantUpdate(id));
    updatesQ.pushAll(updatePtr);
}

void UpdateManager::updateCtWinRound(){
    std::shared_ptr<Update> updatePtr(new CtWinRoundUpdate());
    updatesQ.pushAll(updatePtr);
}

void UpdateManager::updateTtWinRound(){
    std::shared_ptr<Update> updatePtr(new TtWinRoundUpdate());
    updatesQ.pushAll(updatePtr);
}

void UpdateManager::updateBombExplode(){
    std::shared_ptr<Update> updatePtr(new BombExplodeUpdate());
    updatesQ.pushAll(updatePtr);
}

void UpdateManager::updateClip(int id){
    int clip = playerModels.at(id).getClip();
    if (clip != -1) {
        std::shared_ptr<Update> updatePtr(new ClipUpdate(clip));
        updatesQ.push(id, updatePtr);
    }
}


