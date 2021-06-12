#ifndef SERVER_H_
#define SERVER_H_

#include "./th_acceptor.h"
#include "./th_loop.h"

class Server {
 public:
  Server();
  void operator()(char *port);
  ~Server();
};

#endif    // SERVER_H_
