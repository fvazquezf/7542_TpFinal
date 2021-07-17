#ifndef LOGININFO_H
#define LOGININFO_H
#include <string>
#include <vector>
#include "../common/socket.h"

class LogInInfo
{

public:
    std::string map;
    Socket socket;
    LogInInfo();
    ~LogInInfo();

    std::vector<unsigned char> receive(size_t size);
    void send(std::vector<unsigned char> msg);

    std::vector<std::string> receiveGameInformation();

    void sendJoinGameInfo(std::string selectedGame);

    void sendCreateGameInfo(std::string gameName, std::string mapName);
};
#endif // LOGININFO_H
