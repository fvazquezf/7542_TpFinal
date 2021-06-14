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

    bool createMatch(std::string gameName);
    bool joinMatch(std::string gameName);

    ~GamesMonitor();
};


#endif
