/* 
 * File:   Server.cpp
 * Author: DougM
 * 
 * Created on 4 de Dezembro de 2010, 20:53
 */

#include "Server.h"
#include "Log.h"
#include "Database.h"

Server::Server() {
    EXIT_SERVER_PROCCESS = 0;
    RESTART_SERVER = 0;
}

Server::~Server() {
}

Server::initServer() {
    Log::write(LOGO);

    Log::write(LOAD, "[                    ] 0% > Inicializando o WinSock...");
    WSADATA w;
    int error = WSAStartup(MAKEWORD(2, 2), &w);
    if (error) {
        WSACleanup();
        Log::write(ERRO, "A inicializacao do WinSock falhou!");
        MessageBox(NULL, "A inicializacao do WinSock falhou!", "WSAStartup", MB_RETRYCANCEL);
        return false;
    }
    Log::write(LOAD, "[|                   ] 5% > Verificando versao do WinSock...");
    if (w.wVersion != MAKEWORD(2, 2)) {
        WSACleanup();
        Log::write(ERRO, "Versao incorreta do WinSock!");
        MessageBox(NULL, "Versao incorreta do WinSock!", "WSAStartup", MB_RETRYCANCEL);
        return false;
    }
    Log::write(LOAD, "[||                  ] 10% > Criando Socket...");
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        closesocket(s);
        WSACleanup();
        Log::write(ERRO, "Nao foi possivel criar o Socket");
        MessageBox(NULL, "Nao foi possivel criar o Socket!", "Socket", MB_RETRYCANCEL);
        return false;
    }
    Log::write(LOAD, "[|||                 ] 15% > Alterando opcoes do Socket...");
    int option = 1;
    do {
        if (setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, (const char*) &option, sizeof (option)) == -1) {
            closesocket(s);
            WSACleanup();
            Log::write(ERRO, "Erro ao editar op��es do Socket!");
            if (MessageBox(NULL, "Erro ao editar opcoes do Socket!", "Socket", MB_RETRYCANCEL | MB_ICONWARNING) == IDCANCEL) {
                return false;
            }
        } else {
            break;
        }
    } while (true);
    setsockopt(s, IPPROTO_TCP, TCP_NODELAY, (const char*) &option, sizeof (option));
    Log::write(LOAD, "[||||                ] 20% > Preparando servidor...");
    u_short port = 5001;
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    do {
        if (bind(s, (LPSOCKADDR) & addr, sizeof (addr)) == SOCKET_ERROR) {
            closesocket(s);
            WSACleanup();
            Log::write(ERRO, "A funcao \"bind\" falhou...");
            if (MessageBox(NULL, "A funcao \"bind\" falhou...", "WSAStartup", MB_RETRYCANCEL | MB_ICONWARNING) == IDCANCEL) {
                return false;
            }
        } else {
            break;
        }
    } while (true);
    Log::write(LOAD, "[|||||               ] 25% > Preparando recebimento de dados...");
    do {
        if (listen(s, SOMAXCONN) == SOCKET_ERROR) {
            closesocket(s);
            WSACleanup();
            Log::write(ERRO, "A funcao \"listen\" falhou...");
            if (MessageBox(NULL, "A funcao \"listen\" falhou...", "WSAStartup", MB_RETRYCANCEL | MB_ICONWARNING) == IDCANCEL) {
                return false;
            }
        } else {
            break;
        }
    } while (true);
    Log::write(LOAD, "[||||||              ] 30% > Iniciando classe do banco de dados...");
    db = new Database();
    if (!db->init()) {
        Log::write(ERRO, "A inicializacao da classe do banco de dados falhou...");
        return false;
    }
    if (!db->connect()) {
        Log::write(ERRO, "A conexao com o banco de dados falhou...");
        return false;
    }
    if (!ServerLoad()) {
        Log(ERRO, true, "Ocorreu um erro ao carregar os principais dados do server...");
        return false;
    }
    Log::write(SYSTEM, "Server iniciado na porta %i.", port);
    ServerLoop();
    for (UINT i = 0; i < Players.size(); i++) {
        player_base* estecliente = Players.at(i);
        DesconectaPlayer(estecliente);
    }
    db->wait();
    db->close();
    delete db;
    closesocket(s);
    WSACleanup();

    return true;
}

