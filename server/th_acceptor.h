#ifndef SOCKET_ACCEPTADOR_H_
#define SOCKET_ACCEPTADOR_H_

#include "../common/thread.h"
#include "../common/socket.h"
#include "./th_client.h"

#include <atomic>
#include <list>
#define BUFF_SIZE 64

class ThAcceptor : public Thread {
 private:
  Socket server;
  std::list<ThClient *> clients;
  bool keep_running;
  void cleanTheads();
 public:
  explicit ThAcceptor(char* port);
  ~ThAcceptor() override;
  void run() override;
  void stop();
};

#endif    // SOCKET_ACCEPTADOR_H_
