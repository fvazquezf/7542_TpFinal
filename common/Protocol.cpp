#include <vector>
#include "Protocol.h"
#include <arpa/inet.h>
#include <stdexcept>
#include <iostream>

Protocol::Protocol() {
}

void Protocol::createGame(const std::string& gameName,
                          std::function<void(std::vector<unsigned char>)>&callback) const {
    std::vector<unsigned char> msg;
    msg.push_back(CREATE);
    serializeGameName(msg, gameName);
    callback(std::move(msg));
}

void Protocol::joinGame(const std::string &gameName,
                        std::function<void(std::vector<unsigned char>)>&callback) const {
    std::vector<unsigned char> msg;
    msg.push_back(JOIN);
    serializeGameName(msg, gameName);
    callback(std::move(msg));
}

void Protocol::listGames(std::function<void(std::vector<unsigned char>)>&callback) const {
    std::vector<unsigned char> msg;
    msg.push_back(LIST);
    callback(std::move(msg));
}

Protocol::~Protocol() {
}

// client side
void Protocol::serializeGameName(std::vector<unsigned char> &msg, const std::string& gameName) const {
    uint16_t gameSize = gameName.size();
    gameSize = htons(gameSize);
    serializeMsgLenShort(msg, gameSize);
    std::copy(gameName.begin(), gameName.end(), std::back_inserter(msg));
}

uint16_t Protocol::deserializeMsgLenShort(std::vector<unsigned char> &msg) const {
    return ntohs((msg.at(0) << 8) | msg.at(1));
}

void Protocol::move(uint8_t dir, bool isDone,
                    std::function<void(std::vector<unsigned char>)>& callback) const {
    std::vector<unsigned char> msg;
    msg.push_back(isDone ? STOP_MOVE : MOVE);
    msg.push_back(dir);
    callback(std::move(msg));
}

// server side
std::vector<unsigned char> Protocol::handleGameName(std::function<std::vector<unsigned char>(size_t)> &callback) {
    std::vector<unsigned char> received = callback(2);
    uint16_t nameSize = deserializeMsgLenShort(received);
    received = callback(nameSize);
    return received; // no recibirlo por std::move() para evitar copy ellision
}

// server side
std::vector<unsigned char> Protocol::handleByte(std::function<std::vector<unsigned char>(size_t)> &callback) {
    return callback(1); // direccion de movimiento
}

// server/client
// metodo que no sabe nada sobre el server/client
// solo sabe que ellos le pasan un metodo que recibe un size_t y devuelve un vector de chars
std::vector<unsigned char> Protocol::dispatchReceived(uint8_t codeReceived,
                                std::function<std::vector<unsigned char>(size_t)> &receiveCallback) {
    std::vector<unsigned char> msg;
    switch (codeReceived) {
        case CREATE: {
            // server se encarga de crear partida
            // hasta aca lei nada mas el primer byte
            // debo leer los bytes 2 y 3 para saber el largo
            // y los bytes restantes para recibir el nombre
            // llamar a un handler del servidor
            // thClient.handleCreateGame(gameName);
            // es un thClient pq el servidor
            // en teoria ya lo acepto a traves del acceptor/listener
            // SACO EL BREAK PQ EL CODIGO ES IDENTICO PARA CREATE Y JOIN
            // si es CREATE, cae directamente en el scope de JOIN
            msg = handleGameName(receiveCallback);
            break;
        }
        case JOIN: {
            // server se encarga de joinear al user a una partida
            // same que CREATE
            msg = handleGameName(receiveCallback);
            // llamar a un handler del servidor
            // thClient.handleJoinGame(gameName);
            break;
        }
        case LIST:
            // server se encarga de mandarle al user la lista de partidas
            // solo un byte, mando la lista
            // llamar a un handler del servidor
            // thClient.handleListing();
            break;
        case MOVE: {
            // server se encarga de mover a un jugador en una direccion
            // dentro de una partida
            // si el cliente esta en una partida, el servidor lo sabe
            // (lo tienen en mem, puede ser un mapa de partidas)
            // el cliente no necesita pasarle ningun id
            // solo la direccion (up down left right)
            // handle move in direction -> funcion propia del servidor
            // thClient.move(direction);

            msg = handleByte(receiveCallback);
            break;
        }
            // vacio pq el codigo es identico a STOP_MOVE
        case STOP_MOVE: {
            // recibo la dir
            msg = handleByte(receiveCallback);
            break;
        }
        case LOGIN_RESPONSE: {
            msg = handleLoginResponse(receiveCallback);
            break;
        }
        case POS_UPDATE: {
            msg = handleUpdatePosition(receiveCallback);
            break;
        }
        case ROTATE: {
            msg = handleRotation(receiveCallback);
            break;
        }
        case ANGLE_UPDATE: {
            msg = handleAngleUpdate(receiveCallback);
            break;
        }
        case ATTACK : {
            break;
        }
        case STOP_ATTACK : {
            break;
        }
        case ATTACK_UPDATE:{
            msg = handleByte(receiveCallback);
            break;
        }
        case HIT_UPDATE:{
            msg = handleByte(receiveCallback);
            break;
        }
        case DEAD_UPDATE:{
            msg = handleByte(receiveCallback);
            break;
        }
        case CHANGE_WEAPON: {
            msg = handleByte(receiveCallback);
            break;
        }
        case WEAPON_UPDATE: {
            msg = handleUpdateWeapon(receiveCallback);
            break;
        }
        case BUY: {
            msg = handleByte(receiveCallback);
            break;
        }
        case BUYING_UPDATE: {
            msg = handleByte(receiveCallback);
            break;
        }
        default:
            // err, bad code
            throw std::invalid_argument("Bad code received\n");
    }
    return msg;
}

