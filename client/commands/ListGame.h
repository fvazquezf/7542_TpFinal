#ifndef LISTGAME_H
#define LISTGAME_H


#include "Command.h"

class ListGame : public Command{
public:
    ListGame();

    void serialize(std::function<void (std::vector<unsigned char>)> &callback, const Protocol &protocol) override;

    ~ListGame() override;
};


#endif
