#include <vector>
#include "Protocol.h"
#include <arpa/inet.h>

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
    msg.push_back((gameSize >> 8) & 0xff);
    msg.push_back(gameSize & 0xff);
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
std::vector<unsigned char> Protocol::handleMoving(std::function<std::vector<unsigned char>(size_t)> &callback) {
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

            msg = handleMoving(receiveCallback);
            break;
        }
            // vacio pq el codigo es identico a STOP_MOVE
        case STOP_MOVE: {
            // recibo la dir
            msg = handleMoving(receiveCallback);
            break;
        }
        case POS_UPDATE: {
            msg = handleUpdatePosition(receiveCallback);
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

void Protocol::updatePositions(std::map<uint8_t, std::pair<float, float>> &positions,
                               std::function<void(std::vector<unsigned char>)> &callback) const {
    std::vector<unsigned char> msg;
    msg.push_back(POS_UPDATE);
    uint16_t msgSize = positions.size() * 9; // 1 uint8 (1 byte), 2 float (8 bytes)
    msgSize = htons(msgSize);
    msg.push_back((msgSize >> 8) & 0xff);
    msg.push_back(msgSize & 0xff);
    for (auto& pair : positions){
        msg.push_back(pair.first);
        serializePosition(msg, pair.second.first);
        serializePosition(msg, pair.second.second);
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
