#include <unistd.h>
#include "Drawer.h"

Drawer::Drawer(WorldView &world)
: world(world),
  running(true){
}

void Drawer::stop() {
    running = false;
}

void Drawer::run() {
    auto start = std::chrono::steady_clock::now();
    size_t it = 0;
    while (running){
        world.render(it);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<float, std::micro> elapsed = (end - start);
        int rest = FRAMERATE - std::ceil(elapsed.count());

        // me comi unos ricos frames
        if (rest < 0){
            int behind = - rest;
            rest = FRAMERATE - behind % FRAMERATE;
            int lost = behind + rest;
            start += std::chrono::microseconds(lost);
            it += lost / FRAMERATE;
        }
        usleep(rest);
        start += std::chrono::microseconds(FRAMERATE);
        ++it;
    }
}
