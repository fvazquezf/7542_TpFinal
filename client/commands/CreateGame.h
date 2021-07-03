#ifndef CREATEGAME_H
#define CREATEGAME_H

#include "Command.h"

class CreateGame : public Command{
private:
    std::string gameName;
    std::string mapName;
public:
    explicit CreateGame(std::string gameName, std::string mapName);

    void serialize(std::function<void (std::vector<unsigned char>)> &callback,
                   const Protocol& protocol) override;

    ~CreateGame() override;
};


#endif
