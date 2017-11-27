/*
 * File:   Server.cpp
 * Author: Douglas Maitelli
 *
 * Created on December, 4 2010, 20:53
 */

#include "Server.h"

Server::Server() {
    EXIT_SERVER_PROCCESS = 0;
    RESTART_SERVER = 0;
}

Server::~Server() {
}

bool Server::initServer() {
    Log::writeLogo();

    Log::writePercentage(10, "Creating socket...");
	this->sockInit();
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
		this->sockClose(s);
		this->sockQuit();
        Log::write(SERVER_ERROR, "Error creating socket");
        return false;
    }

    Log::writePercentage(15, "Setting socket options...");
    int option = 1;
	if (setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, (const char*) &option, sizeof (option)) == -1) {
		this->sockClose(s);
		this->sockQuit();
		Log::write(SERVER_ERROR, "Error setting socket options!");
        return false;
	}
    setsockopt(s, IPPROTO_TCP, TCP_NODELAY, (const char*) &option, sizeof (option));

    Log::writePercentage(20, "Binding server port...");
    u_short port = 5001;
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);
	int bindResult = ::bind(s, (sockaddr*) &addr, sizeof(addr));
	if (bindResult == SOCKET_ERROR) {
		this->sockClose(s);
		this->sockQuit();
		Log::write(SERVER_ERROR, "Error binding server port!");
        return false;
	}

    Log::writePercentage(25, "Starting server listen...");
	if (listen(s, SOMAXCONN) < 0) {
		this->sockClose(s);
		this->sockQuit();
		Log::write(SERVER_ERROR, "Error starting server listen!");
        return false;
	}

    Log::writePercentage(30, "Connecting to the database...");
    db = new Database();
    if (!db->connect()) {
        Log::write(SERVER_ERROR, "Error connecting to the database!");
        return false;
    }

	if (!this->loadServer()) {
		Log::write(SERVER_ERROR, "Error loading server data!");
		return false;
	}

	this->worldServer = new WorldServer(this);
	this->worldServer->loadServer();

	Log::writePercentage(100, "Concluido.");

    Log::write(SYSTEM, "Server started on port %i.", port);
    this->serverLoop();
    for (unsigned int i = 0; i < players.size(); i++) {
        Player* player = players.at(i);
        this->disconnectPlayer(player);
    }

    db->wait();
    db->close();
    delete db;
	this->sockClose(s);
	this->sockQuit();
    return true;
}

int Server::sockInit(void) {
#ifdef _WIN32
	WSADATA wsa_data;
	return WSAStartup(MAKEWORD(1, 1), &wsa_data);
#else
	return 0;
#endif
}

int Server::sockQuit(void) {
#ifdef _WIN32
	return WSACleanup();
#else
	return 0;
#endif
}

int Server::sockClose(SOCKET sock) {
	int status = 0;

#ifdef _WIN32
	status = shutdown(sock, SD_BOTH);
	if (status == 0) { status = closesocket(sock); }
#else
	status = shutdown(sock, SHUT_RDWR);
	if (status == 0) { status = close(sock); }
#endif

	return status;
}

bool Server::loadServer() {
     Log::writePercentage(50, "Loading server config...");
     if (!this->loadConfig()) {
        Log::write(SERVER_ERROR, "Ocorreu um erro ao carregar as configuracoes do server...");
        return false;
     }

     Log::writePercentage(55, "Resetting player status...");
     if (!this->resetOnlines()) {
         Log::write(SERVER_ERROR, "Ocorreu um erro ao resetar os status dos players...");
     }

     return true;
}

//TODO: Create config file handling