Server::loadServer() {
     Log::write(LOAD, "[||||||||||          ] 50% > Carregando configuracoes do server...");
     if (!LoadConfig()) {
        Log::write(ERRO, "Ocorreu um erro ao carregar as configuracoes do server...");
        return false;
     }
     Log::write(LOAD, "[|||||||||||         ] 55% > Reseetando status dos players...");
     if (!ResetOnlines()) {
         Log::write(ERRO, "Ocorreu um erro ao resetar os status dos players...");
     }
     Log::write(LOAD, "[|||||||||||         ] 60% > Carregando dados dos items...");
     if (!LoadItems()) {
        Log::write(ERRO, "Ocorreu um erro ao carregar dados dos items...");
        return false;
     }
     Log::write(LOAD, "[|||||||||||||       ] 65% > Carregando dados dos monstros...");
     if (!LoadMonsters()) {
        Log::write(ERRO, "Ocorreu um erro ao carregar dados dos monstros...");
        return false;
     }
     Log::write(LOAD, "[||||||||||||||      ] 70% > Carregando dados dos NPCs...");
     if (!LoadNPCS()) {
        Log::write(ERRO, "Ocorreu um erro ao carregar dados dos NPCs...");
        return false;
     }
     Log::write(LOAD, "[||||||||||||||||    ] 80% > Carregando dados das quests...");
     if (!LoadQuests()) {
        Log::write(ERRO, "Ocorreu um erro ao carregar dados das quests...");
        return false;
     }
     Log::write(LOAD, "[||||||||||||||||||  ] 90% > Carregando dados das skills...");
     if (!LoadSkills()) {
        Log::write(ERRO, "Ocorreu um erro ao carregar dados das skills...");
        return false;
     }
     Log::write(LOAD, "[||||||||||||||||||| ] 95% > Carregando dados das guilds...");
     if (!LoadGuilds()) {
        Log::write(ERRO, "Ocorreu um erro ao carregar dados das guilds...");
        return false;
     }
     Log::write(LOAD, "[||||||||||||||||||||] 100% > Carregando dados das guilds...");

     return true;
}

