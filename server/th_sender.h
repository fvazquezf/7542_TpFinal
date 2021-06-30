#ifndef TH_SENDER_H_
#define TH_SENDER_H_

#include "../common/Thread.h"
#include "../common/socket.h"
#include "../common/Protocol.h"
#include "../common/BlockingQueue.h"
#include "updates/Update.h"

#include <utility>
#include <string>
#include <atomic>
#include <map>

class ThSender : public Thread {
public:
    ThSender(Socket& socket, Protocol& protocol, BlockingQueue<std::shared_ptr<Update>>& updates);
    ~ThSender() override;
    void run() override;
    void stop();
    bool isDead();
   
    ThSender(const ThSender&) = delete;
    ThSender& operator=(const ThSender&) = delete;

    ThSender(ThSender&& other) noexcept;
    ThSender& operator=(ThSender&& other) noexcept;

private:
    std::atomic<bool> is_running;
    Socket& peer;
    Protocol& protocol;
    BlockingQueue<std::shared_ptr<Update>>& updateQueue;

    void send(std::vector<unsigned char> msg);
};

#endif    // TH_SENDER_H_
