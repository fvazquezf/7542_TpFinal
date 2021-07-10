#ifndef GAMEDONEUPDATE_H
#define GAMEDONEUPDATE_H


#include "Update.h"

class GameDoneUpdate : public Update{
public:
    GameDoneUpdate();

    void serialize(std::function<void (std::vector<unsigned char>)> &callback) override;

    ~GameDoneUpdate() override;
};


#endif
