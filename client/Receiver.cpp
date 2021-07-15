#include "Receiver.h"

Receiver::Receiver(WorldView &world, Socket& peer, Protocol& protocol)
: world(world),
  peer(peer),
  prot(protocol),
  running(true){
}

Receiver::~Receiver() {
}

void Receiver::run() {
    std::function<std::vector<unsigned char>(size_t)> cb =
            std::bind(&Receiver::receive, this, std::placeholders::_1);
    while (running){
        char update;
        if (peer.recv(&update, 1) <= 0){
            break;
        }
        std::vector<unsigned char> msg = prot.dispatchReceived(update, cb);
        handleReceived(update, msg);
    }
    world.signalDone();
}

void Receiver::stop() {
    running = false;
    peer.shutdown(SHUT_RD);
}

std::vector<unsigned char> Receiver::receive(size_t size) {
    std::vector<unsigned char> msg(size);
    peer.recv(reinterpret_cast<char *>(msg.data()), size);
    return msg;
}

void Receiver::handleReceived(uint8_t code, std::vector<unsigned char> &msg) {
    switch (code) {
        case LOGIN_RESPONSE:{
            if (msg.at(0) != 255){
                world.assignPlayer(msg.at(0));
            }
            break;
        }
        case POS_UPDATE: {
            auto map = prot.deserializePositions(msg);
            world.updatePositions(map);
            break;
        }
        case ANGLE_UPDATE: {
            auto map = prot.deserializeAngles(msg);
            world.updateAngles(map);
            break;
        }
        case ATTACK_UPDATE: {
            world.attack(msg.at(0));
            break;
        }
        case HIT_UPDATE: {
            world.hit(msg.at(0));
            break;
        }
        case DEAD_UPDATE: {
            world.kill(msg.at(0));
            break;
        }
        case WEAPON_UPDATE: {
            world.changeWeapon(msg.at(0), msg.at(1));
            break;
        }
        case BUYING_UPDATE: {
            world.stopLobby();
            world.setMenu(msg.at(0) == BUY_START);
            break;
        }
        case WEAPON_DROP_UPDATE: {
            auto tuple = prot.deserializeDrop(msg, msg.back());
            if (msg.back() == DROP_UPDATE){
                world.dropWeapon(tuple);
            } else {
                world.pickupWeapon(tuple);
            }
            break;
        }
        case TEAM_UPDATE: {
            auto teamMap = prot.deserializeTeams(msg);
            world.buildTeams(std::move(teamMap));
            break;
        }
        case TIMER_UPDATE: {
            world.updateHudTime(msg.at(0));
            break;
        }
        case HEALTH_UPDATE: {
            world.updateHudHealth(msg.at(0));
            break;
        }
        case MONEY_UPDATE: {
            auto money = prot.deserializeMsgLenShort(msg);
            world.updateHudMoney(money);
            break;
        }
        case GAME_DONE: {
            running = false;
            break;
        }
        case MAP_INFO_UPDATE: {
            std::string map(msg.begin(), msg.end());
            world.buildMap(map);
            break;
        }
        case CLIP_UPDATE:
            world.updateHudClip(msg.at(0));
            break;
        case BOMB_PLANT_UPDATE:
            world.plantBomb(msg.at(0));
            break;
        case BOMB_EXPLODE_DONE:
            world.blowBomb();
            break;
        case CT_WIN_ROUND:
            world.updateHudWinner(true);
            break;
        case TT_WIN_ROUND:
            world.updateHudWinner(false);
            break;
        case SCORE_UPDATE: {
            auto scores = prot.deserializeScores(msg);
            break;
        }
        default:
            break;
    }
}
