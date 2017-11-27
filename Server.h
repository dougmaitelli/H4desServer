/*
 * File:   Server.h
 * Author: Douglas Maitelli
 *
 * Created on December, 4 2010, 20:53
 */

#ifndef SERVER_H
#define	SERVER_H

#include <stdio.h>
#include <sys/types.h>

#ifdef _WIN32
#include <winsock2.h>
#include <Ws2tcpip.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <unistd.h>
#endif

#include <thread>
#include <mutex>
#include <string>
#include <string.h>
#include <vector>

#include "common/Log.h"
#include "Database.h"
#include "world/WorldServer.h"
#include "player/Player.h"
#include "player/Character.h"
#include "assets/Item.h"
#include "party/Guild.h"

#define SERVER_NAME "H4des"

#define DEF_MAX_PLAYERS 5000
#define DEF_MAX_PLAYER_CHARS 5

#define ITEMS_PATH "data/items.csv"
#define MONSTER_PATH "data/monsters.csv"
#define NPCS_PATH "data/npcs.csv"
#define QUESTS_PATH "data/quests.csv"
#define SKILLS_PATH "data/skills.csv"

using namespace std;

class Server {
private:
    unsigned char EXIT_SERVER_PROCCESS;

    int s;
	vector<thread> threads;
    Database* db;

	WorldServer* worldServer;

    mutex playersMutex;
    vector<Player*> players;

	// General
	bool loadServer();
	bool loadConfig();
	void serverLoop();

	// Socket
	int sockInit();
	int sockQuit();
	int sockClose(SOCKET);

	// Player
	void execPacket(Player*, char*);
	bool resetOnlines();
	void addPlayer(int, sockaddr_in*);
	void removePlayer(Player*);
	void refreshPlayer(Player*);

public:
    Server();
    virtual ~Server();

    unsigned char RESTART_SERVER;

    // General
    bool initServer();

	// Player
	vector<Player*> getPlayers();
	void disconnectPlayer(Player*);

    // Search
    Player* findPlayerByName(string);
    Character* findCharacterByName(string);
    Guild* findGuildByName(string);
};

#endif	/* SERVER_H */