Protocol::Protocol(Protocol &&other) noexcept {
}

Protocol &Protocol::operator=(Protocol &&other) noexcept {
    return *this;
}

void Protocol::updatePositions(const std::map<uint8_t, std::pair<float, float>> &positions,
                               std::function<void(std::vector<unsigned char>)> &callback) const {
    std::vector<unsigned char> msg;
    msg.push_back(POS_UPDATE);
    uint16_t msgSize = positions.size() * 9; // 1 uint8 (1 byte), 2 float (8 bytes)
    msgSize = htons(msgSize);
    serializeMsgLenShort(msg, msgSize);
    for (auto& pair : positions){
        msg.push_back(pair.first);
        serializePosition(msg, std::get<0>(pair.second));
        serializePosition(msg, std::get<1>(pair.second));
    }
    callback(std::move(msg));
}

void Protocol::serializePosition(std::vector<unsigned char> &msg, float position) const {
    int protocolPosition = position * PRECISION;
    protocolPosition = htonl(protocolPosition);
    auto* hostOrder = reinterpret_cast<char*>(&protocolPosition);
    for (int i = 3; i >= 0; --i){
        msg.push_back(hostOrder[i]);
    }
}

float Protocol::deserializePosition(std::vector<unsigned char> &msg) const {
    int networkPosition = 0;
    for (int i = 0; i != 4; ++i) {
        networkPosition |= ((msg.at(i)) << (24 - i * 8));
    }
    return ntohl(networkPosition) / PRECISION;
}

std::vector<unsigned char>
Protocol::handleUpdatePosition(std::function<std::vector<unsigned char>(size_t)> &sendCallback) {
    std::vector<unsigned char> msg = sendCallback(2);
    uint16_t size = deserializeMsgLenShort(msg);
    msg = sendCallback(size);
    return msg;
}

std::map<uint8_t, std::pair<float, float>> Protocol::deserializePositions(std::vector<unsigned char> &msg) {
    std::map<uint8_t, std::pair<float, float>> positionMap;
    for (size_t i = 0; i < msg.size(); i += 9){
        std::vector<unsigned char> positionX = {msg.begin() + i + 1,
                                                msg.begin() + i + 5};
        std::vector<unsigned char> positionY = {msg.begin() + i + 5,
                                                msg.begin() + i + 9};
        positionMap.emplace(msg.at(i),
                           std::make_pair(deserializePosition(positionX),
                           deserializePosition(positionY)));
    }
    return positionMap;
}

void
Protocol::loginResponse(uint8_t status,
                        std::function<void(std::vector<unsigned char>)> &callback,
                        uint8_t id) const {
    std::vector<unsigned char> msg;
    msg.push_back(LOGIN_RESPONSE);
    msg.push_back(status == LOGIN_OK ? LOGIN_OK : LOGIN_BAD);
    if (status == LOGIN_OK){
        msg.push_back(id);
    }
    callback(msg);
}

