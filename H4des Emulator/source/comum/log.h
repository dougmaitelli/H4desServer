#ifndef LOG_H
#define LOG_H

#include <pthread/pthread.h>

using namespace std;

enum msg_tipo {
     LOGO,
     SHOW_MSG,
     ERRO_SQL,
     ERRO,
     WARN,
     SYSTEM,
     ADM_ACTION,
     GM_ACTION,
     WADM_ACTION,
     WGM_ACTION,
     LOAD,
     HACK,
     CLIENT
};

typedef enum {
    PRETO,
    AZUL_ESCURO,
    VERDE_ESCURO,
    TURQUESA_ESCURO,
    VERMELHO_ESCURO,
    VIOLETA_ESCURO,
    MARROM,
    CINZA,
    CINZA_ESCURO,
    AZUL,
    VERDE,
    TURQUESA,
    VERMELHO,
    VIOLETA,
    AMARELO,
    BRANCO
};

void CorTexto(int Cor);
void FundoTexto(int Cor);
void Log(msg_tipo Tipo, bool completalinha=false, char* Texto=" ", ...);
#endif
