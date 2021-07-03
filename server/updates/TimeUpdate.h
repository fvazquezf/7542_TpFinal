#ifndef TIMEUPDATE_H
#define TIMEUPDATE_H

#include "Update.h"

class TimeUpdate : public Update{
private:
    uint8_t time;
public:
    explicit TimeUpdate(uint8_t time);

    void serialize(std::function<void(std::vector<unsigned char>)>& callback) override;

    ~TimeUpdate() override;
};


#endif
