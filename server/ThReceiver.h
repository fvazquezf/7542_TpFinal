#ifndef SDL_DEMO_THRECEIVER_H
#define SDL_DEMO_THRECEIVER_H

#include "../common/Thread.h"
#include "../common/socket.h"
#include "../common/Protocol.h"
#include "events/ClientEvent.h"
#include "../common/ProtectedQueue.h"

#include <atomic>
#include <utility>
#include <memory>

class ThReceiver : public Thread {
private:
    Socket& peer;
    std::atomic<bool> is_running;
    Protocol& protocol;
    ProtectedQueue<std::unique_ptr<ClientEvent>>& eventQueue;
    uint8_t userId;
    void handleReceived(uint8_t code, std::vector<unsigned char>& msg);
public:
    explicit ThReceiver(Socket& peer,
                        Protocol& protocol,
                        ProtectedQueue<std::unique_ptr<ClientEvent>>& eventsQueue,
                        uint8_t userId);

    ThReceiver(const ThReceiver& other) = delete;
    ThReceiver& operator=(const ThReceiver& other) = delete;

    ThReceiver(ThReceiver&& other) noexcept;
    ThReceiver& operator=(ThReceiver&& other) noexcept;

    void run() override;

    std::vector<unsigned char> receive(size_t size);

    void stop();

    ~ThReceiver() override;
};


#endif //SDL_DEMO_THRECEIVER_H
