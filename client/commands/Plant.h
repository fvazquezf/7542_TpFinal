#ifndef PLANTCOMMAND_H
#define PLANTCOMMAND_H


#include "Command.h"

class Plant : public Command{
private:
    bool planting;
public:
    explicit Plant(bool isPlanting);

    void serialize(std::function<void (std::vector<unsigned char>)> &callback, const Protocol &protocol) override;

    ~Plant() override;
};


#endif
