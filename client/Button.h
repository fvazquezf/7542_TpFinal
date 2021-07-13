#ifndef BUTTON_H
#define BUTTON_H


#include <SDL2/SDL_rect.h>
#include "sdlwrap/SdlTexture.h"

class Button {
private:
    // dimension y posicion
    SDL_Rect box;

    SdlTexture& hudTexture;
    // textura a mostrar en el boton
    SdlTexture& buttonTex;

    SDL_Rect textureSource;

    uint8_t code;
public:
    Button(int x, int y, int w, int h,
           SdlTexture& hudTex,
           SdlTexture& buttonTexture,
           SDL_Rect texSrc,
           uint8_t buttonCode);

    Button(const Button& other) = delete;
    Button& operator=(const Button& other) = delete;

    Button(Button&& other);
    Button& operator=(Button&& other);

    void show();

    bool checkPressed(int mouseX, int mouseY);
    uint8_t getCode() const;

    ~Button();
};


#endif
