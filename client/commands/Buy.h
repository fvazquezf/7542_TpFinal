#ifndef BUY_H
#define BUY_H

#include "Command.h"

class Buy : public Command{
private:
    uint8_t weaponCode;
public:
    explicit Buy(uint8_t weaponCode);

    void serialize(std::function<void (std::vector<unsigned char>)> &callback, const Protocol &protocol) override;

    ~Buy() override;
};


#endif
