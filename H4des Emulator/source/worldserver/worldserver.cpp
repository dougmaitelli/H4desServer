#include <conio.h>
#include <windows.h>
#include <cstdio>
#include <iostream>

#include "../comum/log.h"
#include "worldserver.h"

using namespace std;

void Server::PlayerCaminha(player_base* estecliente)
{

}

void Server::PlayerMenssagem(player_base* estecliente, char* msg)
{
    if (TrimStr(msg)) {
        if (estecliente->perm >= GM_LVL) {
            if ((strcspn(msg, "/") == 0) && (strcspn((&msg[0] + 1), "/") != 0)) {
                GmCmd(estecliente, msg);
            } else if (strcspn(msg, "#") == 0) {
                GmCmd(estecliente, msg);
            } else if (strcspn(msg, "@") == 0) {
                CortaStr(msg, 1);
                MenssagemPrivada(estecliente, msg);
            } else if (strcspn(msg, "$") == 0) {
                CortaStr(msg, 1);
                MenssagemGuild(estecliente, msg);
            } else if (strcspn(msg, "&") == 0) {
                CortaStr(msg, 1);
                MenssagemParty(estecliente, msg);
            } else {
                if (strcspn(msg, "/") == 0) {
                    CortaStr(msg, 1);
                }
                MenssagemChat(estecliente, msg);
            }
        } else {
            if (strcspn(msg, "@") == 0) {
                CortaStr(msg, 1);
                MenssagemPrivada(estecliente, msg);
            } else if (strcspn(msg, "$") == 0) {
                CortaStr(msg, 1);
                MenssagemGuild(estecliente, msg);
            } else if (strcspn(msg, "&") == 0) {
                CortaStr(msg, 1);
                MenssagemParty(estecliente, msg);
            } else {
                MenssagemChat(estecliente, msg);
            }
        }
    }
}

void Server::PlayerNpc(player_base* estecliente)
{

}

void Server::PlayerMonstro(player_base* estecliente)
{

}

void Server::PlayerBuy(player_base* estecliente)
{

}

void Server::PlayerFriendAdd(player_base* estecliente)
{

}

void Server::PlayerFriendDelete(player_base* estecliente)
{

}
