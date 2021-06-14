#ifndef USER_H_
#define USER_H_
#include "../common/socket.h"
#include "../common/Protocol.h"
#include "th_sender.h"
#include "ThReceiver.h"

// le pasamos el socket por movimiento
// sender/receiver tendran una referencia
// al socket
class User {
private:
    Protocol protocol;
    Socket socket;
    //ThSender sender;
    ThReceiver receiver;
    bool playing;
public:
    explicit User(Socket socket);

    User(const User& other) = delete;
    User& operator=(const User& other) = delete;

    User(User&& other) noexcept;
    User& operator=(User&& other) noexcept;

    void run();

    void start();
    void join();
    void stop();

    bool isDead();

    ~User();
};

#endif
