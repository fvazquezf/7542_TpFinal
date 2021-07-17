#ifndef SCORESCREEN_H
#define SCORESCREEN_H


#include <sdlwrap/SdlText.h>
#include "Hud.h"
#include <yaml-cpp/yaml.h>

class ScoreScreen {
private:
    SdlWindow& window;
    Hud& hud;
    std::string font;
    std::vector<SdlText> summaryDataCts;
    std::vector<SdlText> summaryDataTts;
    std::map<bool, std::map<std::string, std::string>> ctTtScoreStrings;
    uint8_t playerId;
    bool draw;
    void setPlayerScore(std::map<std::string, std::string>& teamScore,
                        const std::tuple<uint8_t, uint8_t, uint8_t, uint16_t, bool>& playerScore);
public:
    ScoreScreen(SdlWindow& window, Hud& hud, YAML::Node& config);

    ScoreScreen(const ScoreScreen& other) = delete;
    ScoreScreen& operator=(const ScoreScreen& other) = delete;

    ScoreScreen(ScoreScreen&& other);
    ScoreScreen& operator=(ScoreScreen&& other);

    void setScoreData(const std::vector<std::tuple<uint8_t, uint8_t, uint8_t, uint16_t, bool>>& scoreData);
    void show();
    void setPlayerId(uint8_t id);

    ~ScoreScreen();

    void setEnable();
};


#endif
