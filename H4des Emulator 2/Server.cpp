/*
 * File:   Server.cpp
 * Author: DougM
 *
 * Created on 4 de Dezembro de 2010, 20:53
 */

#include "Server.h"
#include "commom/Log.h"
#include "Database.h"

Server::Server() {
    EXIT_SERVER_PROCCESS = 0;
    RESTART_SERVER = 0;
}

Server::~Server() {
}

bool Server::initServer() {
    Log::write(LOGO);

    Log::write(LOAD, "[||                  ] 10% > Creating socket...");
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        closesocket(s);
        WSACleanup();
        Log::write(MsgType::SERVER_ERROR, "Error creating socket");
        return false;
    }
    Log::write(MsgType::LOAD, "[|||                 ] 15% > Setting socket options...");
    int option = 1;
	if (setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, (const char*) &option, sizeof (option)) == -1) {
		closesocket(s);
		WSACleanup();
		Log::write(MsgType::SERVER_ERROR, "Error setting socket options!");
	}
    setsockopt(s, IPPROTO_TCP, TCP_NODELAY, (const char*) &option, sizeof (option));
    Log::write(LOAD, "[||||                ] 20% > Binding server port...");
    u_short port = 5001;
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(s, (LPSOCKADDR) & addr, sizeof (addr)) == SOCKET_ERROR) {
		closesocket(s);
		WSACleanup();
		Log::write(MsgType::SERVER_ERROR, "Error binding server port!");
	}
    Log::write(LOAD, "[|||||               ] 25% > Starting server listen...");
	if (listen(s, SOMAXCONN) == SOCKET_ERROR) {
		closesocket(s);
		WSACleanup();
		Log::write(MsgType::SERVER_ERROR, "Error starting server listen!");
	}
    Log::write(LOAD, "[||||||              ] 30% > Connecting to the database...");
    db = new Database();
    if (!db->connect()) {
        Log::write(MsgType::SERVER_ERROR, "Error connecting to the database!");
        return false;
    }
    if (!this->loadServer()) {
        Log(MsgType::SERVER_ERROR, true, "Error loading server data!");
        return false;
    }
    Log::write(SYSTEM, "Server started on port %i.", port);
    this->serverLoop();
    for (UINT i = 0; i < players.size(); i++) {
        Player* player = players.at(i);
        this->disconnectPlayer(player);
    }
    db->wait();
    db->close();
    delete db;
    closesocket(s);
    WSACleanup();

    return true;
}

bool Server::loadServer() {
     Log::write(LOAD, "[||||||||||          ] 50% > Carregando configuracoes do server...");
     if (!this->loadConfig()) {
        Log::write(MsgType::SERVER_ERROR, "Ocorreu um erro ao carregar as configuracoes do server...");
        return false;
     }
     Log::write(LOAD, "[|||||||||||         ] 55% > Reseetando status dos players...");
     if (!this->resetOnlines()) {
         Log::write(MsgType::SERVER_ERROR, "Ocorreu um erro ao resetar os status dos players...");
     }
     Log::write(LOAD, "[|||||||||||         ] 60% > Carregando dados dos items...");
     if (!this->loadItems()) {
        Log::write(MsgType::SERVER_ERROR, "Ocorreu um erro ao carregar dados dos items...");
        return false;
     }
     Log::write(LOAD, "[|||||||||||||       ] 65% > Carregando dados dos monstros...");
     if (!this->loadMonsters()) {
        Log::write(MsgType::SERVER_ERROR, "Ocorreu um erro ao carregar dados dos monstros...");
        return false;
     }
     Log::write(LOAD, "[||||||||||||||      ] 70% > Carregando dados dos NPCs...");
     if (!this->loadNPCS()) {
        Log::write(MsgType::SERVER_ERROR, "Ocorreu um erro ao carregar dados dos NPCs...");
        return false;
     }
     Log::write(LOAD, "[||||||||||||||||    ] 80% > Carregando dados das quests...");
     if (!this->loadQuests()) {
        Log::write(MsgType::SERVER_ERROR, "Ocorreu um erro ao carregar dados das quests...");
        return false;
     }
     Log::write(LOAD, "[||||||||||||||||||  ] 90% > Carregando dados das skills...");
     if (!this->loadSkills()) {
        Log::write(MsgType::SERVER_ERROR, "Ocorreu um erro ao carregar dados das skills...");
        return false;
     }
     Log::write(LOAD, "[||||||||||||||||||| ] 95% > Carregando dados das guilds...");
     if (!this->loadGuilds()) {
        Log::write(MsgType::SERVER_ERROR, "Ocorreu um erro ao carregar dados das guilds...");
        return false;
     }
     Log::write(LOAD, "[||||||||||||||||||||] 100% > Carregando dados das guilds...");

     return true;
}

