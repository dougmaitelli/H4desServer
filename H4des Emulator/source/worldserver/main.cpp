#include <conio.h>
#include <windows.h>
#include <cstdio>
#include <iostream>

#include "../comum/log.h"
#include "worldserver.h"

using namespace std;

Server* server;

int main(int argc, char *argv[])
{
    server = new (nothrow)Server();
    pthread_attr_init(&server->at);
    pthread_attr_setdetachstate(&server->at, PTHREAD_CREATE_JOINABLE);
    if (!server->InitServer()) {
        Log(ERRO,false,"Erro ao iniciar a classe Server!");
    }
    pthread_attr_destroy(&server->at);
    Log(SYSTEM,false,"Limpando memória...");
    int restart = server->RESTART_SERVER;
    delete server;
    Log(SYSTEM,false,"Server finalizado...");
    if (restart == 1) {
        Sleep(5000);
        char argumento[80];
        sprintf(argumento, "start \"%s\" \"%s\"", argv[0], argv[0]);
        system(argumento);
    } else {
        cin.get();
    }
    return EXIT_SUCCESS;
}
