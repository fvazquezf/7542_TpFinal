#include "./partidas_disponibles.h"
#include <utility>
#include <string>
#include <vector>
#include <algorithm>

PartidasDisponibles::PartidasDisponibles() {}

void PartidasDisponibles:: agregar(const std::string &partida) {
    Lock lock(this->m);
    set.insert(partida);
}

void PartidasDisponibles::obtener(std::string &partidasDisponibles) {
    Lock lock(this->m);
    std::vector<std::string> vect(this->set.begin(), this->set.end());
    std::sort(vect.begin(), vect.end());
    std::string res("Partidas:\n");
    int n = vect.size();
    for (int i = 0; i < n; i++) {
        res = res + " - " + vect[i] + "\n";
    }
    partidasDisponibles = res;
}

void PartidasDisponibles:: eliminar(const std::string &partida) {
    Lock lock(this->m);
    set.erase(partida);
}


PartidasDisponibles::~PartidasDisponibles() {}
