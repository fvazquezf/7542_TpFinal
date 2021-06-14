#ifndef MATCH_H_
#define MATCH_H_
#include <map>
#include "user.h"

class Match {
public:
    Match();

    Match(const Match& other) = delete;
    Match& operator=(const Match& other) = delete;

    Match(Match&& other) noexcept;
    Match& operator=(Match&& other) noexcept;

    void addUser(Socket socket);
    void removeUser();
    void removeUsers();
    ~Match();
private:
    uint8_t currUserId;
    // cuantos jugadores pueden tener las partidas?
    // no creo que mas de 256 (por eso uint8)
    std::map<uint8_t, User> users;
};

#endif
