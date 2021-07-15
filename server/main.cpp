#include "./server.h"
#include <exception>
#include <ostream>

int main(int argc, char *argv[]) {
    if (argc != 2){
        std::cerr << "Uso: cs2d_server 'PORT'\n";
        return -1;
    }
    try {
        char* port = argv[1];
        Server server;
        server(port);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en el hilo main" << std::endl;
    }

    return 0;
}
