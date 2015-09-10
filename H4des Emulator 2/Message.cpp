/*
 * File:   Message.cpp
 * Author: DougM
 *
 * Created on 16 de Abril de 2011, 00:26
 */

#include "WorldServer.h"

void WorldServer::serverSendAllMessage(string message, ...) {
    va_list ap;
    va_start(ap, message);

    for (UINT i = 0; i < players.size(); i++) {
        Player* toPlayer = players.at(i);

        if (estecliente->logado) {
            Transfer_Data data;
			vsprintf(data.char1, message.c_str(), ap);
            data.comando = 2;
            send(toPlayer->getSocket(), (char*) &data, sizeof (data), 0);
        }
    }

    va_end(ap);
}

void WorldServer::serverSendPlayerMessage(Player* player, string message, ...) {
    va_list ap;
    va_start(ap, message);

    Transfer_Data data;
    vsprintf(data.char1, message.c_str(), ap);
    data.comando = 2;
    send(player->getSocket(), (char*) &data, sizeof (data), 0);

    va_end(ap);
}

void WorldServer::serverSendGuildMessage(Guild* guild, string message, ...) {
    va_list ap;
    va_start(ap, message);

    vector<Player*> guildMembers = guild->getPlayers();

    for (UINT i = 0; i < guildMembers.size(); i++) {
		Player* guildPlayer = guildMembers.at(i);

		Transfer_Data data;
		vsprintf(data.char1, message.c_str(), ap);
		data.comando = 2;
		send(guildPlayer->getSocket(), (char*) &data, sizeof (data), 0);
    }

    va_end(ap);
}

void WorldServer::serverSendPartyMessage(Party* party, string message, ...) {
	va_list ap;
	va_start(ap, message);

	vector<Player*> partyMembers = party->getPlayers();

	for (UINT i = 0; i < partyMembers.size(); i++) {
		Player* partyPlayer = partyMembers.at(i);

		Transfer_Data data;
		vsprintf(data.char1, message.c_str(), ap);
		data.comando = 2;
		send(partyPlayer->getSocket(), (char*) &data, sizeof (data), 0);
	}

	va_end(ap);
}

void WorldServer::serverMessage(Player* player, string message) {
	Character* character = player->getCurrentCharacter();

    for (UINT i = 0; i < players.size(); i++) {
		Player* toPlayer = players.at(i);

		if (estecliente->logado) {
			Transfer_Data data;
			sprintf(data.char1, "%s :> %s", character->GetName(), message);
			data.comando = 2;
			send(toPlayer->getSocket(), (char*) &data, sizeof (data), 0);
		}
	}
}

void WorldServer::chatMessage(Player* player, string message) {
	Character* character = player->getCurrentCharacter();

	for (UINT i = 0; i < players.size(); i++) {
		Player* toPlayer = players.at(i);

		Transfer_Data data;
		sprintf(data.char1, "%s :> %s", character->GetName(), message);
		data.comando = 1;
		send(toPlayer->getSocket(), (char*) &data, sizeof (data), 0);
	}
}

bool WorldServer::privateMessage(Player* player, Player* toPlayer, string message) {
	Character* character = player->getCurrentCharacter();

    if (toPlayer != NULL) {
        Transfer_Data data;
        sprintf(data.char1, "%s :> %s", character->GetName(), message);
        data.comando = 3;
        send(toPlayer->getSocket(), (char*) &data, sizeof (data), 0);
        return true;
    } else {
        return false;
    }
}

void WorldServer::guildMessage(Player* player, string message) {
	Character* character = player->getCurrentCharacter();
	Guild* guild = character->GetGuild();

	vector<Player*> guildMembers = guild->getPlayers();

	for (UINT i = 0; i < guildMembers.size(); i++) {
		Player* guildPlayer = guildMembers.at(i);

		Transfer_Data data;
		sprintf(data.char1, "%s :> %s", character->GetName(), message);
		data.comando = 4;
		send(guildPlayer->getSocket(), (char*) &data, sizeof (data), 0);
	}
}

void WorldServer::partyMessage(Player* player, string message) {
	Character* character = player->getCurrentCharacter();
	Party* party = character->GetParty();

	vector<Player*> partyMembers = party->getPlayers();

    for (UINT i = 0; i < partyMembers.size(); i++) {
    	Player* partyPlayer = partyMembers.at(i);

		Transfer_Data data;
		sprintf(data.char1, "%s :> %s", character->GetName(), message);
		data.comando = 5;
		send(partyPlayer->getSocket(), (char*) &data, sizeof (data), 0);
    }
}


