#ifndef ANGLEUPDATE_H
#define ANGLEUPDATE_H

#include "Update.h"
#include <map>

class AngleUpdate : public Update{
private:
    std::map<uint8_t, int16_t> angles;
public:
    explicit AngleUpdate(std::map<uint8_t, int16_t> angles);

    void serialize(std::function<void (std::vector<unsigned char>)> &callback) override;

    ~AngleUpdate() override;
};


#endif
