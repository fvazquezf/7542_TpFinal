#ifndef PARTIDAS_DISPONIBLES_H_
#define PARTIDAS_DISPONIBLES_H_

#include "../common/lock.h"

#include <unordered_set>
#include <mutex>
#include <string>

class PartidasDisponibles {
 public:
      PartidasDisponibles();
      void agregar(const std::string &partida);
      void obtener(std::string &partidasDisponibles);
      void eliminar(const std::string &partida);
      ~PartidasDisponibles();

 private:
      std::mutex m;
      std::unordered_set<std::string> set;
};

#endif   // PARTIDAS_DISPONIBLES_H_
