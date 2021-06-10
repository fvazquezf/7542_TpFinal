#include "client_tp.h"
#include "../../common/ta_te_ti_logica.h"

#include <string>

#define BUFF_SIZE 256

ClientTp::ClientTp() {
}

void ClientTp::operator()(char* ip, char* port) {
    this->socket.connect(ip, port);
    bool partidaComenzada = false;
    std::string respuesta = "";
    TaTeTiLogica logica;
    while (true) {
        if (!partidaComenzada) {
            // Envio comando
            std::string comando = leerComando();
            enviarComando(comando);
            // Analizo "crear", "unirse" y "listar"
            if (cifrador.esComandoCrear(comando)
            || cifrador.esComandoUnirse(comando)) {
                partidaComenzada = true;
            } else if (cifrador.esComandoListar(comando)) {
                recibirRespuesta(respuesta);
                std::cout << respuesta;
            }
        } else {
            // Recibo respuesta
            int n = recibirRespuesta(respuesta);
            std::cout << respuesta;
            if (n < 0 || n > 128) {
                break;
            }
            // Envio comando
            std::string comando = leerComando();
            enviarComando(comando);
        }
    }
}


std::string ClientTp::leerComando() {
    std::string msj_entrada;
    std::getline(std::cin, msj_entrada);
    return msj_entrada;
}


int ClientTp::recibirRespuesta(std::string &res) {
    char largo_imprimible[3];
    this->socket.recv(largo_imprimible, 2);
    int n = descifrador.descifrarLargo((unsigned char*)largo_imprimible);

    char respuesta[BUFF_SIZE];
    int m = this->socket.recv(respuesta, n);
    respuesta[n] = '\0';
    res = respuesta;

    return m;
}

int ClientTp::enviarComando(std::string comando) {
    char cifrado[BUFF_SIZE];
    int n = cifrador.cifrarComando(comando, (unsigned char*) cifrado);

    return this->socket.send(cifrado, n);
}


ClientTp::~ClientTp() {
    this->socket.close();
}
