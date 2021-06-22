#ifndef PROTOCOL_H
#define PROTOCOL_H

// comandos (client side)
#define CREATE 0x6e
#define JOIN 0x6a
#define LIST 0x6c
#define MOVE 0x70
#define STOP_MOVE 0x7e
#define ROTATE 0x6d

// updates (server side)
#define POS_UPDATE 0x20

// update misc
// login response me manda
// el id si fue buen login
// o fail si fallo
#define LOGIN_RESPONSE 0x60
#define LOGIN_OK 0
#define LOGIN_BAD 1

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
    uint16_t deserializeMsgLenShort(std::vector<unsigned char> &msg) const;
    float deserializePosition(std::vector<unsigned char>& msg) const;
    void serializePosition(std::vector<unsigned char> &msg, float position) const;
public:
    Protocol();

    Protocol(const Protocol& other) = delete;
    Protocol& operator=(const Protocol& other) = delete;

    Protocol(Protocol&& other) noexcept;
    Protocol& operator=(Protocol&& other) noexcept;

    void createGame(const std::string& gameName, std::function<void(std::vector<unsigned char>)>& callback) const;
    void joinGame(const std::string& gameName, std::function<void(std::vector<unsigned char>)>& callback) const;
    void listGames(std::function<void(std::vector<unsigned char>)>& callback) const;
    void updatePositions(std::map<uint8_t, std::pair<float, float>>& positions,
                         std::function<void(std::vector<unsigned char>)>& callback) const;
    void rotate(int16_t angle, std::function<void(std::vector<unsigned char>)>& callback) const;
    void loginResponse(uint8_t status, std::function<void(std::vector<unsigned char>)>& callback, uint8_t id = -1) const;

    std::vector<unsigned char> dispatchReceived(uint8_t codeReceived,
                          std::function<std::vector<unsigned char>(size_t)> &receiveCallback);

    std::vector<unsigned char> handleGameName(std::function<std::vector<unsigned char>(size_t)> &callback);
    std::vector<unsigned char> handleMoving(std::function<std::vector<unsigned char>(size_t)> &callback);
    std::vector<unsigned char> handleUpdatePosition(std::function<std::vector<unsigned char>(size_t)> &callback);
    std::vector<unsigned char> handleLoginResponse(std::function<std::vector<unsigned char>(size_t)> &callback);
    std::vector<unsigned char> handleRotation(std::function<std::vector<unsigned char>(size_t)> &callback);

    std::map<uint8_t, std::pair<float, float>> deserializePositions(std::vector<unsigned char>& msg);
    int deserializeAngle(std::vector<unsigned char>& msg);
    // el booleano indica si el movimiento en la direccion
    // termino (true) o recien esta empezando (false)
    // de aca elegimos alguno de los dos mensajes
    // STOP_MOVE o MOVE
    void move(uint8_t dir, bool isDone, std::function<void(std::vector<unsigned char>)>& callback) const;

    ~Protocol();

    void serializeMsgLenShort(std::vector<unsigned char> &angleMsg, int16_t data) const;
};


#endif
