#ifndef USER_H_
#define USER_H_

#include "../common/socket.h"
#include "../common/Protocol.h"
#include "../common/BlockingQueue.h"
#include "../common/ProtectedQueue.h"
#include "th_sender.h"
#include "ThReceiver.h"
//#include "PlayerModel.h"
#include "Broadcaster.h"
#include "updates/Update.h"
#include <map>
#include <memory>

// le pasamos el socket por movimiento
// sender/receiver tendran una referencia
// al socket
class User {
private:
    Protocol protocol;
    Socket socket;
    ThSender sender;
    ThReceiver receiver;
    bool playing;
    uint8_t id;
public:
    User(Socket socket,
         ProtectedQueue<std::unique_ptr<ClientEvent>>& eventQueue,
         BlockingQueue<std::shared_ptr<Update>>& updateQueue,
         uint8_t id,
         std::function<void()>& earlyStartCb);

    User(const User& other) = delete;
    User& operator=(const User& other) = delete;

    User(User&& other) noexcept;
    User& operator=(User&& other) noexcept;

    void start();
    void join();
    void stop();

    bool isDead();

    ~User();
};

#endif
