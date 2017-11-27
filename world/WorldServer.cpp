/*
 * File:   WorldServer.cpp
 * Author: Douglas Maitelli
 *
 * Created on 4 de Dezembro de 2010, 19:37
 */

#include "WorldServer.h"

#include "../common/Log.h"
#include "../common/Utils.h"
#include "../Server.h"
#include "../player/Player.h"
#include "../player/Character.h"
#include "../party/Guild.h"
#include "../party/Party.h"

WorldServer::WorldServer(Server* server) {
	this->server = server;
}

WorldServer::~WorldServer() {
}

bool WorldServer::loadServer() {
	Log::writePercentage(60, "Carregando dados dos items...");
	if (!this->loadItems()) {
		Log::write(SERVER_ERROR, "Ocorreu um erro ao carregar dados dos items...");
		return false;
	}

	Log::writePercentage(65, "Carregando dados dos monstros...");
	if (!this->loadMonsters()) {
		Log::write(SERVER_ERROR, "Ocorreu um erro ao carregar dados dos monstros...");
		return false;
	}

	Log::writePercentage(70, "Carregando dados dos NPCs...");
	if (!this->loadNPCS()) {
		Log::write(SERVER_ERROR, "Ocorreu um erro ao carregar dados dos NPCs...");
		return false;
	}

	Log::writePercentage(80, "Carregando dados das quests...");
	if (!this->loadQuests()) {
		Log::write(SERVER_ERROR, "Ocorreu um erro ao carregar dados das quests...");
		return false;
	}

	Log::writePercentage(90, "Carregando dados das skills...");
	if (!this->loadSkills()) {
		Log::write(SERVER_ERROR, "Ocorreu um erro ao carregar dados das skills...");
		return false;
	}

	Log::writePercentage(95, "Carregando dados das guilds...");
	if (!this->loadGuilds()) {
		Log::write(SERVER_ERROR, "Ocorreu um erro ao carregar dados das guilds...");
		return false;
	}

	Log::writePercentage(100, "Concluido.");

	return true;
}

bool WorldServer::loadItems() {
	FILE* file;
	char* dados;
	char linha[255];
	file = fopen(ITEMS_PATH, "r");
	if (file == NULL) {
		Log::write(SERVER_ERROR, "Error opening file %s...", ITEMS_PATH);
		return false;
	}
	fgets(linha, sizeof(linha), file);
	do {
		Item* item = new Item();
		fgets(linha, sizeof(linha), file);
		if (feof(file)) {
			break;
		}
		/*dados = strtok(linha, ";");
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
		item->venda = atoi(dados);*/

		items.push_back(item);
	} while (true);

	fclose(file);
	Log::write(SYSTEM, "%i items loaded.", items.size());
	return true;
}

bool WorldServer::loadMonsters() {
	return true;
}

bool WorldServer::loadNPCS() {
	return true;
}

bool WorldServer::loadQuests() {
	return true;
}

bool WorldServer::loadSkills() {
	return true;
}

bool WorldServer::loadGuilds() {
	return true;
}

void WorldServer::playerMessage(Player* player, string msg) {
    //if (player->getPermissionLevel() >= GM_LVL) {
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
    //}

    switch (msg[0]) {
        case '@':
            msg.erase(0);
            //this->privateMessage(player, msg);
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

void WorldServer::savePlayer(Player* player) {
	//TODO: Save Player on DB
}

void WorldServer::disconnectPlayer(Player* player) {
    server->disconnectPlayer(player);
}
