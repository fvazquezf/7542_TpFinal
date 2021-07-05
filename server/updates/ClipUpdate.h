#ifndef CLIPUPDATE_H
#define CLIPUPDATE_H

#include "Update.h"

class ClipUpdate : public Update{
private:
    uint8_t clip;
public:
    explicit ClipUpdate(uint8_t clip);

    void serialize(std::function<void(std::vector<unsigned char>)>& callback) override;

    ~ClipUpdate() override;
};


#endif
