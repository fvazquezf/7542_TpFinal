#ifndef LOCK_H_
#define LOCK_H_

#include <mutex>

class Lock {
 private:
   std::mutex &m;

 public:
   explicit Lock(std::mutex &m);
   ~Lock();
};

#endif  // LOCK_H_
