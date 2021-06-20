#ifndef GAMESMONITOR_H
#define GAMESMONITOR_H

#include <map>
#include <mutex>
#include "match.h"

/*
 * contenedor de juegos
 * varios hilos acceden de manera concurrente
 * para crear partidas, listarlas
 * unirse, etc etc, asi que deberia estar protegido
 * un monitor para esto es ideal (idea de tp3)
 */

class GamesMonitor {
private:
    std::map<std::string, Match> matches;
    std::mutex gamesMonitorLock;
public:
    GamesMonitor();

    GamesMonitor(const GamesMonitor& other) = delete;
    GamesMonitor& operator=(const GamesMonitor& other) = delete;

    GamesMonitor(GamesMonitor&& other) noexcept;
    GamesMonitor& operator=(GamesMonitor&& other) noexcept;

    bool createMatch(std::string gameName,
                     const std::function<Socket(void)> &handIn,
                     const std::function<void(int8_t)>& response);
    bool joinMatch(const std::string &gameName,
                   const std::function<Socket(void)> &handIn,
                   const std::function<void(int8_t)> &response);

    void stopGames();

    ~GamesMonitor();
};


#endif
