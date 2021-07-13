#include "ZoneValidator.h"

ZoneValidator::ZoneValidator(std::vector<std::string> zones) {
    for (long unsigned int i = 0; i != zones.size(); ++i) {
        validity[zones[i]] = false;
    }

}

ZoneValidator::~ZoneValidator() {}

bool ZoneValidator::addPosition(std::string &type, int row, int column) {
    std::pair<int,int> pos(row, column);
    positions[type].push_back(pos);
    int n = positions[type].size();
    if(n > 4) {
        return false;
    } else if (n == 4) {
        if (this->isARectangle(type)) {
            validity[type] = true;
            return true;
        }
        return false;
    } else {
        return true;
    }
}

bool ZoneValidator::isARectangle(std::string &type) {
    
    if(positions[type].size() != 4) {
        return false;
    }

    std::pair<int,int> a = positions[type][0];
    std::pair<int,int> b = positions[type][1];
    std::pair<int,int> c = positions[type][2];
    std::pair<int,int> d = positions[type][3];

    bool isRectangle = true;

    //check x
    isRectangle &= (
        (a.first == b.first && c.first == d.first) ||
        (a.first == c.first && b.first == d.first) ||
        (a.first == d.first && b.first == c.first)
        );

    //check y
    isRectangle &= (
        (a.second == b.second && c.second == d.second) ||
        (a.second == c.second && b.second == d.second) ||
        (a.second == d.second && b.second == c.second)
        );

    return isRectangle;
}   

bool ZoneValidator::isValidZone() {
    bool isValid = true;
    std::map<std::string, bool>::iterator it;
    for (it = validity.begin(); it != validity.end(); it++) {
        isValid &= it->second;
    }
    return isValid;
}

void ZoneValidator::reset(std::string &type) {
    validity[type] = false;
    positions[type].clear();
}

std::vector<std::pair<int,int>> ZoneValidator::getPositions(std::string &type) {
    return positions[type];
}