Server::loadConfig() {
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

player_base* Server::GetUser(char* nome)
{
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

player_base* Server::GetPlayer(char* nome)
{
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

guilds_base* Server::GetGuild(char* nome)
{
    for (UINT i=0;i<Guilds.size();i++) {
        guilds_base* guild = Guilds.at(i);
        if (strcasecmp(guild->nome, nome)==0) {
            return guild;
        }
    }
    return NULL;
}

guilds_base* Server::GetGuildId(unsigned long id)
{
    for (UINT i=0;i<Guilds.size();i++) {
        guilds_base* guild = Guilds.at(i);
        if (guild->id == id) {
            return guild;
        }
    }
    return NULL;
}

bool Server::ResetOnlines()
{
    if (!QueryDB("UPDATE users SET online ='0' WHERE online ='1'")) {
        Log(ERRO,true,"Erro ao resetar status online dos usu�rios...");
        return false;
    }
    if (!QueryDB("UPDATE chars SET online ='0' WHERE online ='1'")) {
        Log(ERRO,true,"Erro ao resetar status online dos chars...");
        return false;
    }
    return true;
}

bool Server::LoadItems()
{
     FILE* file;
     char* dados;
     char linha[255];
     file = fopen(ITEMS_PATH, "r");
     if (file == NULL) {
        Log(ERRO,true,"Erro ao abrir arquivo %s...", ITEMS_PATH);
        return false;
     }
     fgets(linha, sizeof(linha), file);
     do {
        items_base* item = new (nothrow) items_base;
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
        Items.push_back(item);
     } while(true);
     fclose(file);
     Log(SYSTEM,true,"Foram carregados %i items.", Items.size());
     return true;
}

bool Server::LoadMonsters()
{
     return true;
}

bool Server::LoadNPCS()
{
     return true;
}

bool Server::LoadQuests()
{
     return true;
}

bool Server::LoadSkills()
{
     return true;
}

bool Server::LoadGuilds()
{
     MYSQL_RES* res;
     MYSQL_ROW row;
     res = QueryResult("SELECT * FROM guilds");
     if (!res) {
         return false;
     }
     while (row = mysql_fetch_row(res)) {
         guilds_base* guild = new (nothrow) guilds_base;
         guild->id = atoi(row[0]);
         sprintf(guild->nome, row[1]);
         guild->lider = atoi(row[2]);
         guild->lvl = atoi(row[3]);
         Guilds.push_back(guild);
     }
     Log(SYSTEM,true,"Foram carregadas %i guilds.", Guilds.size());
     return true;
}

void Server::Cls() {
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}

void Server::ServerLoop()
{
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
			Log(ERRO, false, "A funcao \"select\" falhou... Erro: #%i", WSAGetLastError());
		}
		if (atividade > 0)  {
           if (FD_ISSET(s, &fds) && Players.size() < MAX_PLAYERS) {
              novocliente = accept(s, (sockaddr*)&cliente_sock, &addr_size);
              if (novocliente == INVALID_SOCKET) {
                 Log(ERRO, false, "Erro ao aceitar conexao... Erro: #%i", WSAGetLastError());
              } else {
                 AdicionaPlayer(novocliente, &cliente_sock);
              }
           }
        }
        if (RESTART_SERVER == 1) {
            break;
        }
    } while(EXIT_SERVER_PROCESS != 1);
}

void Server::AdicionaPlayer(SOCKET novocliente, sockaddr_in* client_sock)
{
    player_base* estecliente = new (nothrow)player_base;

    estecliente->logado = false;
    estecliente->ativo = true;

    estecliente->sock = novocliente;
    estecliente->ip = inet_ntoa(client_sock->sin_addr);
    memset(&estecliente->subnet, '\0', 12);
    sprintf(estecliente->subnet, "%li.%li.%li", (client_sock->sin_addr.s_addr)&0xFF,
           (client_sock->sin_addr.s_addr>>8)&0xFF, (client_sock->sin_addr.s_addr>>16)&0xFF);
    Players.push_back(estecliente);
    memcpy(&estecliente->client_sock, client_sock, sizeof(struct sockaddr_in));
    Log(CLIENT, false, "[%i]Cliente conectado em %s subnet: %s!", estecliente->sock, estecliente->ip, estecliente->subnet);
    pthread_create(&thread[novocliente], NULL, AtualizaPlayers, (PVOID)estecliente);
}

PVOID AtualizaPlayers(PVOID estecliente)
{
    fd_set fds;
    player_base* estecliente2 = (player_base*)estecliente;
    do {
        FD_ZERO(&fds);
        FD_SET(estecliente2->sock, &fds);
		int atividade = select(estecliente2->sock+1, &fds, NULL, NULL, NULL);
		if (atividade == SOCKET_ERROR) {
			Log(ERRO, false, "A fun��o \"select\" falhou... Erro: #%i", WSAGetLastError());
		}
		if (atividade > 0) {
		   if (FD_ISSET(estecliente2->sock, &fds)) {
              char buffer[10000];
              int recebido = recv(estecliente2->sock, buffer, sizeof(buffer), 0);
              if (recebido <= 0) {
                 if (estecliente2->ativo) {
                    server->DesconectaPlayer(estecliente2);
                 }
                 break;
              } else {
                 server->PacoteExec(estecliente2, buffer);
              }
           }
        }
    } while(estecliente2->ativo);
    server->DeletaPlayer(estecliente2);
    pthread_exit(NULL);
    return false;
}

void Server::DesconectaPlayer(player_base* estecliente)
{
     if (estecliente->logado) {
        Log(CLIENT, false, "[%i]Cliente %i: %s deslogou-se e foi desconectado!", estecliente->sock, estecliente->id, estecliente->usuario);
     } else {
        Log(CLIENT, false, "[%i]Cliente foi desconectado em %s subnet: %s!", estecliente->sock, estecliente->ip, estecliente->subnet);
     }
     if (!QueryDB("UPDATE users SET online ='0' WHERE id ='%i'", estecliente->id)) {
        Log(ERRO, false, "N�o foi poss�vel atualizar o status do player: %i:%s para offline", estecliente->id, estecliente->usuario);
     }
     if (!QueryDB("UPDATE chars SET online ='0' WHERE user ='%i'", estecliente->id)) {
        Log(ERRO, false, "N�o foi poss�vel atualizar o status do char do player: %i:%s para offline", estecliente->id, estecliente->usuario);
     }
     estecliente->ativo = false;
     closesocket(estecliente->sock);
}

void Server::DeletaPlayer(player_base* estecliente)
{
     pthread_mutex_lock(&MutexDeleta);
     for (UINT i=0;i<Players.size();i++) {
         player_base* outrocliente = Players.at(i);
         if (estecliente == outrocliente) {
            Players.erase(Players.begin()+i);
            delete outrocliente;
            break;
        }
     }
     pthread_mutex_unlock(&MutexDeleta);
}
