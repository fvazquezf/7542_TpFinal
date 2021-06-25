#ifndef DEADUPDATE_H
#define DEADUPDATE_H

#include <map>
#include "Update.h"

class DeadUpdate : public Update{
private:
    int deadId;
public:
    explicit DeadUpdate(int deadId);

    void serialize(std::function<void(std::vector<unsigned char>)>& callback) override;

    ~DeadUpdate() override;
};


#endif
