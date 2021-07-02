#ifndef SERVER_H_
#define SERVER_H_

#include "./th_acceptor.h"

class Server {
 public:
  Server();
  void operator()(char *port, char *configPath);
  ~Server();
};

#endif    // SERVER_H_
