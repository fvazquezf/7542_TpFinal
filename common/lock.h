#ifndef LOCK_H_
#define LOCK_H_

#include <mutex>

class Lock {
 private:
   std::mutex &m;

 public:
   explicit Lock(std::mutex &m);
   Lock(const Lock&) = delete;
   Lock& operator=(const Lock&) = delete;
   Lock(Lock&& other) = delete;
   Lock& operator=(Lock&& other) = delete;
   ~Lock();
};

#endif  // LOCK_H_
