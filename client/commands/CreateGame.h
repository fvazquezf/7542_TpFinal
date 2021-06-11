#ifndef CREATEGAME_H
#define CREATEGAME_H

#include "Command.h"

class CreateGame : public Command{
private:
    const std::string& gameName;
public:
    explicit CreateGame(const std::string& gameName);

    void serialize(std::function<void (std::vector<unsigned char>)> &callback,
                   const Protocol& protocol) override;

    ~CreateGame() override;
};


#endif
