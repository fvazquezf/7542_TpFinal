#ifndef USER_H_
#define USER_H_
#include "../common/socket.h"
#include "./th_sender.h"

class User {
 public:
  User(Socket socket);
  void run();
  void start();
  void join();
  void stop();
  bool isDead();
  ~User();
 private:
 ThSender thSender;
};

#endif    // USER_H_
