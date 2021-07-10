#include "./server.h"
#include <exception>
#include <ostream>

int main(int argc, char *argv[]) {
    if (argc != 3){
        std::cerr << "Error, numero invalido de argumentos\n";
        // Cuáles son los argumentos esperados? (mejorar el mensaje)
        return -1;
    }
    try {
        char* port = argv[1];
        char* configPath = argv[2];
        Server server;
        server(port, configPath);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en el hilo main" << std::endl;
    }

    return 0;
}
