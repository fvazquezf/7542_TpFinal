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
    Match();
    explicit Match(int playerAmount);

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
    uint8_t maxUsers;
    // cuantos jugadores pueden tener las partidas? 10 max
    std::map<uint8_t, User> users;

    Broadcaster updates;

    WorldModel world;
};

#endif
