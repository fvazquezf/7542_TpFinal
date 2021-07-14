#include <c++/9/iostream>
#include "SdlText.h"

SdlText::SdlText(const std::string &pathToFont, SdlWindow &window, int pointSize)
: window(window),
  texture(nullptr),
  tWidth(0),
  tHeight(0){
    textFont = TTF_OpenFont(pathToFont.c_str(), pointSize);
    if (!textFont){
        // handle
    }
}

SdlText::~SdlText() {
    if (textFont) {
        TTF_CloseFont(textFont);
        textFont = nullptr;
    }

    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void SdlText::render(const Area &dst) {
    Area src(0, 0, tWidth, tHeight);
    window.handleRender(texture, src.buildRectangle(), dst.buildRectangle(), 0, SDL_FLIP_NONE);
}

void SdlText::setText(const std::string& text) {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    SDL_Color c{0xff, 0xff, 0xff};
    SDL_Surface* srf = TTF_RenderText_Blended_Wrapped(textFont, text.c_str(), c, window.getWidth());

    texture = window.createTexture(srf);
    if (!texture){
        TTF_CloseFont(textFont);
        // handle
    }
    TTF_SizeText(textFont, text.c_str(), &tWidth, &tHeight);
    SDL_FreeSurface(srf);
}
