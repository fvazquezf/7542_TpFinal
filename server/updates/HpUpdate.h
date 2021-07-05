#ifndef HPUPDATE_H
#define HPUPDATE_H

#include "Update.h"

class HpUpdate : public Update{
private:
    uint8_t hp;
public:
    explicit HpUpdate(uint8_t hp);

    void serialize(std::function<void(std::vector<unsigned char>)>& callback) override;

    ~HpUpdate() override;
};


#endif
