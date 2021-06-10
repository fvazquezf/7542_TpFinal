#include "./ta_te_ti_logica.h"
#include <string>
#include "./ta_te_ti_constantes.h"

#define T1 "    1 . 2 . 3 .\n"
#define T2 "  +---+---+---+\n1 |   |   |   |\n"
#define T3 "  +---+---+---+\n2 |   |   |   |\n"
#define T4 "  +---+---+---+\n3 |   |   |   |\n"
#define T5 "  +---+---+---+\n"
#define TABLERO_STRING T1 T2 T3 T4 T5

TaTeTiLogica::TaTeTiLogica() {
}

bool TaTeTiLogica::esPosicionValida(const std::string &tablero, int x, int y) {
    if (x < 0 || y < 0 || x >= N_TABLERO || y >= N_TABLERO) {
        return false;
    }
    if (tablero[y * N_TABLERO + x] != PIEZA_NEUTRA) {
        return false;
    }
    return true;
}

bool TaTeTiLogica::colocar(std::string &tablero, int x, int y, char pieza) {
    if (!esPosicionValida(tablero, x, y)) {
        return false;
    }
    tablero[y * 3 + x] = pieza;
    return true;
}

std::string TaTeTiLogica::obtenerEstado(
                            const std::string &tablero, char pieza) {
    if (this->esPerdedor(tablero, pieza)) {
        return MSJ_PERDEDOR;
    } else if (this->esGanador(tablero, pieza)) {
        return MSJ_GANADOR;
    } else if (this->esEmpate(tablero)) {
        return MSJ_EMPATE;
    } else {
        return "";
    }
}

char TaTeTiLogica::obtenerGanador(const std::string &tablero, char pieza) {
    for (int i = 0; i < N_TABLERO; i++) {
        if (((tablero[i] == tablero[i+3])
        &&(tablero[i+3] == tablero[i+6]))
        && tablero[i] != PIEZA_NEUTRA) {
            return tablero[i];
        }
        if (((tablero[3*i] == tablero[1+3*i])
        && (tablero[1+3*i] == tablero[2+3*i]))
        && tablero[3*i] != PIEZA_NEUTRA) {
            return tablero[3*i];
        }
    }
    if (((tablero[0] == tablero[4])
    && (tablero[4] == tablero[8]))
    && tablero[8] != PIEZA_NEUTRA) {
        return tablero[0];
    }
    if (((tablero[2] == tablero[4])
    && (tablero[4] == tablero[6]))
    && tablero[6] != PIEZA_NEUTRA) {
        return tablero[2];
    }
    return PIEZA_NEUTRA;
}

bool TaTeTiLogica::esGanador(const std::string &tablero, char pieza) {
    char ganador = this->obtenerGanador(tablero, pieza);
    return ganador != PIEZA_NEUTRA && ganador == pieza;
}

bool TaTeTiLogica::esPerdedor(const std::string &tablero, char pieza) {
    char ganador = this->obtenerGanador(tablero, pieza);
    return ganador != PIEZA_NEUTRA && ganador != pieza;
}

bool TaTeTiLogica::esEmpate(const std::string &tablero) {
    for (int i = 0; i < N_TABLERO * N_TABLERO; i++) {
        if (tablero[i] == PIEZA_NEUTRA) {
            return false;
        }
    }
    return true;
}

std::string TaTeTiLogica::imprimiblePartida(const std::string &tablero) {
    std::string res(TABLERO_STRING);
    for (int i = 0; i < N_TABLERO; i++) {
        for (int j = 0; j < N_TABLERO; j++) {
            res[36+32*j+4*i]= tablero[j * N_TABLERO + i];
        }
    }
    return res;
}

TaTeTiLogica::~TaTeTiLogica() {
}
