#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <vector>
#include <string>

class Elements {
    public:
        std::vector<std::string> elements = {
            "wall_1", "wall_2", "wall_3", "wall_4", "wall_5", "wall_6", "wall_7", "wall_8",
            "zoneA", "zoneB", "zoneBomb",
            "m3", "AK-47", "AWP"
        };
        std::vector<std::string> walls = {"wall_1", "wall_2", "wall_3", "wall_4", "wall_5", "wall_6", "wall_7", "wall_8"};
        std::vector<std::string> zones = {"zoneA", "zoneB", "zoneBomb"};
        std::vector<std::string> weapoms = {"m3", "AK-47", "AWP"};
};

#endif   //ELEMENTS_H
