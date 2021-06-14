#ifndef SDL_DEMO_THRECEIVER_H
#define SDL_DEMO_THRECEIVER_H

#include "../common/Thread.h"
#include "../common/socket.h"
#include "../common/Protocol.h"

#include <atomic>
#include <utility>

class ThReceiver : public Thread {
private:
    Socket& peer;
    std::atomic<bool> is_running;
    Protocol& protocol;
    // BlockingQueue<algo>& q1;
    // BlockingQueue<algoMas>& q2;
public:
    explicit ThReceiver(Socket& peer, Protocol& protocol);

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
