#include "HitUpdate.h"

HitUpdate::HitUpdate(int id)
: hittedId(id){
}

void HitUpdate::serialize(std::function<void(std::vector<unsigned char>)>& callback) {
    // Manejalo como quieras esto, el hittedId es el Id del que fue atacado, bien redundante.
    // protocol.updateHit(hittedId, callback);
}

HitUpdate::~HitUpdate() {

}
