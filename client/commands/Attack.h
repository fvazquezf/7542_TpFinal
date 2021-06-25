#ifndef ATTACK_H
#define ATTACK_H


#include "Command.h"

class Attack : public Command{
private:
    bool done;
public:
    explicit Attack(bool done = false);

    void serialize(std::function<void (std::vector<unsigned char>)> &callback, const Protocol &protocol) override;

    ~Attack() override;
};


#endif
