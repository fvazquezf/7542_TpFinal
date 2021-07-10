#ifndef RELOAD_H
#define RELOAD_H


#include "Command.h"

class Reload : public Command {
public:
    Reload();

    void serialize(std::function<void (std::vector<unsigned char>)> &callback, const Protocol &protocol) override;

    ~Reload() override;
};


#endif
