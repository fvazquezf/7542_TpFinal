#include "ChangeWeapon.h"

ChangeWeapon::ChangeWeapon(SDL_Keycode changeCode){
    code = changeMap.at(changeCode);
}

void ChangeWeapon::serialize(std::function<void(std::vector<unsigned char>)> &callback, const Protocol &protocol) {
    protocol.changeWeapon(code, callback);
}

ChangeWeapon::~ChangeWeapon() {

}
