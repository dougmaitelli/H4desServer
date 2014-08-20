#include <conio.h>
#include <windows.h>
#include <cstdio>
#include <iostream>

#include "log.h"

using namespace std;

static int __BACKGROUND = PRETO;
static int __FOREGROUND = BRANCO;

void CorTexto(int Cor) {
    __FOREGROUND = Cor;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Cor + (__BACKGROUND << 4));
}

void FundoTexto(int Cor) {
    __BACKGROUND = Cor;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), __FOREGROUND + (Cor << 4));
}

pthread_mutex_t MutexLOG = PTHREAD_MUTEX_INITIALIZER;

void Log(msg_tipo Tipo, bool completalinha, char* Texto, ...) {
    pthread_mutex_lock(&MutexLOG);
    va_list ap;
    va_start(ap, Texto);
    int spc = 0;
    char Texto2[255];
    char Texto3[255];
    vsprintf(Texto2, Texto, ap);
    va_end(ap);
    switch (Tipo) {
        case LOGO:
            spc = 1;
            break;
        case SHOW_MSG:
            spc = 1;
            break;
        case ERRO_SQL:
            spc = 13;
            break;
        case ERRO:
            spc = 9;
            break;
        case WARN:
            spc = 12;
            break;
        case SYSTEM:
            spc = 11;
            break;
        case ADM_ACTION:
            spc = 15;
            break;
        case GM_ACTION:
            spc = 14;
            break;
        case WADM_ACTION:
            spc = 20;
            break;
        case WGM_ACTION:
            spc = 19;
            break;
        case LOAD:
            spc = 12;
            break;
        case HACK:
            spc = 9;
            break;
        case CLIENT:
            spc = 12;
            break;
    }
    if (completalinha) {
        do {
            strcat(Texto2, " ");
        } while (strlen(Texto2) < (unsigned) (80 - spc));
    }
    strcpy(Texto3, "");
    switch (Tipo) {
        case LOGO:
            CorTexto(VERMELHO);
            printf("               /-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\\ \n");
            printf("              /      ___ ___    _____     .___                  \\ \n");
            printf("              <     /   |   \\  /  |  |  __| _/____   ______     > \n");
            printf("              <    /    ~    \\/   |  |_/ __ |/ __ \\ /  ___/     > \n");
            printf("              <    \\    Y    /    ^   / /_/ \\  ___/ \\___ \\      > \n");
            printf("              <     \\___|_  /\\____   |\\____ |\\___  >____  >     > \n");
            printf("              <           \\/      |__|     \\/    \\/     \\/      > \n");
            printf("              <               E  M  U  L  A  T  O  R            > \n");
            printf("              \\             U  N  I  T     T  E  A  M           / \n");
            printf("               \\-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-/ \n\n");
            break;
        case SHOW_MSG:
            CorTexto(CINZA);
            strcat(Texto3, "");
            strcat(Texto3, Texto2);
            cout << Texto3 << endl;
            break;
        case ERRO_SQL:
            CorTexto(VIOLETA);
            strcat(Texto3, "[ERRO SQL]: ");
            strcat(Texto3, Texto2);
            cout << Texto3 << endl;
            break;
        case ERRO:
            CorTexto(VERMELHO);
            strcat(Texto3, "[ERRO]: ");
            strcat(Texto3, Texto2);
            cout << Texto3 << endl;
            break;
        case WARN:
            CorTexto(AMARELO);
            strcat(Texto3, "[WARNING]: ");
            strcat(Texto3, Texto2);
            cout << Texto3 << endl;
            break;
        case SYSTEM:
            CorTexto(VERDE);
            strcat(Texto3, "[SYSTEM]: ");
            strcat(Texto3, Texto2);
            cout << Texto3 << endl;
            break;
        case ADM_ACTION:
            CorTexto(AZUL);
            strcat(Texto3, "[ADM ACTION]: ");
            strcat(Texto3, Texto2);
            cout << Texto3 << endl;
            break;
        case GM_ACTION:
            CorTexto(AMARELO);
            strcat(Texto3, "[GM ACTION]: ");
            strcat(Texto3, Texto2);
            cout << Texto3 << endl;
            break;
        case WADM_ACTION:
            CorTexto(VERMELHO);
            strcat(Texto3, "[ADM ACTION ERRO]: ");
            strcat(Texto3, Texto2);
            cout << Texto3 << endl;
            break;
        case WGM_ACTION:
            CorTexto(VERMELHO);
            strcat(Texto3, "[GM ACTION ERRO]: ");
            strcat(Texto3, Texto2);
            cout << Texto3 << endl;
            break;
        case LOAD:
            CorTexto(TURQUESA);
            strcat(Texto3, "[LOADING]: ");
            strcat(Texto3, Texto2);
            cout << Texto3 << "\r";
            break;
        case HACK:
            CorTexto(VERMELHO);
            strcat(Texto3, "[HACK]: ");
            strcat(Texto3, Texto2);
            cout << Texto3 << endl;
            break;
        case CLIENT:
            CorTexto(TURQUESA);
            strcat(Texto3, "[CLIENTE]: ");
            strcat(Texto3, Texto2);
            cout << Texto3 << endl;
            break;
    }
    CorTexto(BRANCO);
    FILE* file;
    switch (Tipo) {
        case ERRO_SQL:
            file = fopen("logs/Erro_sql-log.txt", "a+");
            break;
        case ERRO:
            file = fopen("logs/Erro-log.txt", "a+");
            break;
        case WARN:
            file = fopen("logs/Warn-log.txt", "a+");
            break;
        case ADM_ACTION:
            file = fopen("logs/ADM_Action-log.txt", "a+");
            break;
        case GM_ACTION:
            file = fopen("logs/GM_Action-log.txt", "a+");
            break;
        case WGM_ACTION:
            file = fopen("logs/GM_Action-log.txt", "a+");
            break;
        case HACK:
            file = fopen("logs/Cack-log.txt", "a+");
            break;
        case CLIENT:
            file = fopen("logs/Client-log.txt", "a+");
            break;
        default:
            file = NULL;
            break;
    }
    if (file != NULL) {
        SYSTEMTIME st;
        GetSystemTime(&st);
        fprintf(file, "[%d/%d/%d %d:%d:%d]", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);
        fprintf(file, Texto3);
        fputc('\n', file);
        fclose(file);
    }
    pthread_mutex_unlock(&MutexLOG);
}
