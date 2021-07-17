#ifndef SDLTEXT_H
#define SDLTEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "SdlWindow.h"
#include "SdlTexture.h"

class SdlText {
private:
    SdlWindow& window;
    TTF_Font* textFont;
    SDL_Texture* texture;
    int tWidth;
    int tHeight;
public:
    SdlText(const std::string& pathToFont, SdlWindow& window, int pointSize);

    SdlText(const SdlText& other) = delete;
    SdlText& operator=(const SdlText& other) = delete;

    SdlText(SdlText&& other);
    SdlText& operator=(SdlText&& other);

    void setText(const std::string& text);

    void render(const Area& dst);

    ~SdlText();
};


#endif