bool Server::loadConfig() {
    /*WorldServer::MAX_PLAYERS = GetPrivateProfileInt("Config", "MAX_PLAYERS", 500, ".//config.ini");

    WorldServer::LVL_MAX = GetPrivateProfileInt("Config", "LVL_MAX", 999, ".//config.ini");
    WorldServer::GUILD_LVL_MAX = GetPrivateProfileInt("Config", "GUILD_LVL_MAX", 99, ".//config.ini");
    WorldServer::EXP_MAX = GetPrivateProfileInt("Config", "EXP_MAX", 999999999, ".//config.ini");
    WorldServer::LIFE_MAX = GetPrivateProfileInt("Config", "LIFE_MAX", 999999, ".//config.ini");
    WorldServer::STATS_MAX = GetPrivateProfileInt("Config", "STATS_MAX", 999, ".//config.ini");

    WorldServer::ADM_LVL = GetPrivateProfileInt("Config", "ADM_LVL", 250, ".//config.ini");
    WorldServer::GM_LVL = GetPrivateProfileInt("Config", "GM_LVL", 100, ".//config.ini");

    WorldServer::LVL_PERM = GetPrivateProfileInt("Config", "LVL_PERM", 150, ".//config.ini");
    WorldServer::EXP_PERM = GetPrivateProfileInt("Config", "EXP_PERM", 150, ".//config.ini");
    WorldServer::GOLD_PERM = GetPrivateProfileInt("Config", "GOLD_PERM", 150, ".//config.ini");
    WorldServer::ITEM_PERM = GetPrivateProfileInt("Config", "ITEM_PERM", 150, ".//config.ini");
    WorldServer::BAN_PERM = GetPrivateProfileInt("Config", "BAN_PERM", 250, ".//config.ini");
    WorldServer::UNBAN_PERM = GetPrivateProfileInt("Config", "UNBAN_PERM", 250, ".//config.ini");
    WorldServer::KICK_PERM = GetPrivateProfileInt("Config", "KICK_PERM", 200, ".//config.ini");
    WorldServer::WARN_PERM = GetPrivateProfileInt("Config", "WARN_PERM", 200, ".//config.ini");
    WorldServer::GO_PERM = GetPrivateProfileInt("Config", "GO_PERM", 150, ".//config.ini");
    WorldServer::BUFF_PERM = GetPrivateProfileInt("Config", "BUFF_PERM", 150, ".//config.ini");
    WorldServer::BUY_PERM = GetPrivateProfileInt("Config", "BUY_PERM", 200, ".//config.ini");
    WorldServer::RESTART_PERM = GetPrivateProfileInt("Config", "RESTART_PERM", 300, ".//config.ini");
    WorldServer::RELOADITEM_PERM = GetPrivateProfileInt("Config", "RELOADITEM_PERM", 300, ".//config.ini");
    WorldServer::RELOADNPC_PERM = GetPrivateProfileInt("Config", "RELOADNPC_PERM", 300, ".//config.ini");
    WorldServer::RELOADMONSTER_PERM = GetPrivateProfileInt("Config", "RELOADMONSTER_PERM", 300, ".//config.ini");
    WorldServer::RELOADQUEST_PERM = GetPrivateProfileInt("Config", "RELOADQUEST_PERM", 300, ".//config.ini");
    WorldServer::RELOADSKILL_PERM = GetPrivateProfileInt("Config", "REALOADSKILL_PERM", 300, ".//config.ini");
    WorldServer::RELOADGUILD_PERM = GetPrivateProfileInt("Config", "RELOADGUILD_PERM", 300, ".//config.ini");
    WorldServer::TEMPO_PERM = GetPrivateProfileInt("Config", "TEMPO_PERM", 300, ".//config.ini");
    WorldServer::REPAIR_PERM = GetPrivateProfileInt("Config", "REPAIR_PERM", 150, ".//config.ini");
    WorldServer::SUMMON_PERM = GetPrivateProfileInt("Config", "SUMMON_PERM", 250, ".//config.ini");
    WorldServer::CLEAR_PERM = GetPrivateProfileInt("Config", "CLEAR_PERM", 250, ".//config.ini");
    WorldServer::CALL_PERM = GetPrivateProfileInt("Config", "CALL_PERM", 250, ".//config.ini");
    WorldServer::HEAL_PERM = GetPrivateProfileInt("Config", "HEAL_PERM", 150, ".//config.ini");
    WorldServer::HIDE_PERM = GetPrivateProfileInt("Config", "HIDE_PERM", 250, ".//config.ini");
    WorldServer::MAXSTAT_PERM = GetPrivateProfileInt("Config", "MAXSTAT_PERM", 150, ".//config.ini");
    WorldServer::MAXHAB_PERM = GetPrivateProfileInt("Config", "MAXHAB_PERM", 150, ".//config.ini");
    WorldServer::WHO_PERM = GetPrivateProfileInt("Config", "WHO_PERM", 150, ".//config.ini");
    WorldServer::GUILDLVL_PERM = GetPrivateProfileInt("Config", "GUILDLVL_PERM", 250, ".//config.ini");
    WorldServer::MSG_PERM = GetPrivateProfileInt("Config", "MSG_PERM", 200, ".//config.ini");
    WorldServer::SAVE_PERM = GetPrivateProfileInt("Config", "SAVE_PERM", 150, ".//config.ini");
    WorldServer::A_LVL_PERM = GetPrivateProfileInt("Config", "A_LVL_PERM", 250, ".//config.ini");
    WorldServer::A_EXP_PERM = GetPrivateProfileInt("Config", "A_EXP_PERM", 250, ".//config.ini");
    WorldServer::A_GOLD_PERM = GetPrivateProfileInt("Config", "A_GOLD_PERM", 250, ".//config.ini");
    WorldServer::A_ITEM_PERM = GetPrivateProfileInt("Config", "A_ITEM_PERM", 250, ".//config.ini");
    WorldServer::A_GO_PERM = GetPrivateProfileInt("Config", "A_GO_PERM", 250, ".//config.ini");
    WorldServer::A_BUFF_PERM = GetPrivateProfileInt("Config", "A_BUFF_PERM", 250, ".//config.ini");
    WorldServer::A_REPAIR_PERM = GetPrivateProfileInt("Config", "A_REPAIR_PERM", 250, ".//config.ini");
    WorldServer::A_HEAL_PERM = GetPrivateProfileInt("Config", "A_HEAL_PERM", 250, ".//config.ini");
    WorldServer::A_MAXSTAT_PERM = GetPrivateProfileInt("Config", "A_MAXSTAT_PERM", 250, ".//config.ini");
    WorldServer::A_MAXHAB_PERM = GetPrivateProfileInt("Config", "A_MAXHAB_PERM", 250, ".//config.ini");
    WorldServer::A_GUILDLVL_PERM = GetPrivateProfileInt("Config", "A_GUILDLVL_PERM", 250, ".//config.ini");
    WorldServer::A_SAVE_PERM = GetPrivateProfileInt("Config", "A_SAVE_PERM", 250, ".//config.ini");*/

    return true;
}

