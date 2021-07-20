#include "AttackUpdate.h"

AttackUpdate::AttackUpdate(int id)
: attackerId(id) {
}

void AttackUpdate::serialize(std::function<void(std::vector<unsigned char>)>& callback) {
    // Manejalo como quieras esto, el attackerId es el Id del que esta atacando, bien redundante.
    // protocol.updateAttack(attackerId, callback);
    protocol.updatePlayerState(ATTACK_UPDATE, attackerId, callback);
}

AttackUpdate::~AttackUpdate() {

}
