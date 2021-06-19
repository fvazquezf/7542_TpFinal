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

    void addUser(Socket socket);
    void removeUser();
    void removeUsers();
    ~Match();

    void startIfShould();
    void stop();

private:
    uint8_t maxUsers;
    // cuantos jugadores pueden tener las partidas? 10 max
    std::map<uint8_t, User> users;

    // Match es el owner de las colas de update
    // cada SENDER popea de estas
    // el broadcaster tiene una referencia a este mapa
    std::map<uint8_t, BlockingQueue<Update>> updateQs;

    // cola no bloqueante para eventos de los usuarios
    ProtectedQueue<std::unique_ptr<ClientEvent>> usersEvents;

    Broadcaster updates;

    //WorldModel world;
};

#endif
