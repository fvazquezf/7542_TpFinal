#include "Cursor.h"

Cursor::Cursor(uint8_t cursorType, SdlWindow &window, const std::string& cursorSourceFile, int cursorSize)
: cursorType(cursorType % 3), // por si alguien manda un numero mas grande que 2
  cursorTexture(cursorSourceFile, window, {0xff, 0, 0xff}),
  cursorSourceArea((this->cursorType % 2) * 46,
                   (this->cursorType / 2) * 46,
                   46,
                   46),
  cursorSize(cursorSize){
    // el area no es magia, la imagen tiene 4 frames en un cuadrado
    // por lo tanto si elijo el cursor "2" (indexo en 0), quiero moverme
    // uno en la altura (2/2 * 46 = 46) y ninguno a lo ancho (2%2 * 46 = 0)
}

void Cursor::draw() {
    int mX, mY;
    SDL_GetMouseState(&mX, &mY);
    Area dst(mX - cursorSize / 2, mY - cursorSize / 2, cursorSize, cursorSize);
    cursorTexture.render(cursorSourceArea, dst, SDL_FLIP_NONE);
}

Cursor::~Cursor() {
}
