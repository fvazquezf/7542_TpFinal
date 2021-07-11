#ifndef CTWINROUNDUPDATE_H
#define CTWINROUNDUPDATE_H


#include "Update.h"

class CtWinRoundUpdate : public Update{
public:
    CtWinRoundUpdate();

    void serialize(std::function<void (std::vector<unsigned char>)> &callback) override;

    ~CtWinRoundUpdate() override;
};


#endif
