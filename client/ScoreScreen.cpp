#include "ScoreScreen.h"

ScoreScreen::ScoreScreen(SdlWindow &window, Hud &hud, YAML::Node& config)
: window(window),
  hud(hud),
  font(config["cs_ttf"].as<std::string>()),
  playerId(0),
  draw(false){
    summaryDataCts.reserve(4);
    summaryDataTts.reserve(4);
    summaryDataCts.emplace_back(font, window, 30);
    summaryDataCts.emplace_back(font, window, 30);
    summaryDataCts.emplace_back(font, window, 30);
    summaryDataCts.emplace_back(font, window, 30);
    summaryDataTts.emplace_back(font, window, 30);
    summaryDataTts.emplace_back(font, window, 30);
    summaryDataTts.emplace_back(font, window, 30);
    summaryDataTts.emplace_back(font, window, 30);
    ctTtScoreStrings = {
            {false, {
                {"ID", "ID: "},
                {"KILLS", "KILLS: "},
                {"DEATHS", "DEATHS: "},
                {"MONEY", "MONEY: "}
                }},
            {true, {
                { "ID", "ID: " },
                { "KILLS", "KILLS: " },
                { "DEATHS", "DEATHS: "},
                { "MONEY", "MONEY: " }
                }}
            };
}

void ScoreScreen::setPlayerId(uint8_t id){
    playerId = id;
}

void ScoreScreen::setScoreData(const std::vector<std::tuple<uint8_t, uint8_t, uint8_t, uint16_t, bool>> &scoreData) {
    // TODO: separar por teams
    for (auto& score : scoreData){
        // si es ct
        if (std::get<4>(score)) {
            setPlayerScore(ctTtScoreStrings.at(true), score);
        } else {
            setPlayerScore(ctTtScoreStrings.at(false), score);
        }
    }
    summaryDataTts.at(0).setText(ctTtScoreStrings.at(false).at("ID"));
    summaryDataTts.at(1).setText(ctTtScoreStrings.at(false).at("KILLS"));
    summaryDataTts.at(2).setText(ctTtScoreStrings.at(false).at("DEATHS"));
    summaryDataTts.at(3).setText(ctTtScoreStrings.at(false).at("MONEY"));
    summaryDataCts.at(0).setText(ctTtScoreStrings.at(true).at("ID"));
    summaryDataCts.at(1).setText(ctTtScoreStrings.at(true).at("KILLS"));
    summaryDataCts.at(2).setText(ctTtScoreStrings.at(true).at("DEATHS"));
    summaryDataCts.at(3).setText(ctTtScoreStrings.at(true).at("MONEY"));
}

void ScoreScreen::show() {
    if (!draw){
        return;
    }

    size_t i = 0;
    for (auto& scoreText : summaryDataCts){
        Area dst3(window.getWidth() / 8, window.getHeight() / 5 + 50 * i, 100, 50);
        scoreText.render(dst3);
        ++i;
    }
    i = 0;
    for (auto& scoreText : summaryDataTts){
        Area dst3(window.getWidth() / 8,3 * window.getHeight() / 5 + 50 * i, 100, 50);
        scoreText.render(dst3);
        ++i;
    }
}

ScoreScreen::~ScoreScreen() {

}

void ScoreScreen::setPlayerScore(std::map<std::string, std::string> &teamScore,
                                 const std::tuple<uint8_t, uint8_t, uint8_t, uint16_t, bool>& playerScore) {
    bool isPlayer = std::get<0>(playerScore) == playerId;
    teamScore["ID"]+= std::to_string(std::get<0>(playerScore)) + (isPlayer ? " (yo) " : " ") + "  |||  ";
    teamScore["KILLS"]+= std::to_string(std::get<1>(playerScore)) + "  |||  ";
    teamScore["DEATHS"]+= std::to_string(std::get<2>(playerScore)) + "  |||  ";
    teamScore["MONEY"]+= std::to_string(std::get<3>(playerScore)) + "  |||  ";
}

ScoreScreen::ScoreScreen(ScoreScreen &&other)
: window(other.window),
  hud(other.hud),
  font(std::move(other.font)),
  summaryDataCts(std::move(other.summaryDataCts)),
  summaryDataTts(std::move(other.summaryDataTts)),
  playerId(other.playerId){
}

ScoreScreen &ScoreScreen::operator=(ScoreScreen &&other) {
    if (this == &other) {
        return *this;
    }

    font = std::move(other.font);
    summaryDataCts = std::move(other.summaryDataCts);
    summaryDataTts = std::move(other.summaryDataTts);
    playerId = other.playerId;

    return *this;
}

void ScoreScreen::setEnable() {
    draw = true;
}


