#include "./ta_te_ti_cifrador.h"

TaTeTiCifrador::TaTeTiCifrador() {
}

bool TaTeTiCifrador::esComandoCrear(const std::string &comando) {
    return comando.substr(0, L_CREAR) == S_CREAR;
}

bool TaTeTiCifrador::esComandoUnirse(const std::string &comando) {
    return comando.substr(0, L_UNIRSE) == S_UNIRSE;
}

bool TaTeTiCifrador::esComandoListar(const std::string &comando) {
    return comando.substr(0, L_LISTAR) == S_LISTAR;
}

bool TaTeTiCifrador::esComandoJugar(const std::string &comando) {
    return comando.substr(0, L_JUGAR) == S_JUGAR;
}

int TaTeTiCifrador::cifrarComando(
    const std::string &comando, unsigned char* cifrado) {
    int bytes = 0;
    if (this->esComandoCrear(comando)) {
        cifrado[0] = C_CREAR;
        int largo_partida = this->cifrarNombrePartida(comando, cifrado);
        bytes = 3 + largo_partida;
    } else if (this->esComandoUnirse(comando)) {
        cifrado[0] = C_UNIRSE;
        int largo_partida = this->cifrarNombrePartida(comando, cifrado);
        bytes = 3 + largo_partida;
    } else if (this->esComandoListar(comando)) {
        cifrado[0] = C_LISTAR;
        bytes =  1;
    } else if (this->esComandoJugar(comando)) {
        cifrado[0] = C_JUGAR;
        this->cifrarPosicionAJugar(comando, cifrado);
        bytes = 2;
    }
    cifrado[bytes] = '\0';
    return bytes;
}

int TaTeTiCifrador::cifrarRespuesta(
    const std::string &respuesta, unsigned char* cifrado) {
    int largo_respuesta = respuesta.length();
    this->cifrarLargo(cifrado, 0, largo_respuesta);
    for (int i = 0; i < largo_respuesta; i++) {
        cifrado[i + 2] = respuesta[i];
    }
    return largo_respuesta + 2;
}

TaTeTiCifrador::~TaTeTiCifrador() {
}

int TaTeTiCifrador::cifrarNombrePartida(
        std::string comando, unsigned char* cifrado) {
    int cl =  comando.length();
    std::string partida = comando.substr(comando.find(" ")+1, cl);
    int largo_partida = partida.length();
    for (int i = 0; i< largo_partida; i++) {
        cifrado[i + 3] = partida[i];
    }
    this->cifrarLargo(cifrado, 1, largo_partida);
    return largo_partida;
}

void TaTeTiCifrador::cifrarLargo(unsigned char* cifrado, int pos, int largo) {
    cifrado[pos] = largo >> 8;
    cifrado[pos + 1] = largo;
}

void TaTeTiCifrador::cifrarPosicionAJugar(
    std::string comando, unsigned char* cifrado) {
    int cl =  comando.length();
    std::string pos = comando.substr(comando.find(" ")+1, cl);
    std::string pos_x = pos.substr(0, 1);
    std::string pos_y = pos.substr(2, 3);

    int x = pos_x[0] - 48 - 1;
    int y = pos_y[0] - 48 - 1;

    cifrado[1] = x << 4| y;
}
