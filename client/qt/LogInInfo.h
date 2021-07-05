#ifndef LOGININFO_H
#define LOGININFO_H
#include <string>
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
private:

};
#endif // LOGININFO_H
