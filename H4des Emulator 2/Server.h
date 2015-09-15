/*
 * File:   Server.h
 * Author: Douglas Maitelli
 *
 * Created on December, 4 2010, 20:53
 */

#ifndef SERVER_H
#define	SERVER_H

#include <pthread.h>

#include "world/WorldServer.h"
#include "Database.h"

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

class WorldServer;
class Database;

class Server {
private:
    unsigned char EXIT_SERVER_PROCCESS;

    int s;
    Database* db;

    pthread_mutex_t playersMutex;
    vector<Player*> players;
    vector<Item*> items;
    vector<Guild*> guilds;

public:
    Server();
    virtual ~Server();

    unsigned char RESTART_SERVER;

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
    void addPlayer(int, sockaddr_in*);
    void removePlayer(Player*);
    void disconnectPlayer(Player*);
};

#endif	/* SERVER_H */

