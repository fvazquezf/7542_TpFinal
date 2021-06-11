#include "./ta_te_ti_descifrador.h"

TaTeTiDescifrador::TaTeTiDescifrador() {
}

bool TaTeTiDescifrador::esComandoCrear(const char* comando) {
    return comando[0] == C_CREAR;
}

bool TaTeTiDescifrador::esComandoUnir(const char* comando) {
    return comando[0] == C_UNIRSE;
}

bool TaTeTiDescifrador::esComandoListar(const char* comando) {
    return comando[0] == C_LISTAR;
}

bool TaTeTiDescifrador::esComandoJugar(const char* comando) {
    return comando[0] == C_JUGAR;
}

bool TaTeTiDescifrador::esComandoNickname(const char* comando) {
    return comando[0] == C_NICKNAME;
}

bool TaTeTiDescifrador::esComandoNickname(const std::string &comando) {
    return this->esComandoNickname(comando.c_str());
}

bool TaTeTiDescifrador::esComandoCrear(const std::string &comando) {
    return this->esComandoCrear(comando.c_str());
}

bool TaTeTiDescifrador::esComandoUnir(const std::string &comando) {
    return this->esComandoUnir(comando.c_str());
}

bool TaTeTiDescifrador::esComandoListar(const std::string &comando) {
    return this->esComandoListar(comando.c_str());
}

bool TaTeTiDescifrador::esComandoJugar(const std::string &comando) {
    return this->esComandoJugar(comando.c_str());
}

int TaTeTiDescifrador::descifrarLargo(unsigned char* comando) {
    int largo = comando[0] << 8 | comando[1];
    return largo;
}

std::pair<int, int> TaTeTiDescifrador::descifrarPosicionAJugar(
    unsigned char* comando) {
    int x = (comando[0] >> 4) & ((unsigned char) 0x0F);
    int y = comando[0] & ((unsigned char) 0x0F);
    return std::pair<int, int>(x, y);
}

TaTeTiDescifrador::~TaTeTiDescifrador() {
}
