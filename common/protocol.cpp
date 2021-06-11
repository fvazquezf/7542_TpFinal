#include "protocol.h"

Protocol::Protocol(Socket &socket): peer(std::move(socket)) {
}

Protocol::~Protocol() {
}

std::string Protocol::recibirComandoX() {
    std::string comando = recibirComando();
    std::string param1 = recibirNombrePartida();
    return param1;
}

std::string Protocol::recibirComando() {
    int n = 1;
    char comando[2];
    this->peer.recv(comando, n);
    comando[n] = '\0';
    return comando;
}

std::string Protocol::recibirNombrePartida() {
    char s_partida_longitud[3];
    this->peer.recv(s_partida_longitud, 2);
    int n = descifrador.descifrarLargo((unsigned char*)s_partida_longitud);

    char nombre_partida[BUFF_SIZE];
    this->peer.recv(nombre_partida, n);
    nombre_partida[n] = '\0';

    std::cout << "RECIBIDO: " << nombre_partida <<".\n";

    return nombre_partida;
}

std::string Protocol::recibirNickName() {
    return recibirNombrePartida();
}

std::pair<int, int> Protocol::recibirPos() {
    char pos_cifrada[3];
    this->peer.recv(pos_cifrada, 1);
    return descifrador.descifrarPosicionAJugar((unsigned char*)pos_cifrada);
}

int Protocol::enviarRespuesta(std::string respuesta) {
    unsigned char cifrado[BUFF_SIZE];
    int n = cifrador.cifrarRespuesta(respuesta, cifrado);
    return this->peer.send((char*)cifrado, n);
}

bool Protocol::esComandoCrear(std::string comando) {
    return descifrador.esComandoCrear(comando);
}

bool Protocol::esComandoUnirse(std::string comando) {
    return descifrador.esComandoUnir(comando);
}

bool Protocol::esComandoListar(std::string comando) {
    return descifrador.esComandoListar(comando);
}

bool Protocol::esComandoNickname(std::string comando) {
    return descifrador.esComandoNickname(comando);
}
