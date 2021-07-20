#include "DeadUpdate.h"

DeadUpdate::DeadUpdate(int id)
: deadId(id) {
}

void DeadUpdate::serialize(std::function<void(std::vector<unsigned char>)>& callback) {
    // Manejalo como quieras esto, el DeaderId es el Id del que esta muerto, bien redundante.
    // protocol.updateDead(DeaderId, callback);
    protocol.updatePlayerState(DEAD_UPDATE, deadId, callback);
}

DeadUpdate::~DeadUpdate() {

}
