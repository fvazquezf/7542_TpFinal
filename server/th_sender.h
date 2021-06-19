#ifndef TH_SENDER_H_
#define TH_SENDER_H_

#include "../common/thread.h"
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
    //ThSender(Socket &socket, Protocol& protocol, BlockingQueue<std::map<int, std::pair<float, float>>>& updates);
    ThSender(Socket& socket, Protocol& protocol, BlockingQueue<Update>& updates);
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
    //BlockingQueue<std::map<int, std::pair<float, float>>>& updates;
    BlockingQueue<Update>& updateQueue;
};

#endif    // TH_SENDER_H_
