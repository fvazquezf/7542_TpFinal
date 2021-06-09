#ifndef PROTOCOL_H
#define PROTOCOL_H

#define CREATE 0x6e
#define JOIN 0x6a
#define LIST 0x6c
#define MOVE 0x70
#define STOP_MOVE 0x7e

#include <string>

/*
 * Basico tipo tp3
 * CREATE: 0x6e
 * JOIN: 0x6a
 * LIST: 0x6c
 * MOVE: 0x70
 * STOP_MOVE: 0x7e
 */

// el protocolo indica que lo primero que se recibe es un byte
// con el comando a leer

class Protocol {
private:
    void serializeGameName(std::vector<unsigned char> &msg, const std::string& gameName);
    uint16_t deserializeGameNameSize(std::vector<unsigned char> &msg);
public:
    // direcciones basicas, hay que ver como es el tema de mirar/apuntar
    enum Direction : uint8_t {UP, DOWN, LEFT, RIGHT};

    Protocol();

    void createGame(const std::string& gameName);
    void joinGame(const std::string& gameName);
    void listGames();

    // el booleano indica si el movimiento en la direccion
    // termino (true) o recien esta empezando (false)
    // de aca elegimos alguno de los dos mensajes
    // STOP_MOVE o MOVE
    void move(Protocol::Direction dir, bool isDone);

    ~Protocol();
};


#endif
