#include <conio.h>
#include <cstdio>
#include <iostream>
#include <winsock2.h>

#include "../comum/log.h"
#include "worldserver.h"

using namespace std;

Server::Server()
{
    EXIT_SERVER_PROCESS = 0;
    RESTART_SERVER = 0;

    MutexDeleta = PTHREAD_MUTEX_INITIALIZER;
    MutexLoad = PTHREAD_MUTEX_INITIALIZER;
}

Server::~Server()
{
}

bool Server::InitServer()
{
     Log(LOGO);

     SetConsoleTitle("0%");
     Log(LOAD,true,"[                    ] 0% > Inicializando o WinSock...");
     WSADATA w;
     int error = WSAStartup(MAKEWORD(2, 2), &w);
     if (error) {
        WSACleanup();
        Log(ERRO,true,"A inicializacao do WinSock falhou!");
        MessageBox(NULL, "A inicializacao do WinSock falhou!", "WSAStartup", MB_RETRYCANCEL);
        return false;
     }
     SetConsoleTitle("5%");
     Log(LOAD,true,"[|                   ] 5% > Verificando versao do WinSock...");
     if (w.wVersion != MAKEWORD(2, 2)) {
        WSACleanup();
        Log(ERRO,true,"Versao incorreta do WinSock!");
        MessageBox(NULL, "Versao incorreta do WinSock!", "WSAStartup", MB_RETRYCANCEL);
        return false;
     }
     SetConsoleTitle("| 10%");
     Log(LOAD,true,"[||                  ] 10% > Criando Socket...");
     s = socket(AF_INET, SOCK_STREAM, 0);
     if (s == INVALID_SOCKET) {
        closesocket(s);
        WSACleanup();
        Log(ERRO,true,"Nao foi possivel criar o Socket");
        MessageBox(NULL, "Nao foi possivel criar o Socket!", "Socket", MB_RETRYCANCEL);
        return false;
     }
	 SetConsoleTitle("| 15%");
	 Log(LOAD,true,"[|||                 ] 15% > Alterando opcoes do Socket...");
	 int option = 1;
	 do {
         if (setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, (const char*)&option, sizeof(option)) == -1) {
            closesocket(s);
            WSACleanup();
            Log(ERRO,true,"Erro ao editar opções do Socket!");
            if (MessageBox(NULL, "Erro ao editar opcoes do Socket!", "Socket", MB_RETRYCANCEL | MB_ICONWARNING) == IDCANCEL) {
                return false;
            }
         } else {
            break;
         }
     } while(true);
     setsockopt(s, IPPROTO_TCP,TCP_NODELAY, (const char*)&option, sizeof(option));
     SetConsoleTitle("|| 20%");
     Log(LOAD,true,"[||||                ] 20% > Preparando servidor...");
	 u_short port = 5001;
     sockaddr_in addr;
     addr.sin_family = AF_INET;
     addr.sin_port = htons(port);
     addr.sin_addr.s_addr = htonl(INADDR_ANY);
     do {
         if (bind(s, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR) {
            closesocket(s);
            WSACleanup();
            Log(ERRO,true,"A funcao \"bind\" falhou...");
            if (MessageBox(NULL, "A funcao \"bind\" falhou...", "WSAStartup", MB_RETRYCANCEL | MB_ICONWARNING) == IDCANCEL) {
                return false;
            }
         } else {
            break;
         }
     } while(true);
     SetConsoleTitle("|| 25%");
     Log(LOAD,true,"[|||||               ] 25% > Preparando recebimento de dados...");
     do {
         if (listen(s, SOMAXCONN) == SOCKET_ERROR) {
            closesocket(s);
            WSACleanup();
            Log(ERRO,true,"A funcao \"listen\" falhou...");
            if (MessageBox(NULL, "A funcao \"listen\" falhou...", "WSAStartup", MB_RETRYCANCEL | MB_ICONWARNING) == IDCANCEL) {
                return false;
            }
         } else {
            break;
         }
     } while(true);
     SetConsoleTitle("||| 30%");
     Log(LOAD,true,"[||||||              ] 30% > Iniciando classe do banco de dados...");
     if (!InitDB()) {
        Log(ERRO,true,"A inicializacao da classe do banco de dados falhou...");
        return false;
     }
     if (!ServerLoad()) {
        Log(ERRO,true,"Ocorreu um erro ao carregar os principais dados do server...");
        return false;
     }
     SetConsoleTitle("H4des Emulator");
     Log(SYSTEM,true,"Server iniciado na porta %i.", port);
     QueryDB("CREATE TEMPORARY TABLE tbl_name (Id INT)");
     ServerLoop();
     for (UINT i=0;i<Players.size();i++) {
         player_base* estecliente = Players.at(i);
         DesconectaPlayer(estecliente);
     }
     WaitDB();
     CloseDB();
     closesocket(s);
     WSACleanup();
     return true;
}

