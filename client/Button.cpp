#include "Button.h"

Button::Button(int x, int y, int w, int h,
               SdlTexture &hudTex,
               SdlTexture &buttonTexture,
               SDL_Rect texSource,
               uint8_t buttonCode)
: box{x, y, w, h},
  hudTexture(hudTex),
  buttonTex(buttonTexture),
  textureSource((texSource)),
  code(buttonCode){
}

void Button::show() {
    Area src(0, 0, box.w, box.h);
    Area dstHud(box.x, box.y, box.w, box.h);
    Area dstGunTex(box.x + (box.w/2 - textureSource.w / 2 ),
                   box.y + (box.h/2 - textureSource.h / 2),
                   textureSource.w,
                   textureSource.h);
    hudTexture.render(src, dstHud, SDL_FLIP_NONE);
    buttonTex.render(src, dstGunTex, SDL_FLIP_NONE);
}

Button::~Button() {

}

// se presiono si el mouse esta dentro de la caja
bool Button::checkPressed(int mouseX, int mouseY) {
    return (mouseX > box.x ) &&
           (mouseX < box.x + box.w) &&
           (mouseY > box.y ) &&
           (mouseY < box.y + box.h);
}

uint8_t Button::getCode() const {
    return code;
}
