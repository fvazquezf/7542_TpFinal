#ifndef TA_TE_TI_CIFRADOR_
#define TA_TE_TI_CIFRADOR_

#include <string>

#include "./ta_te_ti_constantes.h"

class TaTeTiCifrador {
 public:
  TaTeTiCifrador();

  bool esComandoCrear(const std::string &comando);
  bool esComandoUnirse(const std::string &comando);
  bool esComandoListar(const std::string &comando);
  bool esComandoJugar(const std::string &comando);

  int cifrarComando(const std::string &comando, unsigned char* cifrado);
  int cifrarRespuesta(const std::string &comando, unsigned char* cifrado);

  void cifrarLargo(unsigned char* cifrado, int pos, int largo_partida);

  ~TaTeTiCifrador();

 private:
  int cifrarNombrePartida(std::string comando, unsigned char* cifrado);
  void cifrarPosicionAJugar(std::string comando, unsigned char* cifrado);
  void cifrarLenthString(std::string comando, unsigned char* cifrado);
};

#endif    // TA_TE_TI_CIFRADOR_
