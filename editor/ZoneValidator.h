#ifndef ZONEVALIDATOR_H
#define ZONEVALIDATOR_H

#include <vector>
#include <utility>
#include <map>
#include <string>

class ZoneValidator
{

public:
    ZoneValidator(std::vector<std::string> zones);
    ~ZoneValidator();
    bool addPosition(std::string &type, int row, int column);
    bool isValidZone();
    void reset(std::string &type);
    std::vector<std::pair<int,int>> getPositions(std::string &type);


private:
    std::map<std::string, std::vector<std::pair<int,int>>> positions;
    std::map<std::string, bool> validity;
    bool isARectangle(std::string &type);

};

#endif // ZONEVALIDATOR_H
