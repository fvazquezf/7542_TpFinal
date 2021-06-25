#ifndef HITUPDATE_H
#define HITUPDATE_H

#include <map>
#include "Update.h"

class HitUpdate : public Update{
private:
    int hittedId;
public:
    explicit HitUpdate(int hitUpdate);

    void serialize(std::function<void(std::vector<unsigned char>)>& callback) override;

    ~HitUpdate() override;
};


#endif
