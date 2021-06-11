#ifndef COMMAND_H
#define COMMAND_H

#include <functional>
#include <vector>
#include "../../common/Protocol.h"

// clase abstracta
// todos los posibles comandos se iran encolando
// y el sender los enviara, mediante la serializacion del protocolo
class Command {
private:
    //stuff
public:
    Command();

    Command(const Command& other) = delete;
    Command& operator=(const Command& other) = delete;

    // el sender le pasa send para mandar el mensaje
    // este llega hasta el protocolo

    virtual void serialize(std::function<void(std::vector<unsigned char>)>& callback, const Protocol& protocol) = 0;

    virtual ~Command();
};


#endif
