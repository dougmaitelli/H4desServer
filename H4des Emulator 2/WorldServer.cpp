/* 
 * File:   WorldServer.cpp
 * Author: Douglas Maitelli
 * 
 * Created on 4 de Dezembro de 2010, 19:37
 */

#include "WorldServer.h"

WorldServer::WorldServer() {
}

WorldServer::~WorldServer() {
}

void WorldServer::playerMessage(Player* player, string msg) {
    if (player->perm >= GM_LVL) {
        switch (msg[0]) {
            case '/':
                if (msg[1] != '/') {
                    msg.erase(0);
                    break;
                }

                this->gmCmd(player, msg);
                return;
            case '#':
                this->gmCmd(player, msg);
                return;
        }
    }

    switch (msg[0]) {
        case '@':
            msg.erase(0);
            this->privateMessage(player, msg);
            return;
        case '$':
            msg.erase(0);
            this->guildMessage(player, msg);
            return;
        case '&':
            msg.erase(0);
            this->partyMessage(player, msg);
            return;
        default:
            this->chatMessage(player, msg);
            return;
    }
}
