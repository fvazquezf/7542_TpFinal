#ifndef PROTOCOLO_TA_TE_TI_H_
#define PROTOCOLO_TA_TE_TI_H_

#include <string>
#include <utility>

#include "./ta_te_ti_constantes.h"

class TaTeTiDescifrador {
 public:
  TaTeTiDescifrador();

  bool esComandoCrear(const char* comando);
  bool esComandoUnir(const char* comando);
  bool esComandoListar(const char* comando);
  bool esComandoJugar(const char* comando);

  bool esComandoCrear(const std::string &comando);
  bool esComandoUnir(const std::string &comando);
  bool esComandoListar(const std::string &comando);
  bool esComandoJugar(const std::string &comando);

  // std::string descifrarNombrePartida(char* comando);
  std::pair<int, int> descifrarPosicionAJugar(unsigned char* comando);
  int descifrarLargo(unsigned char* comando);

  ~TaTeTiDescifrador();
};

#endif    // PROTOCOLO_TA_TE_TI_H_
