#ifndef EARLYSTART_H
#define EARLYSTART_H


#include "Command.h"

class EarlyStart : public Command{
public:
    EarlyStart();

    void serialize(std::function<void (std::vector<unsigned char>)> &callback, const Protocol &protocol) override;

    ~EarlyStart() override;
};


#endif
