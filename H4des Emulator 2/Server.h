/*
 * File:   Server.h
 * Author: Douglas Maitelli
 *
 * Created on December, 4 2010, 20:53
 */

#ifndef SERVER_H
#define	SERVER_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include <pthread.h>
#include <string>
#include <string.h>
#include <vector>

#define SERVER_NAME "H4des"

#define DEF_MAX_PLAYERS 5000
#define DEF_MAX_PLAYER_CHARS 5

#define ITEMS_PATH "data/items/items.csv"
#define MONSTER_PATH "data/monsters/monsters.csv"
#define NPCS_PATH "data/npcs/npcs.csv"
#define QUESTS_PATH "data/quests/quests.csv"
#define SKILLS_PATH "data/skills/skills.csv"

using namespace std;

class Log;
class Database;
class WorldServer;
class Player;
class Character;
class Item;
class Guild;

class Server {
private:
    unsigned char EXIT_SERVER_PROCCESS;

    int s;
    Database* db;

    pthread_t thread[65535];

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
    static void* refreshPlayer(void*);

    // Search
    Player* findPlayerByName(string);
    Character* findCharacterByName(string);
    Guild* findGuildByName(string);
};

#endif	/* SERVER_H */

