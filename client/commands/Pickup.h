#ifndef PICKUP_H
#define PICKUP_H


#include "Command.h"

class Pickup : public Command{
public:
    Pickup();

    void serialize(std::function<void (std::vector<unsigned char>)> &callback, const Protocol &protocol) override;

    ~Pickup() override;
};


#endif
