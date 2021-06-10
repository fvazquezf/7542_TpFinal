#ifndef THREAD_H
#define THREAD_H

#include <thread>

class Thread {
 public:
    Thread();
    void start();
    void join();
    virtual void run() = 0;
    virtual ~Thread();
 private:
    std::thread thread;
};

#endif    // THREAD_H
