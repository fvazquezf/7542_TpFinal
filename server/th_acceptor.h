#ifndef TH_ACCEPTOR_H_
#define TH_ACCEPTOR_H_

#include "../common/Thread.h"
#include "../common/socket.h"
#include "./th_login.h"
#include "GamesMonitor.h"

#include <atomic>
#include <list>

class ThAcceptor : public Thread {
 private:
  Socket server;
  GamesMonitor& games;
  std::list<ThLogin *> clients;
  bool keep_running;
  void cleanTheads();

 public:
  explicit ThAcceptor(char* port, GamesMonitor& games);
  ~ThAcceptor() override;
  void run() override;
  void stop();
  ThAcceptor(const ThAcceptor&) = delete;
  ThAcceptor& operator=(const ThAcceptor&) = delete;
  ThAcceptor(ThAcceptor&& other) = delete;
  ThAcceptor& operator=(ThAcceptor&& other) = delete;
};

#endif
