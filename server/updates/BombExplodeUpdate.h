#ifndef BOMBEXPLODEUPDATE_H
#define BOMBEXPLODEUPDATE_H


#include "Update.h"

class BombExplodeUpdate : public Update{
public:
    BombExplodeUpdate();

    void serialize(std::function<void (std::vector<unsigned char>)> &callback) override;

    ~BombExplodeUpdate() override;
};


#endif
