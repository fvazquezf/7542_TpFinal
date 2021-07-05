#include <vector>
#include "Protocol.h"
#include <arpa/inet.h>
#include <stdexcept>

Protocol::Protocol() {
}

void Protocol::createGame(const std::string& gameName,
                          const std::string& mapName,
                          std::function<void(std::vector<unsigned char>)>&callback) const {
    std::vector<unsigned char> msg;
    msg.push_back(CREATE);
    serializeStringMessage(msg, gameName);
    serializeStringMessage(msg, mapName);
    callback(std::move(msg));
}

void Protocol::joinGame(const std::string &gameName,
                        std::function<void(std::vector<unsigned char>)>&callback) const {
    std::vector<unsigned char> msg;
    msg.push_back(JOIN);
    serializeStringMessage(msg, gameName);
    callback(std::move(msg));
}

Protocol::~Protocol() {
}

void Protocol::serializeStringMessage(std::vector<unsigned char> &msg, const std::string& gameName) const {
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
std::vector<unsigned char> Protocol::handleCreateGame(std::function<std::vector<unsigned char>(size_t)> &callback) {
    std::vector<unsigned char> nameSizeReceived = callback(2);
    uint16_t nameSize = deserializeMsgLenShort(nameSizeReceived);
    std::vector<unsigned char> gameName = callback(nameSize);
    std::vector<unsigned char> mapSizeReceived = callback(2);
    uint16_t mapSize = deserializeMsgLenShort(mapSizeReceived);
    std::vector<unsigned char> mapName = callback(mapSize);
    std::vector<unsigned char> finalMsg;
    finalMsg.push_back((nameSize >> 8) & 0xff);
    finalMsg.push_back(nameSize & 0xff);
    finalMsg.insert(finalMsg.end(), gameName.begin(), gameName.end());
    finalMsg.push_back((mapSize >> 8) & 0xff);
    finalMsg.push_back(mapSize & 0xff);
    finalMsg.insert(finalMsg.end(), mapName.begin(), mapName.end());
    return finalMsg;
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
            msg = handleCreateGame(receiveCallback);
            break;
        }
        case JOIN: {
            msg = handleStringMsg(receiveCallback);
            break;
        }
        case LIST:
            break;
        case MOVE: {
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
        case WEAPON_DROP_UPDATE: {
            msg = handleDropUpdate(receiveCallback);
            break;
        }
        case PICKUP: {
            break;
        }
        case TEAM_UPDATE: {
            msg = handleTeamUpdate(receiveCallback);
            break;
        }
        case TIMER_UPDATE: {
            msg = handleByte(receiveCallback);
            break;
        }
        case HEALTH_UPDATE: {
            msg = handleByte(receiveCallback);
            break;
        }
        case CLIP_UPDATE: {
            msg = handleByte(receiveCallback);
            break;
        }
        case MONEY_UPDATE: {
            msg = handleShort(receiveCallback);
            break;
        }
        case RELOAD: {
            break;
        }
        case PLANT: {
            break;
        }
        case STOP_PLANT: {
            break;
        }
        case LOGIN_LIST_GAMES: {
            msg = handleStringMsg(receiveCallback);
            break;
        }
        case LIST_MAPS: {
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

void Protocol::serializeMsgLenShort(std::vector<unsigned char> &angleMsg, uint16_t data) const {
    int i = 0;
    while (i != 2){
        angleMsg.push_back(data >> (8 - i * 8) & 0xff);
        ++i;
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

// corresponde a los mensajes de start attack, stop attack, plant bomb, stop planting bomb
// todos los que sean al estilo bool
void Protocol::startStopCommand(uint8_t startStopCode, std::function<void(std::vector<unsigned char>)> &callback) const {
    std::vector<unsigned char> startStopMsg;
    startStopMsg.push_back(startStopCode);
    callback(std::move(startStopMsg));
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

void Protocol::handleByte(uint8_t byte, std::function<void(std::vector<unsigned char>)> &callback) const {
    std::vector<unsigned char> msg;
    msg.push_back(byte);
    callback(std::move(msg));
}

std::vector<unsigned char> Protocol::
handleDropUpdate(std::function<std::vector<unsigned char>(size_t)> &callback) {
    std::vector<unsigned char> msg = callback(1); // es drop o es pickup?
    if (msg.at(0) == DROP_UPDATE){
        auto vec = callback(9);
        vec.push_back(msg.at(0));
        return vec;
    } else {
        auto vec = callback(5);
        vec.push_back(msg.at(0));
        return vec;
    }
}

void Protocol::updateDrop(bool dropped, size_t dropIdentifier,
                          uint8_t weaponCode, float posX, float posY,
                          std::function<void(std::vector<unsigned char>)> &callback) const {
    std::vector<unsigned char> droppedMsg;
    droppedMsg.push_back(WEAPON_DROP_UPDATE);
    droppedMsg.push_back(dropped ? DROP_UPDATE : PICKUP_UPDATE);
    droppedMsg.push_back(weaponCode);
    dropIdentifier = htonl(dropIdentifier);
    droppedMsg.push_back(dropIdentifier >> 24 & 0xff);
    droppedMsg.push_back(dropIdentifier >> 16 & 0xff);
    droppedMsg.push_back(dropIdentifier >> 8 & 0xff);
    droppedMsg.push_back(dropIdentifier & 0xff);
    if (dropped){
        int pX = posX * PRECISION;
        int pY = posY * PRECISION;
        int16_t posXmm = htons(pX);
        int16_t posYmm = htons(pY);
        droppedMsg.push_back(posXmm >> 8 & 0xff);
        droppedMsg.push_back(posXmm & 0xff);
        droppedMsg.push_back(posYmm >> 8 & 0xff);
        droppedMsg.push_back(posYmm & 0xff);
    }
    callback(std::move(droppedMsg));
}

std::tuple<uint8_t, size_t, int16_t, int16_t> Protocol::deserializeDrop(std::vector<unsigned char> &msg, uint8_t dropType) {
    uint8_t weaponCode = msg.at(0);
    size_t dropIdentifier = 0;
    int16_t posX = 0;
    int16_t posY = 0;
    for (int i = 1; i <= 4; ++i) {
        dropIdentifier |= msg.at(i) << (24 - 8*(i - 1));
    }
    dropIdentifier = ntohl(dropIdentifier);
    if (dropType == DROP_UPDATE){
        posX = ntohs(msg.at(5) << 8 | msg.at(6));
        posY = ntohs(msg.at(7) << 8 | msg.at(8));
    }
    return std::make_tuple(weaponCode, dropIdentifier, posX, posY);
}

void Protocol::updateMapInformation(const std::string &serializedMap,
                                    std::function<void(std::vector<unsigned char>)> &callback) const {
    std::vector<unsigned char> msg;
    msg.push_back(MAP_INFO_UPDATE);
    serializeStringMessage(msg, serializedMap);
    callback(std::move(msg));
}

void
Protocol::updateTeams(const std::map<uint8_t, bool> &teamMap,
                      std::function<void(std::vector<unsigned char>)> &callback) {
    std::vector<unsigned char> teamsMsg;
    teamsMsg.push_back(TEAM_UPDATE);
    uint16_t msgSize = htons(teamMap.size() * 2);
    serializeMsgLenShort(teamsMsg, msgSize);
    for (auto& it : teamMap){
        teamsMsg.push_back(it.first);
        teamsMsg.push_back(it.second ? 1 : 0); // isCt = true -> 1 else 0
    }
    callback(std::move(teamsMsg));
}

std::vector<unsigned char> Protocol::handleTeamUpdate(std::function<std::vector<unsigned char>(size_t)> &callback) {
    std::vector<unsigned char> msg = callback(2);
    return callback(deserializeMsgLenShort(msg));
}

std::map<uint8_t, bool> Protocol::deserializeTeams(std::vector<unsigned char> &msg) {
    std::map<uint8_t, bool> teamsById;
    for (size_t i = 0; i < msg.size(); i += 2){
        teamsById.emplace(msg.at(i), msg.at(i + 1));
    }
    return teamsById;
}

std::pair<std::string, std::string> Protocol::deserializeCreateGame(const std::vector<unsigned char> &msg) {
    uint16_t gameNameSize = msg.at(0) << 8 | msg.at(1);
    std::string gameName;
    for (uint16_t i = 2; i < 2 + gameNameSize; ++i){
        gameName.push_back(msg.at(i));
    }
    uint16_t mapNameSize = msg.at(2 + gameNameSize) << 8 | msg.at(3 + gameNameSize);
    std::string mapName;
    for (uint16_t i = gameNameSize + 4; i < gameNameSize + 4 + mapNameSize; ++i){
        mapName.push_back(msg.at(i));
    }
    return std::make_pair(gameName, mapName);
}

std::vector<unsigned char> Protocol::handleStringMsg(std::function<std::vector<unsigned char>(size_t)> &callback) {
    auto stringSize = callback(2);
    return callback(deserializeMsgLenShort(stringSize));
}

std::vector<unsigned char> Protocol::handleShort(std::function<std::vector<unsigned char>(size_t)> &callback) {
    return callback(2);
}

void Protocol::updateMoney(uint16_t money, std::function<void(std::vector<unsigned char>)> &callback) {
    std::vector<unsigned char> moneyVec;
    moneyVec.push_back(MONEY_UPDATE);
    money = htons(money);
    serializeMsgLenShort(moneyVec, money);
    callback(std::move(moneyVec));
}

void Protocol::loginLister(uint8_t commandId,
                           const std::string &loginList,
                           std::function<void(std::vector<unsigned char>)> callback) {
    std::vector<unsigned char> msg;
    msg.push_back(commandId);
    serializeStringMessage(msg, loginList);
    callback(std::move(msg));
}

std::vector<std::string> Protocol::deserializeLoginListMessage(std::vector<unsigned char> &msg) {
    auto charStart = msg.begin();
    auto charEnd = msg.begin();
    std::vector<std::string> games;
    std::string aGame;
    while (charEnd != msg.end()){
        if (*charEnd == '\n'){
            aGame.insert(aGame.begin(), charStart, charEnd);
            charStart = charEnd;
            ++charStart;
            games.push_back(aGame);
            aGame.clear();
        }
        ++charEnd;
    }
    return games;
}
