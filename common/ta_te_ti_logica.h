#ifndef TA_TE_TI_LOGICA_H_
#define TA_TE_TI_LOGICA_H_
#include <bits/stdc++.h>
#include "./ta_te_ti_constantes.h"

#include <string>
class TaTeTiLogica {
 public:
  TaTeTiLogica();
  bool colocar(std::string &tablero, int x, int y, char pieza);
  std::string obtenerEstado(const std::string &tablero, char pieza);
  std::string imprimiblePartida(const std::string &tablero);
  ~TaTeTiLogica();

 private:
  bool esPosicionValida(const std::string &tablero, int x, int y);
  char obtenerGanador(const std::string &tablero, char pieza);
  bool esGanador(const std::string &tablero, char pieza);
  bool esEmpate(const std::string &tablero);
  bool esPerdedor(const std::string &tablero, char pieza);
};

#endif    // TA_TE_TI_PARTIDA_H_
