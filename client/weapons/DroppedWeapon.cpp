#include "DroppedWeapon.h"
#include "../Camera.h"

DroppedWeapon::DroppedWeapon(SdlTexture &texture, uint8_t weaponType, size_t uniqueId, int16_t posX, int16_t posY)
: weaponTypeId(weaponType),
  uniqueId(uniqueId),
  droppedDrawable(texture,
                  droppedSizes.at(weaponTypeId).first,
                  droppedSizes.at(weaponTypeId).second,
                  posX / 100,
                  posY / 100),
  posXmm(posX),
  posYmm(posY),
  show(true){
}

bool DroppedWeapon::isWeaponTypeAndId(uint8_t weaponType, size_t uniqueIdentifier) {
    return weaponTypeId == weaponType && this->uniqueId == uniqueIdentifier;
}

void DroppedWeapon::draw(Camera& cam) {
    if (show && cam.isVisible(posXmm / 100, posYmm / 100)){
        droppedDrawable.render(cam, 0);
    }
}

DroppedWeapon::DroppedWeapon(DroppedWeapon &&other) noexcept
: weaponTypeId(other.weaponTypeId),
  uniqueId(other.uniqueId),
  droppedDrawable(std::move(other.droppedDrawable)),
  posXmm(other.posXmm),
  posYmm(other.posYmm),
  show(other.show){
}

DroppedWeapon &DroppedWeapon::operator=(DroppedWeapon &&other) noexcept {
    if (this == &other){
        return *this;
    }

    weaponTypeId = other.weaponTypeId;
    uniqueId = other.uniqueId;
    posXmm = other.posXmm;
    posYmm = other.posYmm;
    show = other.show;

    return *this;
}

DroppedWeapon::~DroppedWeapon() {

}

void DroppedWeapon::doNotShow() {
    show = false;
}
