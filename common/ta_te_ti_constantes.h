#ifndef TA_TE_TI_CONSTANTES_H_
#define TA_TE_TI_CONSTANTES_H_

#define TABLERO "         X"
#define TABLERO_LEN 10
#define PIEZA_NEUTRA ' '
#define N_TABLERO 3

#define C_CREAR 0x6E
#define C_UNIRSE 0x6A
#define C_LISTAR 0x6C
#define C_JUGAR 0x70
#define C_NICKNAME 0x72
#define C_COMANDOX 0x71

#define S_CREAR "crear"
#define S_UNIRSE "unirse"
#define S_LISTAR "listar"
#define S_JUGAR "jugar"
#define S_NICKNAME "nickname"
#define S_COMANDOX "comandox"

#define L_CREAR 5
#define L_UNIRSE 6
#define L_LISTAR 6
#define L_JUGAR 5
#define L_NICKNAME 8
#define L_COMANDOX 8

#define C_GANADOR 'G'
#define C_PERDEDOR 'P'
#define C_EMPATE 'E'
#define C_CONTINUA ' '

#define MSJ_GANADOR "Felicitaciones! Ganaste!\n"
#define MSJ_PERDEDOR "Has perdido. Segui intentando!\n"
#define MSJ_EMPATE "La partida ha terminado en empate\n"

#endif    // TA_TE_TI_CONSTANTES_H_
