#ifndef PROTECTEDQUEUE_H
#define PROTECTEDQUEUE_H

#include <queue>
#include <mutex>
#include <utility>

template<typename T>
class ProtectedQueue{
private:
    std::queue<T> q;
    std::mutex queueMutex;
public:
    ProtectedQueue(){}

    ProtectedQueue(const ProtectedQueue& other) = delete;
    ProtectedQueue& operator=(const ProtectedQueue& other) = delete;

    ProtectedQueue(ProtectedQueue &&other) noexcept
    : q(std::move(other.q)){
    }

    ProtectedQueue &operator=(ProtectedQueue &&other)  noexcept {
        if (this == &other) {
            return *this;
        }
        q = std::move(other.q);
        return *this;
    }

    T pop(){
        std::unique_lock<std::mutex> lock1(queueMutex);
        // si la q esta vacia no popeo nada
        // catcheo esta excepcion del lado del mundo
        if (q.empty()){
            throw std::invalid_argument("Queue empty exception\n");
        }
        T elem = std::move(q.front());
        q.pop(); // bye bye
        return elem;
    }

    void push(T queueElement){
        std::unique_lock<std::mutex> lock1(queueMutex);
        q.push(std::move(queueElement));
    }

    void clear(){
        std::unique_lock<std::mutex> lock1(queueMutex);
        std::queue<T> empty;
        std::swap(q, empty);
    }
};

#endif
