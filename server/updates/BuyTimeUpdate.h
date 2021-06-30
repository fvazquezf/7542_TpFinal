#ifndef BUYTIMEUPDATE_H
#define BUYTIMEUPDATE_H


#include "Update.h"

class BuyTimeUpdate : public Update{
private:
    bool buyingTime;
public:
    explicit BuyTimeUpdate(bool buyingTime);

    void serialize(std::function<void (std::vector<unsigned char>)> &callback) override;

    ~BuyTimeUpdate() override;
};


#endif
