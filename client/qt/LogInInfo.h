#ifndef LOGININFO_H
#define LOGININFO_H
#include <string>
#include <vector>
#include "../common/socket.h"

class LogInInfo
{

public:
    std::string map;
    std::string username;
    std::string ip;
    std::string port;
    Socket socket;
    LogInInfo();
    ~LogInInfo();

    std::vector<unsigned char> receive(size_t size);
    void send(std::vector<unsigned char> msg);

    std::vector<std::string> receiveGameInformation();

};
#endif // LOGININFO_H
