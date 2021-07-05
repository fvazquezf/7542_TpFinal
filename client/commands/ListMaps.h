#ifndef LISTMAPS_H
#define LISTMAPS_H


#include "Command.h"

class ListMaps : public Command {
public:
    ListMaps();

    void serialize(std::function<void (std::vector<unsigned char>)> &callback, const Protocol &protocol) override;

    ~ListMaps() override;
};


#endif
