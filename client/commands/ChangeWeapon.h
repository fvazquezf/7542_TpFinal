#ifndef CHANGEWEAPON_H
#define CHANGEWEAPON_H

#include <SDL2/SDL_keycode.h>
#include "Command.h"

class ChangeWeapon : public Command{
public:
    enum ChangeCode : uint8_t {PRI, GLK, KNF, BMB};

    explicit ChangeWeapon(SDL_Keycode changeCode);

    void serialize(std::function<void (std::vector<unsigned char>)> &callback, const Protocol &protocol) override;

    ~ChangeWeapon() override;
private:
    uint8_t code;
    std::map<SDL_Keycode, ChangeWeapon::ChangeCode> changeMap{
            {SDLK_1, ChangeCode::PRI},
            {SDLK_2, ChangeCode::GLK},
            {SDLK_3, ChangeCode::KNF},
            {SDLK_4, ChangeCode::BMB}
    };
};


#endif
