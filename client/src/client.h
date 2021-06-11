#ifndef CLIENT_H_
#define CLIENT_H_

#include "../../common/ta_te_ti_cifrador.h"
#include "../../common/ta_te_ti_descifrador.h"
#include "../../common/socket.h"

#include <string>
class Client {
 public:
    Client();
    void operator()(char* ip, char* port);
    ~Client();

 private:
    Socket socket;
    TaTeTiCifrador cifrador;
    TaTeTiDescifrador descifrador;

    int recibirRespuesta(std::string &res);
    int enviarComando(std::string comando);
    std::string leerComando();
};

#endif    // CLIENT_H_
