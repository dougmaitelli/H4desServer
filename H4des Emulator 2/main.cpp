#include <stdlib.h>

#include <pthread.h>

#include "Server.h"
#include "commom/Log.h"

using namespace std;

int main(int argc, char *argv[]) {
    Server* server;
    char restartRequested = 0;
    do {
		server = new Server();
		pthread_attr_init(&server->at);
		pthread_attr_setdetachstate(&server->at, PTHREAD_CREATE_JOINABLE);
		if (!server->initServer()) {
			Log::write(SERVER_ERROR, "Error starting server!");
		}
		pthread_attr_destroy(&server->at);
		if (server->RESTART_SERVER == 1) {
			Log::write(SYSTEM, "Server restart triggered...");
			restartRequested = 1;
		}
		Log::write(SYSTEM, "Cleaning memory...");
		delete server;
    } while(restartRequested == 1);
    Log::write(SYSTEM, "Server finalized...");
    return EXIT_SUCCESS;
}
