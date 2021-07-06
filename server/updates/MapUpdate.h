//
// Created by leogm99 on 6/7/21.
//

#ifndef MAPUPDATE_H
#define MAPUPDATE_H


#include "Update.h"

class MapUpdate : public Update{
private:
    std::string map;
public:
    explicit MapUpdate(std::string map);

    void serialize(std::function<void (std::vector<unsigned char>)> &callback) override;

    ~MapUpdate() override;
};


#endif
