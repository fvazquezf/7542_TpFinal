#ifndef UPDATE_H
#define UPDATE_H

#include "../../common/Protocol.h"

class Update {
private:
protected:
    Protocol protocol;
public:
    Update();

    virtual void serialize(std::function<void(std::vector<unsigned char>)>& callback) = 0;

    virtual ~Update();
};


#endif
