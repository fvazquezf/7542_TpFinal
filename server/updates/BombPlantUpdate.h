#ifndef BOMBPLANTUPDATE_H
#define BOMBPLANTUPDATE_H

#include <map>
#include "Update.h"

class BombPlantUpdate : public Update{
private:
    int planterId;
public:
    explicit BombPlantUpdate(int id);

    void serialize(std::function<void(std::vector<unsigned char>)>& callback) override;

    ~BombPlantUpdate() override;
};


#endif
