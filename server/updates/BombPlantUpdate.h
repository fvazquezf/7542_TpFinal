#ifndef BOMBPLANTUPDATE_H
#define BOMBPLANTUPDATE_H

#include <map>
#include "Update.h"

class BombPlantUpdate : public Update{
private:
public:
    BombPlantUpdate();

    void serialize(std::function<void(std::vector<unsigned char>)>& callback) override;

    ~BombPlantUpdate() override;
};


#endif