//TODO: Create Find Methods

Player* Server::findPlayerByName(string name) {
    /*for (unsigned int i = 0; i < players.size(); i++) {
        player_base* estecliente = Players.at(i);
        if (estecliente->logado) {
            if (strcasecmp(estecliente->usuario,nome) == 0) {
                return estecliente;
            }
        }
    }*/
    return NULL;
}

Character* Server::findCharacterByName(string name) {
    /*for (unsigned int i = 0; i< players.size(); i++) {
        player_base* estecliente = Players.at(i);
        if (estecliente->charsel) {
            if ((strcasecmp(estecliente->usuario,nome) == 0) || (strcasecmp(estecliente->chars[estecliente->chara].nome,nome) == 0)) {
                return estecliente;
            }
        }
    }*/
    return NULL;
}

Guild* Server::findGuildByName(string nome) {
    /*for (unsigned int i=0;i<Guilds.size();i++) {
        guilds_base* guild = Guilds.at(i);
        if (strcasecmp(guild->nome, nome)==0) {
            return guild;
        }
    }*/
    return NULL;
}

//TODO: Create file load functions

void Server::serverLoop() {
    fd_set fds;

	sockaddr_in	cliente_sock;
	socklen_t addr_size = sizeof(sockaddr_in);

    do {
        FD_ZERO(&fds);
        FD_SET(s, &fds);

		timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 1000;

		int activity = select(s + 1, &fds, NULL, NULL, &timeout);
		if (activity < 0) {
			Log::write(SERVER_ERROR, "Error looking for new connection...");
		} else if (activity > 0)  {
           if (FD_ISSET(s, &fds) && players.size() < DEF_MAX_PLAYERS) {
			  int clientSocket = accept(s, (sockaddr*) &cliente_sock, &addr_size);
              if (clientSocket < 0) {
                 Log::write(SERVER_ERROR, "Error accepting new connection...");
              } else {
                 this->addPlayer(clientSocket, &cliente_sock);
              }
           }
        }

        if (RESTART_SERVER == 1) {
            break;
        }
    } while(EXIT_SERVER_PROCCESS != 1);
}

