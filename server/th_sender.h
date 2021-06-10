#ifndef TH_SENDER_H_
#define TH_SENDER_H_

#include "../common/thread.h"
#include "../common/socket.h"
#include "../common/ta_te_ti_descifrador.h"
#include "../common/ta_te_ti_cifrador.h"

#include "./partidas_disponibles.h"
#include "./repositorio_de_tableros.h"

#include <utility>
#include <string>
#include <atomic>

class ThSender : public Thread {
 public:
    ThSender(Socket &socket, PartidasDisponibles &partidas,
            RepositorioDeTableros &repo);
    ~ThSender() override;
    void run() override;
    void stop();
    bool isDead();

 private:
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_running;
    Socket peer;

    PartidasDisponibles* partidas;
    RepositorioDeTableros* repo;

    TaTeTiDescifrador descifrador;
    TaTeTiCifrador cifrador;

    std::string partida = "";
    char pieza = ' ';

    std::string estado();
    int enviarRespuesta(std::string respuesta);
    std::string recibirComando();
    std::string recibirNombrePartida();
    std::pair<int, int> recibirPos();
};

#endif    // TH_SENDER_H_
