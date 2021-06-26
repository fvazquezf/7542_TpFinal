#include <tuple>
#include <iostream>
#include "Animation.h"

Animation::Animation(SdlTexture &texture,
                     int numFrames,
                     int framesW,
                     int framesH,
                     int sizeW,
                     int sizeH)
: texture(texture),
  currentFrame(0),
  numFrames(numFrames),
  sizeW(sizeW),
  sizeH(sizeH),
  numFramesH(framesH),
  numFramesW(framesW),
  frameOffset(0){
    for (int i = 0; i < framesH; ++i){
        for (int j = 0; j < framesW; ++j){
            frames.push_back(SDL_Rect{j * sizeW, i * sizeH, sizeW, sizeH});
        }
    }
}

Animation::~Animation(){

}

Animation::Animation(SdlTexture &texture, int numFrames, int framesW, int framesH, int size)
: texture(texture),
  currentFrame(0),
  numFrames(numFrames),
  sizeW(size),
  sizeH(size),
  numFramesH(framesH),
  numFramesW(framesW),
  frameOffset(0){
    for (int i = 0; i < framesH; ++i) {
        for (int j = 0; j < framesW; ++j) {
            frames.push_back(SDL_Rect{j * sizeW, i * sizeH, sizeW, sizeH});
        }
    }
}

void Animation::render(Camera &cam, float posX, float posY, float angle, uint8_t iteration) {
    if (currentFrame == numFrames){
        currentFrame = frameOffset;
    }

    auto frame = frames.at(currentFrame % numFrames);
    cam.renderFromRect(texture, frame, posX, posY, angle, sizeW, sizeH);
    std::cout << frame.x << " " << frame.y << " " << " " << frame.w << " " << frame.h << std::endl;
    ++currentFrame;

    if (shouldStay){
        renderCoordinates.emplace_back(std::make_tuple(posX, posY, frame));
    }
}

void Animation::stay() {
    shouldStay = true;
}

// seteo el frame desde el cual quiero renderizar
void Animation::renderFromFrame(int nFrame) {
    currentFrame = nFrame;
    frameOffset = nFrame;
}

void Animation::reset() {
    renderCoordinates.clear();
    currentFrame = 0;
}

void Animation::renderOld(Camera &camera) {
    for (auto& it : renderCoordinates){
        camera.renderFromRect(texture,
                              std::get<2>(it),
                              std::get<0>(it),
                              std::get<1>(it),
                              0,
                              sizeW,
                              sizeH);
    }
}