bool Server::ServerLoad()
{
     SetConsoleTitle("||||| 50%");
     Log(LOAD,true,"[||||||||||          ] 50% > Carregando configuracoes do server...");
     if (!LoadConfig()) {
        Log(ERRO,true,"Ocorreu um erro ao carregar as configuracoes do server...");
        return false;
     }
     SetConsoleTitle("|||||| 55%");
     Log(LOAD,true,"[|||||||||||         ] 55% > Reseetando status dos players...");
     if (!ResetOnlines()) {
         Log(ERRO,true,"Ocorreu um erro ao resetar os status dos players...");
     }
     SetConsoleTitle("|||||| 60%");
     Log(LOAD,true,"[|||||||||||         ] 60% > Carregando dados dos items...");
     if (!LoadItems()) {
        Log(ERRO,true,"Ocorreu um erro ao carregar dados dos items...");
        return false;
     }
     SetConsoleTitle("||||||| 65%");
     Log(LOAD,true,"[|||||||||||||       ] 65% > Carregando dados dos monstros...");
     if (!LoadMonsters()) {
        Log(ERRO,true,"Ocorreu um erro ao carregar dados dos monstros...");
        return false;
     }
     SetConsoleTitle("||||||| 70%");
     Log(LOAD,true,"[||||||||||||||      ] 70% > Carregando dados dos NPCs...");
     if (!LoadNPCS()) {
        Log(ERRO,true,"Ocorreu um erro ao carregar dados dos NPCs...");
        return false;
     }
     SetConsoleTitle("|||||||| 80%");
     Log(LOAD,true,"[||||||||||||||||    ] 80% > Carregando dados das quests...");
     if (!LoadQuests()) {
        Log(ERRO,true,"Ocorreu um erro ao carregar dados das quests...");
        return false;
     }
     SetConsoleTitle("||||||||| 90%");
     Log(LOAD,true,"[||||||||||||||||||  ] 90% > Carregando dados das skills...");
     if (!LoadSkills()) {
        Log(ERRO,true,"Ocorreu um erro ao carregar dados das skills...");
        return false;
     }
     SetConsoleTitle("|||||||||| 95%");
     Log(LOAD,true,"[||||||||||||||||||| ] 95% > Carregando dados das guilds...");
     if (!LoadGuilds()) {
        Log(ERRO,true,"Ocorreu um erro ao carregar dados das guilds...");
        return false;
     }
     SetConsoleTitle("|||||||||| 100%");
     Log(LOAD,true,"[||||||||||||||||||||] 100% > Carregando dados das guilds...");

     return true;
}

