#include "./server_tp.h"
#include <exception>
#include <ostream>

int main(int argc, char *argv[]) {
    try {
        char* port = argv[1];
        TpServer server;
        server(port);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en el hilo main" << std::endl;
    }

    return 0;
}