bool Server::loadConfig() {
    WorldServer::MAX_PLAYERS = GetPrivateProfileInt("Config", "MAX_PLAYERS", 500, ".//config.ini");

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
    WorldServer::A_SAVE_PERM = GetPrivateProfileInt("Config", "A_SAVE_PERM", 250, ".//config.ini");

    return true;
}

player_base* Server::GetUser(char* nome) {
    for (UINT i=0;i<Players.size();i++) {
        player_base* estecliente = Players.at(i);
        if (estecliente->logado) {
            if (strcasecmp(estecliente->usuario,nome) == 0) {
                return estecliente;
            }
        }
    }
    return NULL;
}

player_base* Server::GetPlayer(char* nome) {
    for (UINT i=0;i<Players.size();i++) {
        player_base* estecliente = Players.at(i);
        if (estecliente->charsel) {
            if ((strcasecmp(estecliente->usuario,nome) == 0) || (strcasecmp(estecliente->chars[estecliente->chara].nome,nome) == 0)) {
                return estecliente;
            }
        }
    }
    return NULL;
}

guilds_base* Server::GetGuild(char* nome) {
    for (UINT i=0;i<Guilds.size();i++) {
        guilds_base* guild = Guilds.at(i);
        if (strcasecmp(guild->nome, nome)==0) {
            return guild;
        }
    }
    return NULL;
}

bool Server::loadItems() {
     FILE* file;
     char* dados;
     char linha[255];
     file = fopen(ITEMS_PATH, "r");
     if (file == NULL) {
        Log(MsgType::SERVER_ERROR,true,"Erro ao abrir arquivo %s...", ITEMS_PATH);
        return false;
     }
     fgets(linha, sizeof(linha), file);
     do {
        Item* item = new Item();
        fgets(linha, sizeof(linha), file);
        if (feof(file)) {
           break;
        }
        dados = strtok(linha, ";");
        item->id = atoi(dados);
        dados = strtok(linha, ";");
        sprintf(item->nome, dados);
        dados = strtok(linha, ";");
        item->tipo = atoi(dados);
        dados = strtok(linha, ";");
        item->ataque = atoi(dados);
        dados = strtok(linha, ";");
        item->defesa = atoi(dados);
        dados = strtok(linha, ";");
        item->durabilidade = atoi(dados);
        dados = strtok(linha, ";");
        item->hp = atoi(dados);
        dados = strtok(linha, ";");
        item->mp = atoi(dados);
        dados = strtok(linha, ";");
        item->str_req = atoi(dados);
        dados = strtok(linha, ";");
        item->intl_req = atoi(dados);
        dados = strtok(linha, ";");
        item->dex_req = atoi(dados);
        dados = strtok(linha, ";");
        item->agi_req = atoi(dados);
        dados = strtok(linha, ";");
        item->str = atoi(dados);
        dados = strtok(linha, ";");
        item->intl = atoi(dados);
        dados = strtok(linha, ";");
        item->sau = atoi(dados);
        dados = strtok(linha, ";");
        item->per = atoi(dados);
        dados = strtok(linha, ";");
        item->car = atoi(dados);
        dados = strtok(linha, ";");
        item->dex = atoi(dados);
        dados = strtok(linha, ";");
        item->agi = atoi(dados);
        dados = strtok(linha, ";");
        item->magia = atoi(dados);
        dados = strtok(linha, ";");
        item->map_dest = atoi(dados);
        dados = strtok(linha, ";");
        item->x_dest = atoi(dados);
        dados = strtok(linha, ";");
        item->y_dest = atoi(dados);
        dados = strtok(linha, ";");
        item->venda = atoi(dados);

        items.push_back(item);
     } while(true);

     fclose(file);
     Log(SYSTEM, true, "%i items loaded.", items.size());
     return true;
}

bool Server::loadMonsters() {
     return true;
}

bool Server::loadNPCS() {
     return true;
}

bool Server::loadQuests() {
     return true;
}

bool Server::loadSkills() {
     return true;
}

bool Server::loadGuilds() {
     MYSQL_RES* res;
     MYSQL_ROW row;
     res = QueryResult("SELECT * FROM guilds");
     if (!res) {
         return false;
     }
     while (row = mysql_fetch_row(res)) {
         Guild* guild = new Guild();
         guild->id = atoi(row[0]);
         sprintf(guild->nome, row[1]);
         guild->lider = atoi(row[2]);
         guild->lvl = atoi(row[3]);
         guilds.push_back(guild);
     }
     Log(SYSTEM,true,"%i guilds loaded.", guilds.size());
     return true;
}

