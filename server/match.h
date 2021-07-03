#ifndef MATCH_H_
#define MATCH_H_

#include <map>
#include "user.h"
#include "WorldModel.h"
#include "Broadcaster.h"
#include "updates/Update.h"
#include "../common/BlockingQueue.h"
#include "../common/ProtectedQueue.h"
#include "events/ClientEvent.h"

class Match {
public:
    explicit Match(const std::map<int, float>& matchConfig,
                   const std::string& mapName);

    Match(const Match& other) = delete;
    Match& operator=(const Match& other) = delete;

    Match(Match&& other) noexcept;
    Match& operator=(Match&& other) noexcept;

    int8_t addUser(Socket socket);
    void removeUser();
    void removeUsers();
    ~Match();

    void startIfShould();
    void stop();

    int8_t getCurrentPlayerId();

private:
    // cuantos jugadores pueden tener las partidas? 10 max
    std::map<uint8_t, User> users;
    const std::map<int, float>& matchConfig;
    uint8_t maxUsers;

    Broadcaster updates;

    WorldModel world;
    YAML::Node mapInfo;
};

#endif