bool Server::LoadConfig()
{
     MAX_PLAYERS = GetPrivateProfileInt("Config", "MAX_PLAYERS", 500, ".//config.ini");

     LVL_MAX = GetPrivateProfileInt("Config", "LVL_MAX", 999, ".//config.ini");
     GUILD_LVL_MAX = GetPrivateProfileInt("Config", "GUILD_LVL_MAX", 99, ".//config.ini");
     EXP_MAX = GetPrivateProfileInt("Config", "EXP_MAX", 999999999, ".//config.ini");
     LIFE_MAX = GetPrivateProfileInt("Config", "LIFE_MAX", 999999, ".//config.ini");
     STATS_MAX = GetPrivateProfileInt("Config", "STATS_MAX", 999, ".//config.ini");

     ADM_LVL = GetPrivateProfileInt("Config", "ADM_LVL", 250, ".//config.ini");
     GM_LVL = GetPrivateProfileInt("Config", "GM_LVL", 100, ".//config.ini");

     LVL_PERM = GetPrivateProfileInt("Config", "LVL_PERM", 150, ".//config.ini");
     EXP_PERM = GetPrivateProfileInt("Config", "EXP_PERM", 150, ".//config.ini");
     GOLD_PERM = GetPrivateProfileInt("Config", "GOLD_PERM", 150, ".//config.ini");
     ITEM_PERM = GetPrivateProfileInt("Config", "ITEM_PERM", 150, ".//config.ini");
     BAN_PERM = GetPrivateProfileInt("Config", "BAN_PERM", 250, ".//config.ini");
     UNBAN_PERM = GetPrivateProfileInt("Config", "UNBAN_PERM", 250, ".//config.ini");
     KICK_PERM = GetPrivateProfileInt("Config", "KICK_PERM", 200, ".//config.ini");
     WARN_PERM = GetPrivateProfileInt("Config", "WARN_PERM", 200, ".//config.ini");
     GO_PERM = GetPrivateProfileInt("Config", "GO_PERM", 150, ".//config.ini");
     BUFF_PERM = GetPrivateProfileInt("Config", "BUFF_PERM", 150, ".//config.ini");
     BUY_PERM = GetPrivateProfileInt("Config", "BUY_PERM", 200, ".//config.ini");
     RESTART_PERM = GetPrivateProfileInt("Config", "RESTART_PERM", 300, ".//config.ini");
     RELOADITEM_PERM = GetPrivateProfileInt("Config", "RELOADITEM_PERM", 300, ".//config.ini");
     RELOADNPC_PERM = GetPrivateProfileInt("Config", "RELOADNPC_PERM", 300, ".//config.ini");
     RELOADMONSTER_PERM = GetPrivateProfileInt("Config", "RELOADMONSTER_PERM", 300, ".//config.ini");
     RELOADQUEST_PERM = GetPrivateProfileInt("Config", "RELOADQUEST_PERM", 300, ".//config.ini");
     RELOADSKILL_PERM = GetPrivateProfileInt("Config", "REALOADSKILL_PERM", 300, ".//config.ini");
     RELOADGUILD_PERM = GetPrivateProfileInt("Config", "RELOADGUILD_PERM", 300, ".//config.ini");
     TEMPO_PERM = GetPrivateProfileInt("Config", "TEMPO_PERM", 300, ".//config.ini");
     REPAIR_PERM = GetPrivateProfileInt("Config", "REPAIR_PERM", 150, ".//config.ini");
     SUMMON_PERM = GetPrivateProfileInt("Config", "SUMMON_PERM", 250, ".//config.ini");
     CLEAR_PERM = GetPrivateProfileInt("Config", "CLEAR_PERM", 250, ".//config.ini");
     CALL_PERM = GetPrivateProfileInt("Config", "CALL_PERM", 250, ".//config.ini");
     HEAL_PERM = GetPrivateProfileInt("Config", "HEAL_PERM", 150, ".//config.ini");
     HIDE_PERM = GetPrivateProfileInt("Config", "HIDE_PERM", 250, ".//config.ini");
     MAXSTAT_PERM = GetPrivateProfileInt("Config", "MAXSTAT_PERM", 150, ".//config.ini");
     MAXHAB_PERM = GetPrivateProfileInt("Config", "MAXHAB_PERM", 150, ".//config.ini");
     WHO_PERM = GetPrivateProfileInt("Config", "WHO_PERM", 150, ".//config.ini");
     GUILDLVL_PERM = GetPrivateProfileInt("Config", "GUILDLVL_PERM", 250, ".//config.ini");
     MSG_PERM = GetPrivateProfileInt("Config", "MSG_PERM", 200, ".//config.ini");
     SAVE_PERM = GetPrivateProfileInt("Config", "SAVE_PERM", 150, ".//config.ini");
     A_LVL_PERM = GetPrivateProfileInt("Config", "A_LVL_PERM", 250, ".//config.ini");
     A_EXP_PERM = GetPrivateProfileInt("Config", "A_EXP_PERM", 250, ".//config.ini");
     A_GOLD_PERM = GetPrivateProfileInt("Config", "A_GOLD_PERM", 250, ".//config.ini");
     A_ITEM_PERM = GetPrivateProfileInt("Config", "A_ITEM_PERM", 250, ".//config.ini");
     A_GO_PERM = GetPrivateProfileInt("Config", "A_GO_PERM", 250, ".//config.ini");
     A_BUFF_PERM = GetPrivateProfileInt("Config", "A_BUFF_PERM", 250, ".//config.ini");
     A_REPAIR_PERM = GetPrivateProfileInt("Config", "A_REPAIR_PERM", 250, ".//config.ini");
     A_HEAL_PERM = GetPrivateProfileInt("Config", "A_HEAL_PERM", 250, ".//config.ini");
     A_MAXSTAT_PERM = GetPrivateProfileInt("Config", "A_MAXSTAT_PERM", 250, ".//config.ini");
     A_MAXHAB_PERM = GetPrivateProfileInt("Config", "A_MAXHAB_PERM", 250, ".//config.ini");
     A_GUILDLVL_PERM = GetPrivateProfileInt("Config", "A_GUILDLVL_PERM", 250, ".//config.ini");
     A_SAVE_PERM = GetPrivateProfileInt("Config", "A_SAVE_PERM", 250, ".//config.ini");

     return true;
}

bool Server::ResetOnlines()
{
    if (!QueryDB("UPDATE users SET online ='0' WHERE online ='1'")) {
        Log(ERRO,true,"Erro ao resetar status online dos usuários...");
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
			Log(ERRO, false, "A função \"select\" falhou... Erro: #%i", WSAGetLastError());
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
        Log(ERRO, false, "Não foi possível atualizar o status do player: %i:%s para offline", estecliente->id, estecliente->usuario);
     }
     if (!QueryDB("UPDATE chars SET online ='0' WHERE user ='%i'", estecliente->id)) {
        Log(ERRO, false, "Não foi possível atualizar o status do char do player: %i:%s para offline", estecliente->id, estecliente->usuario);
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
