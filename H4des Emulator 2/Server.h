/* 
 * File:   Server.h
 * Author: DougM
 *
 * Created on 4 de Dezembro de 2010, 20:53
 */

#ifndef SERVER_H
#define	SERVER_H

#include <windows.h>

#include "WorldServer.h"

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

    vector<player_base*> Players;
    vector<items_base*> Items;
    vector<guilds_base*> Guilds;
};

#endif	/* SERVER_H */

