#ifndef PROTOCOL_H
#define PROTOCOL_H

// TODO: CALLBACK QUE RECIBA UNA REFERENCIA Y NO UN PASAJE POR MOVIMIENTO, DONDE SEA POSIBLE

// comandos (client side)
#define CREATE 0x6e
#define JOIN 0x6a
#define LIST 0x6c
#define MOVE 0x70
#define STOP_MOVE 0x7e
#define ROTATE 0x6d
#define ATTACK 0x6b
#define STOP_ATTACK 0x7b
#define CHANGE_WEAPON 0x6f
#define BUY 0x7a
#define PICKUP 0x7c

// updates (server side)
#define POS_UPDATE 0x20
#define ANGLE_UPDATE 0x21
#define HIT_UPDATE 0x22
#define DEAD_UPDATE 0x23
#define ATTACK_UPDATE 0x24
#define WEAPON_UPDATE 0x25
#define BUYING_UPDATE 0x26
#define WEAPON_DROP_UPDATE 0x27
#define MAP_INFO_UPDATE 0x28
#define TEAM_UPDATE 0x29

// update misc
// login response me manda
// el id si fue buen login
// o fail si fallo
// al loggear, mandamos GAME_INFO
// puede tener el nombre de las partidas
#define LOGIN_RESPONSE 0x60
#define LOGIN_OK 0
#define LOGIN_BAD 1
#define GAME_INFO

#define BUY_START 0
#define BUY_END 1
#define PICKUP_UPDATE 0
#define DROP_UPDATE 1

// metros a centimetros
#define PRECISION 100.0f

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
    void serializeStringMessage(std::vector<unsigned char> &msg, const std::string& gameName) const;
    float deserializePosition(std::vector<unsigned char>& msg) const;
    void serializePosition(std::vector<unsigned char> &msg, float position) const;
public:
    Protocol();

    Protocol(const Protocol& other) = delete;
    Protocol& operator=(const Protocol& other) = delete;

    Protocol(Protocol&& other) noexcept;
    Protocol& operator=(Protocol&& other) noexcept;

                                //---------------CLIENT---------------//
    void createGame(const std::string& gameName, std::function<void(std::vector<unsigned char>)>& callback) const;
    void joinGame(const std::string& gameName, std::function<void(std::vector<unsigned char>)>& callback) const;
    void listGames(std::function<void(std::vector<unsigned char>)>& callback) const;
    void rotate(int16_t angle, std::function<void(std::vector<unsigned char>)>& callback) const;
    void attack(bool b, std::function<void(std::vector<unsigned char>)> &function) const;
    void move(uint8_t dir, bool isDone, std::function<void(std::vector<unsigned char>)>& callback) const;
    void changeWeapon(uint8_t changeCode, std::function<void(std::vector<unsigned char>)> &callback) const;
    void buy(uint8_t weaponCode, std::function<void(std::vector<unsigned char>)> &callback) const;

                                //---------------SERVER---------------//
    // dato clave, los updates son serializados en paralelo
    // por lo cual, todos los contenedores se pasan por referencia constante
    // segun cppreference el acceso es thread safe si no hay ningun write (y const asegura que no lo haya)
    // en cuanto al contenido de estos, nunca se modifica, de modo que sigue siendo safe
    void loginResponse(uint8_t status, std::function<void(std::vector<unsigned char>)>& callback, uint8_t id = -1) const;
    void updatePositions(const std::map<uint8_t, std::pair<float, float>>& positions,
                         std::function<void(std::vector<unsigned char>)>& callback) const;
    void updateAngles(const std::map<uint8_t, int16_t>& angles,
                      std::function<void(std::vector<unsigned char>)>& callback) const;
    void updatePlayerState(uint8_t code, uint8_t playerId, std::function<void(std::vector<unsigned char>)>& callback) const;
    void updatePlayerWeapon(uint8_t weaponCode,
                            uint8_t playerId,
                            std::function<void(std::vector<unsigned char>)>& callback) const;
    void updateBuyingTime(bool buyingTime, std::function<void(std::vector<unsigned char>)>& callback) const;
    void updateDrop(bool dropped,
                    size_t dropIdentifier,
                    uint8_t weaponCode,
                    float posX,
                    float posY,
                    std::function<void(std::vector<unsigned char>)> &callback) const;
    void updateMapInformation(const std::string& serializedMap, std::function<void(std::vector<unsigned char>)> &callback) const;
    void updateTeams(const std::map<uint8_t, bool> &map, std::function<void(std::vector<unsigned char>)> &callback);

    std::vector<unsigned char> dispatchReceived(uint8_t codeReceived,
                          std::function<std::vector<unsigned char>(size_t)> &receiveCallback);

                                //---------------CLIENT---------------//
    std::vector<unsigned char> handleUpdatePosition(std::function<std::vector<unsigned char>(size_t)> &callback);
    std::vector<unsigned char> handleLoginResponse(std::function<std::vector<unsigned char>(size_t)> &callback);
    std::vector<unsigned char> handleAngleUpdate(std::function<std::vector<unsigned char>(size_t)> &callback);
    std::vector<unsigned char> handleUpdateWeapon(std::function<std::vector<unsigned char>(size_t)> &callback);
    std::vector<unsigned char> handleDropUpdate(std::function<std::vector<unsigned char>(size_t)> &callback);
    std::vector<unsigned char> handleTeamUpdate(std::function<std::vector<unsigned char>(size_t)> &callback);

    std::map<uint8_t, std::pair<float, float>> deserializePositions(std::vector<unsigned char>& msg);
    std::map<uint8_t, int16_t> deserializeAngles(std::vector<unsigned char>& msg);
    std::tuple<uint8_t, size_t, int16_t, int16_t> deserializeDrop(std::vector<unsigned char>& msg, uint8_t dropType);
    std::map<uint8_t, bool> deserializeTeams(std::vector<unsigned char>& msg);

                                //---------------SERVER---------------//
    std::vector<unsigned char> handleGameName(std::function<std::vector<unsigned char>(size_t)> &callback);
    std::vector<unsigned char> handleByte(std::function<std::vector<unsigned char>(size_t)> &callback);
    std::vector<unsigned char> handleRotation(std::function<std::vector<unsigned char>(size_t)> &callback);

    ~Protocol();

    void handleByte(uint8_t byte, std::function<void(std::vector<unsigned char>)> &callback) const;
    void serializeMsgLenShort(std::vector<unsigned char> &angleMsg, int16_t data) const;
    uint16_t deserializeMsgLenShort(std::vector<unsigned char> &msg) const;

};


#endif