bool Server::resetOnlines() {
    //TODO: Fix Queries
    /*if (!QueryDB("UPDATE users SET online ='0' WHERE online ='1'")) {
        Log::write(SERVER_ERROR, "Erro ao resetar status online dos usu�rios...");
        return false;
    }
    if (!QueryDB("UPDATE chars SET online ='0' WHERE online ='1'")) {
        Log::write(SERVER_ERROR, "Erro ao resetar status online dos chars...");
        return false;
    }*/
    return true;
}

vector<Player*> Server::getPlayers() {
	return this->players;
}

void Server::addPlayer(int clientSocket, sockaddr_in* clientSockAddr) {
    Player* player = new Player(this);

    //player->logado = false;
    player->active = true;

    player->socket = clientSocket;
    strcpy(player->ip, inet_ntoa(clientSockAddr->sin_addr));
    players.push_back(player);
    memcpy(&player->sockeAddr, clientSockAddr, sizeof(sockaddr_in));
    Log::write(CLIENT, "[%i]Client connected in %s!", player->getSocket(), player->getIp());

    this->threads.push_back(std::thread(&Server::refreshPlayer, this, player));
}

void Server::removePlayer(Player* player) {
	std::lock_guard<std::mutex> guard(playersMutex);

    for (unsigned int i = 0; i < players.size(); i++) {
		Player* toPlayer = players.at(i);
		
		if (player == toPlayer) {
           players.erase(players.begin() + i);
           delete toPlayer;
           break;
		}
	}

	playersMutex.unlock();
}

void Server::disconnectPlayer(Player* player) {
    //TODO: Fix Queries
	Log::write(CLIENT, "[%i]Client disconnected in %s!", player->getSocket(), player->getIp());
     /*if (!QueryDB("UPDATE users SET online ='0' WHERE id ='%i'", estecliente->id)) {
        Log::write(SERVER_ERROR, "N�o foi poss�vel atualizar o status do player: %i:%s para offline", estecliente->id, estecliente->usuario);
     }
     if (!QueryDB("UPDATE chars SET online ='0' WHERE user ='%i'", estecliente->id)) {
        Log::write(SERVER_ERROR, "N�o foi poss�vel atualizar o status do char do player: %i:%s para offline", estecliente->id, estecliente->usuario);
     }*/
     player->active = false;
	 sockClose(player->getSocket());
}

void Server::refreshPlayer(Player* player) {
	fd_set fds;

	Server* server = player->getServer();
	
	do {
		FD_ZERO(&fds);
		FD_SET(player->getSocket(), &fds);

		int activity = select(player->getSocket() + 1, &fds, NULL, NULL, NULL);
		if (activity < 0) {
			Log::write(CLIENT, "[%i]Client socket error in %s!", player->getSocket(), player->getIp());
			continue;
		}

		if (FD_ISSET(player->socket, &fds)) {
			char buffer[10000];
			int received = recv(player->socket, buffer, sizeof(buffer), 0);
			if (received <= 0) {
				if (player->active) {
					server->disconnectPlayer(player);
				}
				break;
			} else {
				server->execPacket(player, buffer);
			}
		}
	} while(player->active);

	server->removePlayer(player);
}

void Server::execPacket(Player* player, char* buffer) {
	this->worldServer->playerMessage(player, buffer);
}
