//
// Created by leogm99 on 3/7/21.
//
// Estos headers automáticos los borraría todos, o pondría un header uniforme que referencie al grupo
// entero en vez de a un solo integrante (vale para todos los headers que haya en el código).
//

#ifndef RELOAD_H
#define RELOAD_H


#include "Command.h"

class Reload : public Command {
public:
    Reload();

    void serialize(std::function<void (std::vector<unsigned char>)> &callback, const Protocol &protocol) override;

    ~Reload() override;
};


#endif
