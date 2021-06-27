#include "WeaponUpdate.h"

WeaponUpdate::WeaponUpdate(int id, int weaponId)
: id(id),
  weaponId(weaponId){
}

void WeaponUpdate::serialize(std::function<void(std::vector<unsigned char>)>& callback) {
    // Manejalo como quieras esto, el WeaponerId es el Id del que esta muerto, bien redundante.
    // protocol.updateWeapon(WeaponerId, callback);
    
    // protocol.updatePlayerState(WEAPON_UPDATE, weaponId, callback);
}

WeaponUpdate::~WeaponUpdate() {

}
