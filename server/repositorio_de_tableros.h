#ifndef REPOSITORIO_DE_TABLEROS_H_
#define REPOSITORIO_DE_TABLEROS_H_

#include <unordered_map>
#include <mutex>
#include <string>
#include <utility>

class RepositorioDeTableros {
 public:
      RepositorioDeTableros();
      void agregarTablero(const std::string &partida);
      void colocar(const std::string &partida, int x, int y, char p);
      void colocar(
           const std::string &partida, std::pair <int, int> pos, char p);
      void piezaTurno(
           const std::string &partida, std::string &res);
      void obtenerTablero(
           const std::string &partida, std::string &tablero);
      void obtenerEstado(
           const std::string &partida, char pieza, std::string &estado);
      void eliminarTablero(const std::string &partida);
      ~RepositorioDeTableros();

 private:
      std::mutex m;
      std::unordered_map<std::string, std::string> tableros;
      bool esPosValida(std::string tablero, int x, int y);
};

#endif   // REPOSITORIO_DE_TABLEROS_H_
