#ifndef ATTACKUPDATE_H
#define ATTACKUPDATE_H

#include <map>
#include "Update.h"

class AttackUpdate : public Update{
private:
    // mapa con las posiciones de cada jugador
    int attackerId;
public:
    explicit AttackUpdate(int attackUpdate);

    void serialize(std::function<void(std::vector<unsigned char>)>& callback) override;

    ~AttackUpdate() override;
};


#endif