std::vector<unsigned char>
Protocol::handleLoginResponse(std::function<std::vector<unsigned char>(size_t)> &callback) {
    std::vector<unsigned char> status = callback(1);
    if (status.at(0) == LOGIN_OK){
        // devuelvo el id
        return callback(1);
    } else {
        // login bad
        return status;
    }
}

void Protocol::rotate(int16_t angle, std::function<void(std::vector<unsigned char>)> &callback) const {
    std::vector<unsigned char> angleMsg;
    angleMsg.push_back(ROTATE);
    angle = htons(angle);
    serializeMsgLenShort(angleMsg, angle);
    callback(std::move(angleMsg));
}

void Protocol::serializeMsgLenShort(std::vector<unsigned char> &angleMsg, int16_t data) const {
    for (int i = 0; i != 2; ++i){
        angleMsg.push_back((data >> (8 - i * 8)) & 0xff);
    }
}

std::vector<unsigned char> Protocol::handleRotation(std::function<std::vector<unsigned char>(size_t)> &callback) {
    return callback(2);
}

void Protocol::updateAngles(const std::map<uint8_t, int16_t> &angles,
                            std::function<void(std::vector<unsigned char>)> &callback) const {
    std::vector<unsigned char> msg;
    msg.push_back(ANGLE_UPDATE);
    uint16_t msgSize = angles.size() * 3; // 1 uint8_t (1 byte), 1 int16_t (2 bytes)
    msgSize = htons(msgSize);
    serializeMsgLenShort(msg, msgSize);
    for (auto& it : angles){
        msg.push_back(it.first);
        int16_t angle = htons(it.second);
        serializeMsgLenShort(msg, angle);
    }
    callback(std::move(msg));
}

std::vector<unsigned char> Protocol::handleAngleUpdate(std::function<std::vector<unsigned char>(size_t)> &callback) {
    auto v = callback(2);
    uint16_t msgSize = deserializeMsgLenShort(v);
    return callback(msgSize);
}

std::map<uint8_t, int16_t> Protocol::deserializeAngles(std::vector<unsigned char> &msg) {
    std::map<uint8_t, int16_t> angleMap;
    for (size_t i = 0; i < msg.size(); i += 3){
        std::vector<unsigned char> angle = {msg.data()[i+1],
                                            msg.data()[i+2]};
        angleMap.emplace(msg.at(i), static_cast<int16_t>(deserializeMsgLenShort(angle)));
    }
    return angleMap;
}

void Protocol::attack(bool done, std::function<void(std::vector<unsigned char>)> &callback) const {
    std::vector<unsigned char> attackMsg;
    attackMsg.push_back(done ? STOP_ATTACK : ATTACK);
    callback(std::move(attackMsg));
}

void Protocol::updatePlayerState(uint8_t code, uint8_t playerId, std::function<void(std::vector<unsigned char>)> &callback) const {
    std::vector<unsigned char> update;
    update.push_back(code);
    update.push_back(playerId);
    callback(std::move(update));
}

void Protocol::changeWeapon(uint8_t changeCode, std::function<void(std::vector<unsigned char>)> &callback) const {
    std::vector<unsigned char> changeMsg;
    changeMsg.push_back(CHANGE_WEAPON);
    changeMsg.push_back(changeCode);
    callback(std::move(changeMsg));
}

void Protocol::updatePlayerWeapon(uint8_t weaponCode, uint8_t playerId,
                                  std::function<void(std::vector<unsigned char>)> &callback) const {
    std::vector<unsigned char> update;
    update.push_back(WEAPON_UPDATE);
    update.push_back(weaponCode);
    update.push_back(playerId);
    callback(std::move(update));
}

std::vector<unsigned char> Protocol::handleUpdateWeapon(std::function<std::vector<unsigned char>(size_t)> &callback) {
    // weapon id y player id
    return callback(2);
}

void Protocol::buy(uint8_t weaponCode, std::function<void(std::vector<unsigned char>)> &callback) const {
    std::vector<unsigned char> buyingMsg;
    buyingMsg.push_back(BUY);
    buyingMsg.push_back(weaponCode);
    callback(std::move(buyingMsg));
}

void Protocol::updateBuyingTime(bool buyingTime, std::function<void(std::vector<unsigned char>)> &callback) const {
    std::vector<unsigned char> buyMsg;
    buyMsg.push_back(BUYING_UPDATE);
    buyMsg.push_back(buyingTime ? BUY_START : BUY_END);
    callback(std::move(buyMsg));
}
