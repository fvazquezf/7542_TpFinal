#ifndef ROTATE_H
#define ROTATE_H

#include "Command.h"

class Rotate : public Command {
private:
    int16_t angle;
public:
    explicit Rotate(int16_t angle);

    void serialize(std::function<void (std::vector<unsigned char>)> &callback, const Protocol &protocol) override;

    ~Rotate() override;
};


#endif
