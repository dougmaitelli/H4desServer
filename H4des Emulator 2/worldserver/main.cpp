#include <stdlib.h>

#include "Server.h"

using namespace std;

int main(int argc, char *argv[]) {
    Server* server = new Server();
    pthread_attr_init(&server->at);
    pthread_attr_setdetachstate(&server->at, PTHREAD_CREATE_JOINABLE);
    if (!server->initServer()) {
        Log::write(ERRO, "Erro ao iniciar a classe Server!");
    }
    pthread_attr_destroy(&server->at);
    if (server->RESTART_SERVER == 1) {
        Log::write(SYSTEM, "Agendando reinicializacao do server...");
        Sleep(5000);
        char argumento[80];
        sprintf(argumento, "start \"%s\" \"%s\"", argv[0], argv[0]);
        system(argumento);
    }
    delete server;
    Log::write(SYSTEM, "Limpando memoria...");
    Log::write(SYSTEM, "Server finalizado...");
    return EXIT_SUCCESS;
}