void Server::serverLoop() {
    SOCKET novocliente;
    sockaddr_in	cliente_sock;
    int addr_size = sizeof(sockaddr_in);
    fd_set fds;
	int atividade;
    timeval timeout;
	int maxfd = s;
    do {
        timeout.tv_sec = 0;
        timeout.tv_usec = 1000;
        FD_ZERO(&fds);
        FD_SET(s, &fds);
		atividade = select(maxfd + 1, &fds, NULL, NULL, &timeout);
		if (atividade == SOCKET_ERROR) {
			Log(MsgType::SERVER_ERROR, false, "Error looking for new connection... Error: #%i", WSAGetLastError());
		}
		if (atividade > 0)  {
           if (FD_ISSET(s, &fds) && players.size() < MAX_PLAYERS) {
              novocliente = accept(s, (sockaddr*)&cliente_sock, &addr_size);
              if (novocliente == INVALID_SOCKET) {
                 Log(MsgType::SERVER_ERROR, false, "Error accepting new connection... Error: #%i", WSAGetLastError());
              } else {
                 this->addPlayer(novocliente, &cliente_sock);
              }
           }
        }
        if (RESTART_SERVER == 1) {
            break;
        }
    } while(EXIT_SERVER_PROCCESS != 1);
}

bool Server::resetOnlines() {
    if (!QueryDB("UPDATE users SET online ='0' WHERE online ='1'")) {
        Log(MsgType::SERVER_ERROR,true,"Erro ao resetar status online dos usu�rios...");
        return false;
    }
    if (!QueryDB("UPDATE chars SET online ='0' WHERE online ='1'")) {
        Log(MsgType::SERVER_ERROR,true,"Erro ao resetar status online dos chars...");
        return false;
    }
    return true;
}

void Server::addPlayer(SOCKET clientSocket, sockaddr_in* clientSockAddr) {
    Player* player = new Player();

    player->logado = false;
    player->active = true;

    player->socket = clientSocket;
    player->ip = inet_ntoa(clientSockAddr->sin_addr);
    memset(&player->subnet, '\0', 12);
    sprintf(player->subnet, "%li.%li.%li", (clientSockAddr->sin_addr.s_addr)&0xFF,
           (clientSockAddr->sin_addr.s_addr>>8)&0xFF, (clientSockAddr->sin_addr.s_addr>>16)&0xFF);
    players.push_back(player);
    memcpy(&player->sockeAddr, clientSockAddr, sizeof(struct sockaddr_in));
    Log(CLIENT, false, "[%i]Client connected in %s subnet: %s!", player->getSocket(), player->getIp(), player->getSubnet());
    pthread_create(&thread[clientSocket], NULL, refreshPlayers, (PVOID) player);
}

void Server::removePlayer(Player* player) {
     pthread_mutex_lock(&playersMutex);

     for (UINT i = 0; i < players.size(); i++) {
         Player* toPlayer = players.at(i);

         if (player == toPlayer) {
            players.erase(players.begin() + i);
            delete toPlayer;
            break;
        }
     }

     pthread_mutex_unlock(&playersMutex);
}

void Server::disconnectPlayer(Player* player) {
	Log(CLIENT, false, "[%i]Client disconnected in %s subnet: %s!", player->getSocket(), player->getIp(), player->getSubnet());
     if (!QueryDB("UPDATE users SET online ='0' WHERE id ='%i'", estecliente->id)) {
        Log(MsgType::SERVER_ERROR, false, "N�o foi poss�vel atualizar o status do player: %i:%s para offline", estecliente->id, estecliente->usuario);
     }
     if (!QueryDB("UPDATE chars SET online ='0' WHERE user ='%i'", estecliente->id)) {
        Log(MsgType::SERVER_ERROR, false, "N�o foi poss�vel atualizar o status do char do player: %i:%s para offline", estecliente->id, estecliente->usuario);
     }
     player->active = false;
     closesocket(player->getSocket());
}

PVOID refreshPlayers(PVOID playerP) {
    fd_set fds;

    Player* player = (Player*) playerP;

    do {
        FD_ZERO(&fds);
        FD_SET(player->socket, &fds);
		int atividade = select(player->socket + 1, &fds, NULL, NULL, NULL);
		if (atividade == SOCKET_ERROR) {
			Log(MsgType::CLIENT, false, "[%i]Client socket error in %s subnet: %s! Error: #%i", player->getSocket(), player->getIp(), player->getSubnet(), WSAGetLastError());
		}
		if (atividade > 0) {
		   if (FD_ISSET(player->socket, &fds)) {
              char buffer[10000];
              int received = recv(player->socket, buffer, sizeof(buffer), 0);
              if (received <= 0) {
                 if (player->active) {
                    server->disconnectPlayer(player);
                 }
                 break;
              } else {
                 server->PacoteExec(player, buffer);
              }
           }
        }
    } while(player->active);

    server->removePlayer(player);
    pthread_exit(NULL);
    return false;
}
