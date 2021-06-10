#include "./th_sender.h"
#include "../common/ta_te_ti_logica.h"
#include <atomic>
#include <string>
#include <string.h>

#define BUFF_SIZE 256

ThSender::ThSender(Socket &socket, PartidasDisponibles &partidas,
                    RepositorioDeTableros &repo): peer(std::move(socket)) {
    this->partidas = &partidas;
    this->repo = &repo;
    this->keep_talking = true;
}

ThSender::~ThSender() {
}

void ThSender::run() {
    TaTeTiLogica l;

    std::string turno = "X";

    std::string mensaje;
    std::string comando;

    while (!this->isDead()) {
        if (partida == "") {
            comando = recibirComando();
            if (descifrador.esComandoCrear(comando)) {
                pieza = 'O';
                partida = recibirNombrePartida();
                repo->agregarTablero(partida);
                partidas->agregar(partida);
                partidas->obtener(mensaje);
            } else if (descifrador.esComandoUnir(comando)) {
                pieza = 'X';
                partida = recibirNombrePartida();
            } else if (descifrador.esComandoListar(comando)) {
                this->partidas->obtener(mensaje);
                enviarRespuesta(mensaje);
            }
        } else {
            if (this->estado() != "") {
                break;
            }
            this->repo->piezaTurno(partida, turno);
            if (turno[0] == pieza) {
                this->repo->piezaTurno(partida, turno);
                continue;
            }
            if (this->estado() != "") {
                break;
            }

            this->repo->obtenerTablero(partida, mensaje);
            enviarRespuesta(l.imprimiblePartida(mensaje));

            comando = recibirComando();
            if (descifrador.esComandoJugar(comando.c_str())) {
                repo->colocar(partida, recibirPos(), pieza);
            }
        }
    }

    this->repo->obtenerTablero(partida, mensaje);
    std::string mensajeFinal = l.imprimiblePartida(mensaje) + this->estado();
    enviarRespuesta(mensajeFinal);
    partidas->eliminar(partida);
    repo->eliminarTablero(partida);
    this->stop();
    this->is_running = false;
}

bool ThSender::isDead() {
    return keep_talking == false;
}

void ThSender::stop() {
    this->keep_talking = false;
    this->peer.close();
}
std::string ThSender::estado() {
    std::string estado;
    this->repo->obtenerEstado(partida, pieza, estado);
    return estado;
}

std::string ThSender::recibirComando() {
    int n = 1;
    char comando[2];
    this->peer.recv(comando, n);
    comando[n] = '\0';
    return comando;
}

std::string ThSender::recibirNombrePartida() {
    char s_partida_longitud[3];
    this->peer.recv(s_partida_longitud, 2);
    int n = descifrador.descifrarLargo((unsigned char*)s_partida_longitud);

    char nombre_partida[BUFF_SIZE];
    this->peer.recv(nombre_partida, n);
    nombre_partida[n] = '\0';

    return nombre_partida;
}

std::pair<int, int> ThSender::recibirPos() {
    char pos_cifrada[3];
    this->peer.recv(pos_cifrada, 1);
    return descifrador.descifrarPosicionAJugar((unsigned char*)pos_cifrada);
}

int ThSender::enviarRespuesta(std::string respuesta) {
    unsigned char cifrado[BUFF_SIZE];
    int n = cifrador.cifrarRespuesta(respuesta, cifrado);
    return this->peer.send((char*)cifrado, n);
}
