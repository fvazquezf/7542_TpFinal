#ifndef TH_SENDER_H_
#define TH_SENDER_H_

#include "../common/thread.h"
#include "../common/socket.h"
#include "../common/protocol.h"
#include "./games.h"

#include <utility>
#include <string>
#include <atomic>

class ThSender : public Thread {
 public:
    ThSender(Socket &socket);
    ~ThSender() override;
    void run() override;
    void stop();
    bool isDead();

 private:
    std::atomic<bool> is_running;
    Socket peer;
};

#endif    // TH_SENDER_H_
