#include "client.h"

#include <string>

#define BUFF_SIZE 256

Client::Client() {
}

void Client::operator()(char* ip, char* port) {
    this->socket.connect(ip, port);
    bool partidaComenzada = false;
    std::string respuesta = "";
    while (true) {
        if (!partidaComenzada) {
            // Envio comando
            std::string comando = leerComando();
            enviarComando(comando);
            // Analizo "crear", "unirse" y "listar"
            if (cifrador.esComandoUnirse(comando)) {
                partidaComenzada = true;
            }
            recibirRespuesta(respuesta);
            std::cout << respuesta;
        } else {
            // Envio comando
            std::string comando = leerComando();
            enviarComando(comando);
            
            // Recibo respuesta
            int n = recibirRespuesta(respuesta);
            std::cout << respuesta;
            if (respuesta == "q" || n < 0) {
                break;
            }
            
        }
    }
}


std::string Client::leerComando() {
    std::string msj_entrada;
    std::getline(std::cin, msj_entrada);
    return msj_entrada;
}

int Client::recibirRespuesta(std::string &res) {
    char largo_imprimible[3];
    this->socket.recv(largo_imprimible, 2);
    int n = descifrador.descifrarLargo((unsigned char*)largo_imprimible);

    char respuesta[BUFF_SIZE];
    int m = this->socket.recv(respuesta, n);
    respuesta[n] = '\0';
    res = respuesta;

    return m;
}

int Client::enviarComando(std::string comando) {
    char cifrado[BUFF_SIZE];
    int n = cifrador.cifrarComando(comando, (unsigned char*) cifrado);
    return this->socket.send(cifrado, n);
}


Client::~Client() {
    this->socket.close();
}
