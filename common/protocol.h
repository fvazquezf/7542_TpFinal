#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include "../common/socket.h"
#include "../common/ta_te_ti_descifrador.h"
#include "../common/ta_te_ti_cifrador.h"

#define BUFF_SIZE 256

class Protocol {
 private:
   Socket peer;
   TaTeTiDescifrador descifrador;
   TaTeTiCifrador cifrador;
 public:
  Protocol(Socket &socket);
  ~Protocol();
  int enviarRespuesta(std::string respuesta);
  std::string recibirComando();
  std::string recibirNombrePartida();
  std::string recibirNickName();
  bool esComandoCrear(std::string comando);
  bool esComandoUnirse(std::string comando);
  bool esComandoListar(std::string comando);  
  std::pair<int, int> recibirPos();
};

#endif    // PROTOCOL_H_
