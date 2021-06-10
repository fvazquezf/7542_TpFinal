#include "./repositorio_de_tableros.h"
#include "../common/ta_te_ti_constantes.h"
#include "../common/ta_te_ti_logica.h"
#include "../common/lock.h"

#include <utility>
#include <string>

RepositorioDeTableros::RepositorioDeTableros() {}

void RepositorioDeTableros::obtenerTablero(
    const std::string &partida, std::string &tablero) {
    Lock lock(this->m);
    tablero = this->tableros[partida];
}

void RepositorioDeTableros::agregarTablero(const std::string &partida) {
    Lock lock(this->m);
    std::pair <std::string, std::string> valor(partida, TABLERO);
    this->tableros.insert(valor);
}

void RepositorioDeTableros::eliminarTablero(const std::string &partida) {
    Lock lock(this->m);
    this->tableros.erase(partida);
}

void RepositorioDeTableros::colocar(
    const std::string &partida, std::pair <int, int> pos, char p) {
    colocar(partida, pos.first, pos.second, p);
}

void RepositorioDeTableros::colocar(
    const std::string &partida, int x, int y, char p) {
    Lock lock(this->m);
    if (this->esPosValida(this->tableros[partida], x, y)) {
        this->tableros[partida][y * N_TABLERO + x] = p;
    }
    this->tableros[partida][N_TABLERO * N_TABLERO] = p;
}

bool RepositorioDeTableros::esPosValida(std::string tablero, int x, int y) {
    if (x < 0 || y < 0 || x >= N_TABLERO || y >= N_TABLERO) {
        return false;
    }
    if (tablero[y * N_TABLERO + x] != PIEZA_NEUTRA) {
        return false;
    }
    return true;
}

void RepositorioDeTableros::piezaTurno(
    const std::string &partida, std::string &res) {
    Lock lock(this->m);
    std::string pieza = " ";
    pieza[0] = this->tableros[partida][N_TABLERO * N_TABLERO];
    res = pieza;
}

void RepositorioDeTableros::obtenerEstado(
    const std::string &partida, char pieza, std::string &estado) {
    Lock lock(this->m);
    TaTeTiLogica l;
    estado = l.obtenerEstado(this->tableros[partida], pieza);
}

RepositorioDeTableros::~RepositorioDeTableros() {}
