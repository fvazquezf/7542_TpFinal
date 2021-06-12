#ifndef SOCKET_H_
#define SOCKET_H_

#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include <string>
#include <iostream>
#include <exception>
#include <cstdlib>

class Socket{
 public:
    Socket();
    Socket& operator=(Socket&& other);
    Socket(Socket&& other);
    Socket(const Socket&) = delete;
	 Socket& operator=(const Socket&) = delete;
    int send(const char* buffer, ssize_t len);
    int recv(char* buffer, ssize_t length);
    void bind(const char* port);
    void listen();
    Socket accept();
    void connect(const char* host, const char* service);
    void close();
    void shutdown(int channel);
    ~Socket();

 protected:
    explicit Socket(int file_descriptor);
    int sfd = -1;
};

#endif    // SOCKET_H_
