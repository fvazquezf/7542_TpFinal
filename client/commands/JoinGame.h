#ifndef JOINGAME_H
#define JOINGAME_H

#include "Command.h"

class JoinGame : public Command {
private:
    const std::string& gameName;
public:
    explicit JoinGame(const std::string& gameName);

    void serialize(std::function<void(std::vector<unsigned char>)>& callback,
                           const Protocol& protocol) override;

    ~JoinGame() override;
};


#endif
