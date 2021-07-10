#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <string>
#include <utility>

// el tipo que entre en la cola tiene que ser movible
template<typename T>
class BlockingQueue {
private:
    bool closed;
    std::queue<T> q;
    std::mutex queueMutex;
    std::condition_variable cv;
public:
    BlockingQueue()
    : closed(false){
    }

    BlockingQueue(const BlockingQueue& other) = delete;
    BlockingQueue& operator=(const BlockingQueue& other) = delete;

    BlockingQueue(BlockingQueue &&other) noexcept
    : closed(other.closed), q(std::move(other.q)){
    }

    BlockingQueue &operator=(BlockingQueue &&other)  noexcept {
        if (this == &other) {
            return *this;
        }
        closed = other.closed;
        q = std::move(other.q);
        return *this;
    }

    bool isNotClosedOrNotEmpty(){
        std::unique_lock<std::mutex> lock1(queueMutex);
        return (!closed || !q.empty());
    }

    void signalClosed(){
        std::lock_guard<std::mutex> lock(queueMutex);
        closed = true;
        cv.notify_all();
    }

    T pop(){
        std::unique_lock<std::mutex> lock1(queueMutex);
        while (q.empty()){
            if (closed){
                // Usar una exception propia.
                throw std::invalid_argument("Queue is closed.\n");
            }
            cv.wait(lock1);
        }
        T elem = std::move(q.front());
        q.pop(); // bye bye
        return elem;
    }

    void push(T queueElement){
        std::unique_lock<std::mutex> lock1(queueMutex);
        q.push(std::move(queueElement));
        cv.notify_all();
    }
};

#endif
