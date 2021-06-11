#include "th_loop.h"

ThLoop::ThLoop(Games &games) : games(games), is_running(true) {
}

ThLoop::~ThLoop() {
}

void ThLoop::run() {
    while(this->is_running) {
        // TO-DO
    }
}

void stop() {

}