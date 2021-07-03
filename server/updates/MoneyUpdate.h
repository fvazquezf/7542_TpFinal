#ifndef MONEYUPDATE_H
#define MONEYUPDATE_H

#include "Update.h"

class MoneyUpdate : public Update{
private:
    uint8_t money;
public:
    explicit MoneyUpdate(uint8_t money);

    void serialize(std::function<void(std::vector<unsigned char>)>& callback) override;

    ~MoneyUpdate() override;
};


#endif
