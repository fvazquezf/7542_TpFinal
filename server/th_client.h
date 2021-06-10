#ifndef TH_CLIENT_H_
#define TH_CLIENT_H_

#include "./th_sender.h"
#include "../common/socket.h"
#include "../common/ta_te_ti_descifrador.h"
#include "../common/ta_te_ti_cifrador.h"
#include "./th_sender.h"
#include "./partidas_disponibles.h"
#include "./repositorio_de_tableros.h"

#include <utility>
#include <string>
#include <atomic>

class ThClient {
 public:
    ThClient(Socket &socket, PartidasDisponibles &partidas,
            RepositorioDeTableros &repo);
    ~ThClient();
    void run();
    void start();
    void join();
    void stop();
    bool isDead();

 private:
    ThSender thSender;
};

#endif    // TH_CLIENT_H_
