#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include "../Broadcaster.h"
#include "../PlayerModel.h"
#include "../Tally.h"
#include <map>

class UpdateManager {
private:
Broadcaster& updatesQ;
const std::map<int, PlayerModel>& playerModels;

public:
    UpdateManager(Broadcaster& broadcaster, const std::map<int, PlayerModel>& playerModels);

    void updatePositions();
    void updateAngles();
    void updateAttack(int id);
    void updateHit(int id);
    void updateDead(int id);
    void updateWeapon(uint8_t id, uint8_t code);
    void updateBuying(bool buying);
    void updateTeams();
    void updateHp(int id);
    void updateMoney(int id);
    void updateTime(Tally& tally);
    void updateBombPlanted(int id);
    void updateCtWinRound();
    void updateTtWinRound();
    void updateBombExplode();
    void updateClip(int id);
    void updateScore(Tally& tally);
};


#endif
