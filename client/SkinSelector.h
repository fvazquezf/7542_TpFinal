#ifndef SKINSELECTOR_H
#define SKINSELECTOR_H

#include <unordered_map>
#include <string>
#include "sdlwrap/SdlTexture.h"
#include "Button.h"
#include "CharacterManager.h"
#include <yaml-cpp/yaml.h>

class SkinSelector {
private:
    std::unordered_map<uint8_t, SdlTexture> skinTexturesCt;
    std::unordered_map<uint8_t, SdlTexture> skinTexturesTt;
    std::vector<Button> counterButtons;
    std::vector<Button> terroristButtons;
    bool show;
    bool isPlayerCt;
    CharacterManager& characterManager;
    int8_t ttId;
    int8_t ctId;
    uint8_t selectRandomFrom(std::unordered_map<uint8_t, SdlTexture>& skinTextures);
public:
    SkinSelector(SdlWindow& window,
                 YAML::Node& config,
                 SdlTexture& hudButton,
                 bool isPlayerCt,
                 CharacterManager& characterManager);

    void setPlayerTeam(bool isCt);

    void draw();

    // devuelve la textura correspondiente al boton presionado
    void assignTexturesFromButtonPressed();
    // setea skins random si el jugador no selecciono ninguno
    void setRandomSkinsIfNotSelected();

    ~SkinSelector();
};


#endif
