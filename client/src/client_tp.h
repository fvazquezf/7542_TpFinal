#ifndef CLIENT_TP_H_
#define CLIENT_TP_H_

#include "../../common/ta_te_ti_cifrador.h"
#include "../../common/ta_te_ti_descifrador.h"
#include "../../common/socket.h"

#include <string>
class ClientTp {
 public:
    ClientTp();
    void operator()(char* ip, char* port);
    ~ClientTp();

 private:
    Socket socket;
    TaTeTiCifrador cifrador;
    TaTeTiDescifrador descifrador;

    int recibirRespuesta(std::string &res);
    int enviarComando(std::string comando);
    std::string leerComando();
};

#endif    // CLIENT_TP_H_
