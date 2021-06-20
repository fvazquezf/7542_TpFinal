#ifndef PROTOCOL_H
#define PROTOCOL_H

// comandos (client side)
#define CREATE 0x6e
#define JOIN 0x6a
#define LIST 0x6c
#define MOVE 0x70
#define STOP_MOVE 0x7e

// updates (server side)
#define POS_UPDATE 0x20

// update misc

// metros a milimetros
#define PRECISION 1000.0f

#include <vector>
#include <string>
#include <functional>
#include <map>

/*
 * Basico tipo tp3
 * CREATE: 0x6e
 * JOIN: 0x6a
 * LIST: 0x6c
 * MOVE: 0x70
 * STOP_MOVE: 0x7e
 * ...
 */

// el protocolo indica que lo primero que se recibe es un byte
// con el comando a leer
// los comandos podrian ser pusheados a una queue
// de la cual popea el sender
// estos objetos comando llaman al protocolo
// se serializan, y el sender los envia.

class Protocol {
private:
    void serializeGameName(std::vector<unsigned char> &msg, const std::string& gameName) const;
    uint16_t deserializeGameNameSize(std::vector<unsigned char> &msg) const;
public:
    Protocol();

    float deserializePosition(std::vector<unsigned char>& msg) const;
    void serializePosition(std::vector<unsigned char> &msg, float position) const;
    Protocol(const Protocol& other) = delete;
    Protocol& operator=(const Protocol& other) = delete;

    Protocol(Protocol&& other) noexcept;
    Protocol& operator=(Protocol&& other) noexcept;

    void createGame(const std::string& gameName, std::function<void(std::vector<unsigned char>)>& callback) const;
    void joinGame(const std::string& gameName, std::function<void(std::vector<unsigned char>)>& callback) const;
    void listGames(std::function<void(std::vector<unsigned char>)>& callback) const;
    void updatePositions(std::map<uint8_t, std::pair<float, float>>& positions,
                         std::function<void(std::vector<unsigned char>)>& callback) const;

    std::vector<unsigned char> dispatchReceived(uint8_t codeReceived,
                          std::function<std::vector<unsigned char>(size_t)> &receiveCallback);

    std::vector<unsigned char> handleGameName(std::function<std::vector<unsigned char>(size_t)> &sendcallback);
    std::vector<unsigned char> handleMoving(std::function<std::vector<unsigned char>(size_t)> &sendCallback);

    // el booleano indica si el movimiento en la direccion
    // termino (true) o recien esta empezando (false)
    // de aca elegimos alguno de los dos mensajes
    // STOP_MOVE o MOVE
    void move(uint8_t dir, bool isDone, std::function<void(std::vector<unsigned char>)>& callback) const;

    ~Protocol();
};


#endif
