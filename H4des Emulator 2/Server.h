/* 
 * File:   Server.h
 * Author: DougM
 *
 * Created on 4 de Dezembro de 2010, 20:53
 */

#ifndef SERVER_H
#define	SERVER_H

#include "WorldServer.h"

using namespace std;

class Server {
public:
    Server();
    virtual ~Server();
    bool initServer();
    bool loadServer();
    bool loadConfig();

private:
    unsigned char EXIT_SERVER_PROCCESS;
    unsigned char RESTART_SERVER;

    SOCKET s;
    Database* db;

    vector<Item*> Items;
    vector<Guild*> Guilds;
};

#endif	/* SERVER_H */

