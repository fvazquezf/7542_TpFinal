#ifndef CURSOR_H
#define CURSOR_H


#include <cstdint>
#include "sdlwrap/SdlWindow.h"
#include "sdlwrap/SdlTexture.h"

class Cursor {
private:
    uint8_t cursorType;
    SdlTexture cursorTexture;
    Area cursorSourceArea;
    int cursorSize;
public:
    Cursor(uint8_t cursorType, SdlWindow& window, const std::string& cursorSourceFile, int cursorSize);

    void draw();

    ~Cursor();
};


#endif
