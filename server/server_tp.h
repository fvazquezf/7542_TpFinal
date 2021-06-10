#ifndef SERVER_TP_H_
#define SERVER_TP_H_

#include "./th_acceptor.h"

class TpServer {
 public:
  TpServer();
  void operator()(char *port);
  ~TpServer();
};

#endif    // SERVER_TP_H_
