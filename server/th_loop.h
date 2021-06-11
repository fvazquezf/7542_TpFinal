#ifndef TH_LOOP_H_
#define TH_LOOP_H_

#include "../common/thread.h"
#include "../common/socket.h"
#include "../common/protocol.h"
#include "./games.h"

#include <utility>
#include <string>
#include <atomic>

class ThLoop: public Thread {
 public:
    ThLoop(Games &games);
    ~ThLoop();
    virtual void run() override;
    void stop();

 private:
 	 Games games;
	 Socket peer;
    std::atomic<bool> is_running;
};

#endif    // TH_LOOP_H_
