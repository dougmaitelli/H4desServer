#pragma comment(lib, "ws2_32.lib")

#include <stdlib.h>
#include <conio.h>

#include "Server.h"
#include "common/Log.h"

using namespace std;

int main(int argc, char *argv[]) {
    Server* server;
    char restartRequested = 0;
    do {
		server = new Server();

		if (!server->initServer()) {
			Log::write(SERVER_ERROR, "Error starting server!");
		}

		if (server->RESTART_SERVER == 1) {
			Log::write(SYSTEM, "Server restart triggered...");
			restartRequested = 1;
		}

		Log::write(SYSTEM, "Cleaning memory...");
		delete server;
    } while(restartRequested == 1);
    
	Log::write(SYSTEM, "Server finalized...");
	while (!_kbhit()) {
	}
    return EXIT_SUCCESS;
}
