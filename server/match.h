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
    explicit Match(const std::map<int, int>& matchConfig,
                   const std::string& mapName);

    Match(const Match& other) = delete;
    Match& operator=(const Match& other) = delete;

    Match(Match&& other) noexcept;
    Match& operator=(Match&& other) noexcept;

    ~Match();

    void stop();

    bool isGameStarted();

    bool tryAddingUserAndStartIfShould(const std::function<Socket(void)> &socketHandIn,
                                       const std::function<void(int8_t)> &loginResponse);
    std::function<void()> startEarlyCallback;
private:
    // cuantos jugadores pueden tener las partidas? 10 max
    std::map<uint8_t, User> users;
    const std::map<int, int>& matchConfig;
    uint8_t maxUsers;

    Broadcaster updates;

    WorldModel world;
    YAML::Node mapInfo;

    // el match ahora puede ser accedido por
    // gamesMonitor (a traves del login)
    // o por el receiver de algun cliente (por el callback de earlyStart)
    std::mutex matchMutex;
    std::atomic_bool gameStarted;
    // solo accedido mediante callbacks
    void start();
};

#endif
