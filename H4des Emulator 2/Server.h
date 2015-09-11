/* 
 * File:   Server.h
 * Author: DougM
 *
 * Created on 4 de Dezembro de 2010, 20:53
 */

#ifndef SERVER_H
#define	SERVER_H

#include <pthread.h>

#include "WorldServer.h"

#define SERVER_NAME "H4des"

#define MAX_PLAYERS 5000
#define MAX_PLAYER_CHARS 5

#define DATA_FOLDER "data/"

#define ITEMS_PATH DATA_FOLDER + "items/items.csv"
#define MONSTER_PATH DATA_FOLDER + "monsters/monsters.csv"
#define NPCS_PATH DATA_FOLDER + "npcs/npcs.csv"
#define QUESTS_PATH DATA_FOLDER + "quests/quests.csv"
#define SKILLS_PATH DATA_FOLDER + "skills/skills.csv"

using namespace std;

class Server {
private:
    unsigned char EXIT_SERVER_PROCCESS;
    unsigned char RESTART_SERVER;

    SOCKET s;
    Database* db;

    pthread_mutex_t playersMutex;
    vector<Player*> players;
    vector<Item*> items;
    vector<Guild*> guilds;

public:
    Server();
    virtual ~Server();

    pthread_attr_t at;

    // General
    bool initServer();
    bool loadServer();
    bool loadConfig();
    void serverLoop();

    // Data
    bool loadItems();
    bool loadMonsters();
    bool loadNPCS();
    bool loadQuests();
    bool loadSkills();
    bool loadGuilds();

    // Player
    bool resetOnlines();
    void addPlayer(SOCKET, sockaddr_in*);
    void removePlayer(Player*);
    void disconnectPlayer(Player*);
};

#endif	/* SERVER_H */

