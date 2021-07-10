#ifndef CLIENT_H
#define CLIENT_H

#include <yaml-cpp/node/node.h>
#include "../common/socket.h"
#include "Sender.h"
#include "sdlwrap/SdlWindow.h"

class Client {
private:
    Socket clientSocket;
    YAML::Node& clientConfig;
    SdlWindow window;
public:
    Client(LogInInfo& login, YAML::Node& clientConfig);

    Client(const Client& other) = delete;
    Client& operator=(const Client& other) = delete;

    Client(Client&& other) noexcept;
    Client& operator=(Client&& other) noexcept;

    void launch();


    ~Client();
};


#endif
