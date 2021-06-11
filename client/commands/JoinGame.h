#ifndef JOINGAME_H
#define JOINGAME_H

#include "Command.h"

class JoinGame : public Command {
private:
    std::string gameName;
public:
    explicit JoinGame(std::string gameName);

    void serialize(std::function<void(std::vector<unsigned char>)>& callback,
                           const Protocol& protocol) override;

    ~JoinGame() override;
};


#endif
