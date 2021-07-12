#ifndef ZONEVALIDATOR_H
#define ZONEVALIDATOR_H

#include <list>
#include <utility>

class ZoneValidator
{

public:
    ZoneValidator();
    ~ZoneValidator();
    void addPosition();
    bool isValidZone();

private:
    int pieces = 0;
    bool isValidZone = false;

};

#endif // ZONEVALIDATOR_H
