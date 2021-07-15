#ifndef SERVER_H_
#define SERVER_H_

#include "./th_acceptor.h"
#define SERV_CONFIG_PATH "/var/cs2d/config/server_config.yaml"

class Server {
 public:
  Server();
  void operator()(char *port);
  ~Server();
};

#endif    // SERVER_H_
