#include "client_tp.h"
#include <exception>
#include <ostream>

int main(int argc, char *argv[]) {
    try {
        char* ip = argv[1];
        char* port = argv[2];

        ClientTp client;
        client(ip, port);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en el hilo main" << std::endl;
    }

    return 0;
}
