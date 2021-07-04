#ifndef LOGININFO_H
#define LOGININFO_H
#include <string>

class LogInInfo
{

public:
    std::string map;
    std::string username;
    std::string ip;
    std::string port;
    LogInInfo();
    ~LogInInfo();
private:

};
#endif // LOGININFO_H
