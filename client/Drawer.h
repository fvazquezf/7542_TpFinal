#ifndef DRAWER_H
#define DRAWER_H

#include <atomic>
#include "../common/Thread.h"
#include "WorldView.h"

class Drawer : public Thread{
private:
    WorldView& world;
    std::atomic_bool running;

    void run() override;
public:
    explicit Drawer(WorldView& world);

    void stop();
};


#endif
