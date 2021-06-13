#ifndef TH_LOGIN_H_
#define TH_LOGIN_H_

#include "../common/thread.h"
#include "../common/socket.h"
//#include "../common/protocol.h"
#include "../common/Protocol.h"
#include "./games.h"
#include "./match.h"

#include <utility>
#include <string>
#include <atomic>
#include <iostream>
#include <functional>


class ThLogin: public Thread {
public:
    ThLogin(Socket &peer, Games &games);
    ~ThLogin() override;
    void run() override;
    void stop();
    bool isDead();
    std::vector<unsigned char> receiveMsgs(size_t msgSize);

    ThLogin(const ThLogin&) = delete;
    ThLogin& operator=(const ThLogin&) = delete;
    ThLogin(ThLogin&& other) = delete;
    ThLogin& operator=(ThLogin&& other) = delete;

private:
    Games games;
    Socket peer;
    std::atomic<bool> is_logged_in;
};

#endif    // TH_LOGIN_H_