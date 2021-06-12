#ifndef THREAD_H
#define THREAD_H

#include <thread>

class Thread {
private:
    std::thread handler;
protected:
    virtual void run() = 0;
public:
    Thread() = default;

    Thread(const Thread& other) = delete;
    Thread& operator= (const Thread& other) = delete;

    Thread(Thread&& other) noexcept;
    Thread& operator= (Thread&& other) noexcept;

    void start();
    void join();

    virtual ~Thread() = default;
};


#endif
