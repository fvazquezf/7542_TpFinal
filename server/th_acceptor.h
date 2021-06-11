#ifndef TH_ACCEPTOR_H_
#define TH_ACCEPTOR_H_

#include "../common/thread.h"
#include "../common/socket.h"
#include "./th_login.h"
#include "./games.h"

#include <atomic>
#include <list>

class ThAcceptor : public Thread {
 private:
  Socket server;
  Games games;
  std::list<ThLogin *> clients;
  bool keep_running;
  void cleanTheads();

 public:
  explicit ThAcceptor(char* port, Games games);
  ~ThAcceptor() override;
  void run() override;
  void stop();
  ThAcceptor(const ThAcceptor&) = delete;
  ThAcceptor& operator=(const ThAcceptor&) = delete;
  ThAcceptor(ThAcceptor&& other) = delete;
  ThAcceptor& operator=(ThAcceptor&& other) = delete;
};

#endif    // TH_ACCEPTOR_H_
