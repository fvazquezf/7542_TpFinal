#ifndef CLIENT_H
#define CLIENT_H

#include "../common/socket.h"
#include "Sender.h"
#include "sdlwrap/SdlWindow.h"

class Client {
private:
    Socket clientSocket;
    SdlWindow window;
public:
    explicit Client(Socket clientSocket);

    Client(const Client& other) = delete;
    Client& operator=(const Client& other) = delete;

    Client(Client&& other) noexcept;
    Client& operator=(Client&& other) noexcept;

    void launch();


    ~Client();
};


#endif
