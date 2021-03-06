#include "socket.h"

#define ACCEPT_QUEUE_LEN 20

Socket::Socket(int file_descriptor) {
    this->sfd = file_descriptor;
}

Socket::Socket() {
    this->sfd = -1;
}

Socket::Socket(Socket&& other) {
	this->sfd = other.sfd;
	other.sfd = -1;
}

Socket& Socket::operator=(Socket&& other) {
     if (this == &other) {
          return *this;
     }

     if ((this->sfd != -1) && this->sfd != other.sfd) {
         this->close();
     }

     this->sfd = other.sfd;
     other.sfd = -1;
     return *this;
}

int Socket::send(const char* buffer, ssize_t len) {
    int total = 0;

    while (len > total) {
        int bs = ::send(this->sfd, &buffer[total], len-total, MSG_NOSIGNAL);
        if (bs == -1) {
            throw Exception("Socket failed at send, errno: ", errno);
        } else if (bs == 0) {
            return total;
        } else {
            total += bs;
        }
    }
    return total;
}

int Socket::recv(char* buffer, ssize_t length) {
    int total = 0;

    while (length > total) {
        int bytes_recv = ::recv(this->sfd, &buffer[total], length-total, MSG_NOSIGNAL);
        if (bytes_recv == -1) {
            throw Exception("Socket failed at recv, errno: ", errno);
        } else if (bytes_recv == 0) {
            return total;
        } else {
            total += bytes_recv;
        }
    }
    return total;
}


void Socket::connect(const char* host, const char* service) {
    struct addrinfo hints, *server_info, *rp;
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    int error = getaddrinfo(host, service, &hints, &server_info);
    if (error != 0) {
        throw Exception("socket unable to connect 1.");
    }

    for (rp = server_info; rp != nullptr; rp = rp->ai_next) {
        this->sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (this->sfd == -1)
            continue;
        if (::connect(this->sfd, rp->ai_addr, rp->ai_addrlen) != -1)
            break;
        ::close(this->sfd);
    }
    freeaddrinfo(server_info);
    if (rp == nullptr) {
        throw Exception("socket unable to connect 2.");
    }
}


void Socket::bind(const char* port) {
    struct addrinfo hints, *server_info, *rp;
    memset(&hints, 0, sizeof(struct sockaddr));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    int error = getaddrinfo(nullptr, port, &hints, &server_info);

    if (error != 0)
        throw Exception("socket unable to bind 1.");

    for (rp = server_info; rp; rp = rp->ai_next) {
        this->sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (this->sfd == -1)
            continue;
        if (::bind(this->sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;
        ::close(this->sfd);
    }

    freeaddrinfo(server_info);
    if (rp == nullptr)
        throw Exception("socket unable to bind 2.");
}

void Socket::listen() {
    ::listen(this->sfd, ACCEPT_QUEUE_LEN);
}

Socket Socket::accept() {
    int fileDescriptor = ::accept(this->sfd, nullptr, nullptr);
    if (fileDescriptor == -1) {
        throw Exception("Socket will not continue accepting");
    }
    return Socket(fileDescriptor);
}

void Socket::close() {
    if (this->sfd != -1) {
        ::shutdown(this->sfd, SHUT_RDWR);
        ::close(this->sfd);
        this->sfd = -1;
    }
}

void Socket::shutdown(int channel) const {
    if (this->sfd != -1) {
        ::shutdown(this->sfd, channel);
    }
}

Socket::~Socket() {
    if (this->sfd != -1) {
        this->close();
    }
}
