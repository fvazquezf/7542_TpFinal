#ifndef FINALSCREENUPDATE_H
#define FINALSCREENUPDATE_H


#include "Update.h"

class FinalScreenUpdate : public Update{
    std::vector<std::tuple<uint8_t, uint8_t, uint8_t, uint16_t, bool>> scores;
public:
    FinalScreenUpdate(std::vector<std::tuple<uint8_t, uint8_t, uint8_t, uint16_t, bool>> scores);

    void serialize(std::function<void (std::vector<unsigned char>)> &callback) override;

    ~FinalScreenUpdate() override;
};


#endif
