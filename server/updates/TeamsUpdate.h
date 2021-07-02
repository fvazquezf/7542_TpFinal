#ifndef TEAMSUPDATE_H
#define TEAMSUPDATE_H

#include <map>
#include "Update.h"

class TeamsUpdate : public Update{
private:
    // mapa con las posiciones de cada jugador
    std::map<uint8_t, bool> teamsUpdates;
public:
    explicit TeamsUpdate(std::map<uint8_t, bool> teamsUpdates);

    void serialize(std::function<void(std::vector<unsigned char>)>& callback) override;

    ~TeamsUpdate() override;
};


#endif
