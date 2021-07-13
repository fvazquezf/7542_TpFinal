#ifndef TTWINROUNDUPDATE_H
#define TTWINROUNDUPDATE_H


#include "Update.h"

class TtWinRoundUpdate : public Update{
public:
    TtWinRoundUpdate();

    void serialize(std::function<void (std::vector<unsigned char>)> &callback) override;

    ~TtWinRoundUpdate() override;
};


#endif
