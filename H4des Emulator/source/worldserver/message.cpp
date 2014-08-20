#include <conio.h>
#include <windows.h>
#include <cstdio>
#include <iostream>

#include "../comum/log.h"
#include "worldserver.h"

using namespace std;

void Server::SendMessage(player_base* estecliente, char* Menssagem, ...)
{
     va_list ap;
     va_start(ap, Menssagem);
     Transfer_Data data;
     vsprintf(data.char1, Menssagem, ap);
     data.comando = 2;
     send(estecliente->sock, (char*)&data, sizeof(data), 0);
     va_end(ap);
}

void Server::SendAll(char* Menssagempt_BR, char* Menssagemen_US, ...)
{
     va_list ap;
     va_start(ap, Menssagemen_US);
     for (UINT i=0;i<Players.size();i++) {
         player_base* estecliente = Players.at(i);
         if (estecliente->logado) {
            Transfer_Data data;
            if (strcmp(estecliente->lang,"pt_BR")==0) {
               vsprintf(data.char1, Menssagempt_BR, ap);
            } else if (strcmp(estecliente->lang,"en_US")==0) {
               vsprintf(data.char1, Menssagemen_US, ap);
            }
            data.comando = 2;
            send(estecliente->sock, (char*)&data, sizeof(data), 0);
         }
     }
     va_end(ap);
}

void Server::SendMessageGuild(unsigned int guildid, char* Menssagempt_BR, char* Menssagemen_US, ...)
{
     va_list ap;
     va_start(ap, Menssagemen_US);
     for (UINT i=0;i<Players.size();i++) {
         player_base* outrocliente = Players.at(i);
         if ((outrocliente->chars[outrocliente->chara].guild == guildid) && outrocliente->logado) {
            Transfer_Data data;
            if (strcmp(outrocliente->lang,"pt_BR")==0) {
               vsprintf(data.char1, Menssagempt_BR, ap);
            } else if (strcmp(outrocliente->lang,"en_US")==0) {
               vsprintf(data.char1, Menssagemen_US, ap);
            }
            data.comando = 2;
            send(outrocliente->sock, (char*)&data, sizeof(data), 0);
         }
     }
     va_end(ap);
}

void Server::SendMessageParty(unsigned int partyid, char* Menssagempt_BR, char* Menssagemen_US, ...)
{
     va_list ap;
     va_start(ap, Menssagemen_US);
     for (UINT i=0;i<Players.size();i++) {
         player_base* outrocliente = Players.at(i);
         if ((outrocliente->chars[outrocliente->chara].party == partyid) && outrocliente->charsel) {
            Transfer_Data data;
            if (strcmp(outrocliente->lang,"pt_BR")==0) {
               vsprintf(data.char1, Menssagempt_BR, ap);
            } else if (strcmp(outrocliente->lang,"en_US")==0) {
               vsprintf(data.char1, Menssagemen_US, ap);
            }
            data.comando = 2;
            send(outrocliente->sock, (char*)&data, sizeof(data), 0);
         }
      }
      va_end(ap);
}

void Server::MenssagemServer(player_base* estecliente, char* Menssagem)
{
     for (UINT i=0;i<Players.size();i++) {
         player_base* outrocliente = Players.at(i);
         if (outrocliente->logado) {
            Transfer_Data data;
            sprintf(data.char1, "%s :> %s", estecliente->chars[estecliente->chara].nome, Menssagem);
            data.comando = 2;
            send(outrocliente->sock, (char*)&data, sizeof(data), 0);
         }
     }
}

bool Server::MenssagemPrivada(player_base* estecliente, char Menssagem[])
{
     char* msg;
     char Menssagem2[255];
     strcpy(Menssagem2, Menssagem);
     if ((msg = strtok(Menssagem, " ,."))==NULL) {
        return false;
     }
     char* player=msg;
     player_base* outrocliente = GetPlayer(player);
     if (outrocliente != NULL) {
        Transfer_Data data;
        CortaStr(Menssagem2, strlen(player)+1);
        sprintf(data.char1, "%s :> %s", estecliente->chars[estecliente->chara].nome, Menssagem2);
        data.comando = 3;
        send(outrocliente->sock, (char*)&data, sizeof(data), 0);
        return true;
     } else {
        return false;
     }
}

void Server::MenssagemGuild(player_base* estecliente, char* Menssagem)
{
     for (UINT i=0;i<Players.size();i++) {
         player_base* outrocliente = Players.at(i);
         if ((outrocliente->chars[outrocliente->chara].guild == estecliente->chars[estecliente->chara].guild) && outrocliente->charsel) {
            Transfer_Data data;
            sprintf(data.char1, "%s :> %s", estecliente->chars[estecliente->chara].nome, Menssagem);
            data.comando = 4;
            send(outrocliente->sock, (char*)&data, sizeof(data), 0);
         }
     }
}

void Server::MenssagemParty(player_base* estecliente, char* Menssagem)
{
     for (UINT i=0;i<Players.size();i++) {
         player_base* outrocliente = Players.at(i);
         if ((outrocliente->chars[outrocliente->chara].party == estecliente->chars[estecliente->chara].party) && outrocliente->charsel) {
            Transfer_Data data;
            sprintf(data.char1, "%s :> %s", estecliente->chars[estecliente->chara].nome, Menssagem);
            data.comando = 5;
            send(outrocliente->sock, (char*)&data, sizeof(data), 0);
         }
      }
}

void Server::MenssagemChat(player_base* estecliente, char* Menssagem)
{
     for (UINT i=0;i<Players.size();i++) {
         player_base* outrocliente = Players.at(i);
         if ((outrocliente->chars[outrocliente->chara].map == estecliente->chars[estecliente->chara].map) && outrocliente->charsel) {
            Transfer_Data data;
            sprintf(data.char1, "%s :> %s", estecliente->chars[estecliente->chara].nome, Menssagem);
            data.comando = 1;
            send(outrocliente->sock, (char*)&data, sizeof(data), 0);
         }
     }
}
