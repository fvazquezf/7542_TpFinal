#ifndef POSITIONUPDATE_H
#define POSITIONUPDATE_H

#include <map>
#include "Update.h"

class PositionUpdate : public Update{
private:
    // mapa con las posiciones de cada jugador
    std::map<uint8_t, std::pair<float, float>> positionUpdates;
public:
    explicit PositionUpdate(std::map<uint8_t, std::pair<float, float>> positionUpdates);

    void serialize(std::function<void(std::vector<unsigned char>)>& callback) override;

    ~PositionUpdate() override;
};


#endif
