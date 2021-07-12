#include "SkinSelector.h"

SkinSelector::SkinSelector(SdlWindow &window,
                           YAML::Node& config,
                           SdlTexture& hudButton,
                           bool isPlayerCt,
                           CharacterManager& characterManager)
: show(true),
  isPlayerCt(isPlayerCt),
  characterManager(characterManager),
  ttId(-1),
  ctId(-1){
    skinTexturesCt.emplace(std::piecewise_construct,
                         std::forward_as_tuple(0),
                         std::forward_as_tuple(config["seal_force"].as<std::string>(),
                                                        window));
    skinTexturesCt.emplace(std::piecewise_construct,
                           std::forward_as_tuple(1),
                           std::forward_as_tuple(config["gsg-9"].as<std::string>(),
                                                        window));
    skinTexturesCt.emplace(std::piecewise_construct,
                           std::forward_as_tuple(2),
                           std::forward_as_tuple(config["sas"].as<std::string>(),
                                                        window));
    skinTexturesCt.emplace(std::piecewise_construct,
                           std::forward_as_tuple(3),
                           std::forward_as_tuple(config["gign"].as<std::string>(),
                                                 window));
    skinTexturesTt.emplace(std::piecewise_construct,
                           std::forward_as_tuple(0),
                           std::forward_as_tuple(config["pheonix"].as<std::string>(),
                                                 window));
    skinTexturesTt.emplace(std::piecewise_construct,
                           std::forward_as_tuple(1),
                           std::forward_as_tuple(config["l337"].as<std::string>(),
                                                        window));
    skinTexturesTt.emplace(std::piecewise_construct,
                           std::forward_as_tuple(2),
                           std::forward_as_tuple(config["artic"].as<std::string>(),
                                                        window));
    skinTexturesTt.emplace(std::piecewise_construct,
                           std::forward_as_tuple(3),
                           std::forward_as_tuple(config["guerilla"].as<std::string>(),
                                                 window));
    for (size_t i = 0; i < 4; ++i){
        counterButtons.emplace_back(400, 100 + 50 * i, 32,  32,
                                    hudButton,
                                    skinTexturesCt.at(i),
                                    SDL_Rect{0, 0, 32, 32},
                                    i);
        terroristButtons.emplace_back(400, 100 + 50 * i, 32, 32,
                                      hudButton,
                                      skinTexturesTt.at(i),
                                      SDL_Rect{0, 0, 32, 32},
                                      i);
    }
}

SkinSelector::~SkinSelector() {

}

void SkinSelector::draw() {
    if (!show) {
        return;
    }

    if (isPlayerCt) {
        for (auto& ctButton: counterButtons){
            ctButton.show();
        }
    } else {
        for (auto& ttButton: terroristButtons){
            ttButton.show();
        }
    }
}

void SkinSelector::assignTexturesFromButtonPressed() {
    int mX, mY;
    SDL_GetMouseState(&mX, &mY);
    if (isPlayerCt){
        for (auto& button : counterButtons){
            if (button.checkPressed(mX, mY)){
                ctId = button.getCode();
                ttId = selectRandomFrom(skinTexturesTt);
                break;
            }
        }
    } else {
        for (auto& button : terroristButtons){
            if (button.checkPressed(mX, mY)){
                ttId = button.getCode();
                ctId = selectRandomFrom(skinTexturesCt);
                break;
            }
        }
    }

    // si no los presiono, lanzo una exp
    // por como esta el codigo
    // no puede ser que alguno sea -1
    if (ctId == -1 && ttId == -1){
        throw std::exception();
    }

    show = false;
    characterManager.createCharacters(skinTexturesTt.at(ttId), skinTexturesCt.at(ctId));
}

uint8_t SkinSelector::selectRandomFrom(std::unordered_map<uint8_t, SdlTexture> &skinTextures) {
    auto randomTexIt = std::next(std::begin(skinTextures), rand() % skinTextures.size());
    return randomTexIt->first;
}

void SkinSelector::setRandomSkinsIfNotSelected() {
    if (ctId != -1 && ttId != -1){
        return;
    }
    ctId = selectRandomFrom(skinTexturesCt);
    ttId = selectRandomFrom(skinTexturesTt);
    show = false;
    characterManager.createCharacters(skinTexturesTt.at(ttId), skinTexturesCt.at(ctId));
}

void SkinSelector::setPlayerTeam(bool isCt) {
    if (ctId == -1 && ttId == -1){
        isPlayerCt = isCt;
    }
}

