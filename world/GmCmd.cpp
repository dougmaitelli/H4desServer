/*
 * File:   GmCmd.cpp
 * Author: DougM
 *
 * Created on 16 de Abril de 2011, 00:26
 */

#include "WorldServer.h"

#include "../common/Log.h"
#include "../common/Utils.h"
#include "../Server.h"
#include "../player/Player.h"
#include "../player/Character.h"
#include "../party/Guild.h"
#include "../party/Party.h"

//TODO: Change strtok usage to strtok_r and review current commands

//------------------------------------------------------------------------
// Global Config Vars
//------------------------------------------------------------------------
unsigned int WorldServer::MAX_PLAYERS = 100;

unsigned int WorldServer::LVL_MAX = 100;
unsigned int WorldServer::GUILD_LVL_MAX = 100;
unsigned int WorldServer::EXP_MAX = 1000;
unsigned int WorldServer::GOLD_MAX = 1000;
unsigned int WorldServer::LIFE_MAX = 1000;
unsigned int WorldServer::STATS_MAX = 1000;

unsigned int WorldServer::ADM_LVL = 100;
unsigned int WorldServer::GM_LVL = 30;

unsigned int WorldServer::LVL_PERM = 0;
unsigned int WorldServer::EXP_PERM = 0;
unsigned int WorldServer::GOLD_PERM = 0;
unsigned int WorldServer::ITEM_PERM = 0;
unsigned int WorldServer::BAN_PERM = 0;
unsigned int WorldServer::UNBAN_PERM = 0;
unsigned int WorldServer::KICK_PERM = 0;
unsigned int WorldServer::WARN_PERM = 0;
unsigned int WorldServer::GO_PERM = 0;
unsigned int WorldServer::BUFF_PERM = 0;
unsigned int WorldServer::BUY_PERM = 0;
unsigned int WorldServer::RESTART_PERM = 0;
unsigned int WorldServer::RELOADITEM_PERM = 0;
unsigned int WorldServer::RELOADNPC_PERM = 0;
unsigned int WorldServer::RELOADMONSTER_PERM = 0;
unsigned int WorldServer::RELOADQUEST_PERM = 0;
unsigned int WorldServer::RELOADSKILL_PERM = 0;
unsigned int WorldServer::RELOADGUILD_PERM = 0;
unsigned int WorldServer::TEMPO_PERM = 0;
unsigned int WorldServer::REPAIR_PERM = 0;
unsigned int WorldServer::SUMMON_PERM = 0;
unsigned int WorldServer::CLEAR_PERM = 0;
unsigned int WorldServer::CALL_PERM = 0;
unsigned int WorldServer::HEAL_PERM = 0;
unsigned int WorldServer::HIDE_PERM = 0;
unsigned int WorldServer::MAXSTAT_PERM = 0;
unsigned int WorldServer::MAXHAB_PERM = 0;
unsigned int WorldServer::WHO_PERM = 0;
unsigned int WorldServer::GUILDLVL_PERM = 0;
unsigned int WorldServer::MSG_PERM = 0;
unsigned int WorldServer::SAVE_PERM = 0;
unsigned int WorldServer::A_LVL_PERM = 0;
unsigned int WorldServer::A_EXP_PERM = 0;
unsigned int WorldServer::A_GOLD_PERM = 0;
unsigned int WorldServer::A_ITEM_PERM = 0;
unsigned int WorldServer::A_GO_PERM = 0;
unsigned int WorldServer::A_BUFF_PERM = 0;
unsigned int WorldServer::A_REPAIR_PERM = 0;
unsigned int WorldServer::A_HEAL_PERM = 0;
unsigned int WorldServer::A_MAXSTAT_PERM = 0;
unsigned int WorldServer::A_MAXHAB_PERM = 0;
unsigned int WorldServer::A_GUILDLVL_PERM = 0;
unsigned int WorldServer::A_SAVE_PERM = 0;

bool WorldServer::gmCmd(Player* player, string command) {
    char* savePtr;
    char* cmdo;
    cmdo = strtok_s(strdup(command.c_str()), " ,.", &savePtr);
    if (cmdo == NULL) {
		this->serverSendPlayerMessage(player, "Invalid command");
        return false;
    } else if (strcmp(cmdo, "/lvl") == 0) {
        if (player->getPermissionLevel() < LVL_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
			this->serverSendPlayerMessage(player, "The correct syntax is /lvl number");
            return false;
        }
        int lvl = atoi(cmdo);
        if (GM_lvl(player, lvl)) {
            gmLog(player, command, "\"/lvl %i\"", lvl);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/exp") == 0) {
        if (player->getPermissionLevel() < EXP_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
			this->serverSendPlayerMessage(player, "The correct syntax is /exp number");
            return false;
        }
        long int exp = atoi(cmdo);
        if (GM_exp(player, exp)) {
            gmLog(player, command, "\"/exp %i\"", exp);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/gold") == 0) {
        if (player->getPermissionLevel() < GOLD_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
			this->serverSendPlayerMessage(player, "The correct syntax is /gold number");
            return false;
        }
        int gold = atoi(cmdo);
        if (GM_gold(player, gold)) {
            gmLog(player, command, "\"/gold %i\"", gold);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/item") == 0) {
        if (player->getPermissionLevel() < ITEM_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
			this->serverSendPlayerMessage(player, "The correct syntax is /item item_id item_ammount");
            return false;
        }
        int itemid = atoi(cmdo);
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
			this->serverSendPlayerMessage(player, "The correct syntax is /item item_id item_ammount");
            return false;
        }
        int itemammount = atoi(cmdo);
        if (GM_item(player, itemid, itemammount)) {
            gmLog(player, command, "\"/item %i %i\"", itemid, itemammount);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/ban") == 0) {
        if (player->getPermissionLevel() < BAN_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
			this->serverSendPlayerMessage(player, "The correct syntax is /ban player_name");
            return false;
        }
        char* banid = cmdo;
        if (GM_ban(player, banid)) {
            gmLog(player, command, "\"/ban %s\"", banid);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/unban") == 0) {
        if (player->getPermissionLevel() < UNBAN_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
			this->serverSendPlayerMessage(player, "The correct syntax is /unban player_name");
            return false;
        }
        char* unbanid = cmdo;
        if (GM_unban(player, unbanid)) {
            gmLog(player, command, "\"/unban %s\"", unbanid);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/kick") == 0) {
        if (player->getPermissionLevel() < KICK_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
			this->serverSendPlayerMessage(player, "The correct syntax is /kick player_name");
            return false;
        }
        char* kickid = cmdo;
        if (GM_kick(player, kickid)) {
            gmLog(player, command, "\"/kick %s\"", kickid);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/warn") == 0) {
        if (player->getPermissionLevel() < WARN_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
			this->serverSendPlayerMessage(player, "The correct syntax is /warn player_name number");
            return false;
        }
        char* warnid = cmdo;
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
			this->serverSendPlayerMessage(player, "The correct syntax is /warn player_name number");
            return false;
        }
        int warnnum = atoi(cmdo);
        if (GM_warn(player, warnid, warnnum)) {
            gmLog(player, command, "\"/warn %s %i\"", warnid, warnnum);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/go") == 0) {
        if (player->getPermissionLevel() < GO_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
			this->serverSendPlayerMessage(player, "The correct syntax is /go map_id");
            return false;
        }
        int goid = atoi(cmdo);
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
			this->serverSendPlayerMessage(player, "The correct syntax is /go map_id x y");
            return false;
        }
        float gox = atoi(cmdo);
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
			this->serverSendPlayerMessage(player, "The correct syntax is /go map_id x y");
            return false;
        }
        float goy = atoi(cmdo);
        if (GM_go(player, goid, gox, goy)) {
            gmLog(player, command, "\"/go %i %i %i\"", goid, gox, goy);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/buff") == 0) {
        if (player->getPermissionLevel() < BUFF_PERM) {
            return false;
        }
        if (GM_buff(player)) {
            gmLog(player, command, "\"/buff\"");
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/buy") == 0) {
        if (player->getPermissionLevel() < BUY_PERM) {
            return false;
        }
        if (GM_buy(player)) {
            gmLog(player, command, "\"/buy\"");
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/restart_server") == 0) {
        if (player->getPermissionLevel() < RESTART_PERM) {
            return false;
        }
        if (GM_restart(player)) {
            gmLog(player, command, "\"/restart_server\"");
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/reload_item") == 0) {
        if (player->getPermissionLevel() < RELOADITEM_PERM) {
            return false;
        }
        if (GM_reloaditem(player)) {
            gmLog(player, command, "\"/reload_item\"");
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/reload_npc") == 0) {
        if (player->getPermissionLevel() < RELOADNPC_PERM) {
            return false;
        }
        if (GM_reloadnpc(player)) {
            gmLog(player, command, "\"/reload_npc\"");
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/reload_monster") == 0) {
        if (player->getPermissionLevel() < RELOADMONSTER_PERM) {
            return false;
        }
        if (GM_reloadmonster(player)) {
            gmLog(player, command, "\"/reload_monster\"");
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/reload_quest") == 0) {
        if (player->getPermissionLevel() < RELOADQUEST_PERM) {
            return false;
        }
        if (GM_reloadquest(player)) {
            gmLog(player, command, "\"/reload_quest\"");
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/reload_skill") == 0) {
        if (player->getPermissionLevel() < RELOADSKILL_PERM) {
            return false;
        }
        if (GM_reloadskill(player)) {
            gmLog(player, command, "\"/reload_skill\"");
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/reload_guild") == 0) {
        if (player->getPermissionLevel() < RELOADGUILD_PERM) {
            return false;
        }
        if (GM_reloadguild(player)) {
            gmLog(player, command, "\"/reload_guild\"");
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/tempo") == 0) {
        if (player->getPermissionLevel() < TEMPO_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
			this->serverSendPlayerMessage(player, "The correct syntax is /tempo name");
            return false;
        }
        char* tempoid = cmdo;
        if (GM_tempo(player, tempoid)) {
            gmLog(player, command, "\"/tempo %s\"", tempoid);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/repair") == 0) {
        if (player->getPermissionLevel() < REPAIR_PERM) {
            return false;
        }
        if (GM_repair(player)) {
            gmLog(player, command, "\"/repair\"");
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/summon") == 0) {
        if (player->getPermissionLevel() < SUMMON_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is /summon monster_id");
            return false;
        }
        int summonid = atoi(cmdo);
        if (GM_summon(player, summonid)) {
            gmLog(player, command, "\"/summon %i\"", summonid);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/clear_map") == 0) {
        if (player->getPermissionLevel() < CLEAR_PERM) {
            return false;
        }
        if (GM_clear(player)) {
            gmLog(player, command, "\"/clear_map\"");
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/call") == 0) {
        if (player->getPermissionLevel() < CALL_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is /call player_name");
            return false;
        }
        char* callid = cmdo;
        if (GM_call(player, callid)) {
            gmLog(player, command, "\"/call %s\"", callid);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/heal") == 0) {
        if (player->getPermissionLevel() < HEAL_PERM) {
            return false;
        }
        if (GM_heal(player)) {
            gmLog(player, command, "\"/heal\"");
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/hide") == 0) {
        if (player->getPermissionLevel() < HIDE_PERM) {
            return false;
        }
        if (GM_hide(player)) {
            gmLog(player, command, "\"/hide\"");
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/max_stats") == 0) {
        if (player->getPermissionLevel() < MAXSTAT_PERM) {
            return false;
        }
        if (GM_maxstat(player)) {
            gmLog(player, command, "\"/max_stats\"");
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/max_hab") == 0) {
        if (player->getPermissionLevel() < MAXHAB_PERM) {
            return false;
        }
        if (GM_maxhab(player)) {
            gmLog(player, command, "\"/max_hab\"");
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/who") == 0) {
        if (player->getPermissionLevel() < WHO_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is /who player_name");
            return false;
        }
        char* whoid = cmdo;
        if (GM_who(player, whoid)) {
            gmLog(player, command, "\"/who %s\"", whoid);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/guild_lvl") == 0) {
        if (player->getPermissionLevel() < GUILDLVL_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is /guild_lvl number");
            return false;
        }
        int lvl = atoi(cmdo);
        if (GM_guildlvl(player, lvl)) {
            gmLog(player, command, "\"/guild_lvl %i\"", lvl);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/msg") == 0) {
        if (player->getPermissionLevel() < MSG_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is /msg text");
            return false;
        }
        string msg = command.substr(5);
        if (GM_msg(player, msg)) {
            gmLog(player, command, "\"/msg %s\"", msg);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "/save") == 0) {
        if (player->getPermissionLevel() < SAVE_PERM) {
            return false;
        }
        if (GM_save(player)) {
            gmLog(player, command, "\"/save\"");
            return true;
        } else {
            return false;
        }
        //------------------------------------------------------------------------------
    } else if (strcmp(cmdo, "#lvl") == 0) {
        if (player->getPermissionLevel() < A_LVL_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is #lvl player_name number");
            return false;
        }
        char* playerName = cmdo;
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is #lvl player_name number");
            return false;
        }
        int lvl = atoi(cmdo);
        if (GM_A_lvl(player, playerName, lvl)) {
            gmLog(player, command, "\"#lvl %s %i\"", playerName, lvl);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "#exp") == 0) {
        if (player->getPermissionLevel() < A_EXP_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is #exp player_name number");
            return false;
        }
        char* playerName = cmdo;
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is #exp player_name number");
            return false;
        }
        long int exp = atoi(cmdo);
        if (GM_A_exp(player, playerName, exp)) {
            gmLog(player, command, "\"#exp %s %i\"", playerName, exp);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "#gold") == 0) {
        if (player->getPermissionLevel() < A_GOLD_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is #gold player_name number");
            return false;
        }
        char* playerName = cmdo;
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is #gold player_name number");
            return false;
        }
        int gold = atoi(cmdo);
        if (GM_A_gold(player, playerName, gold)) {
            gmLog(player, command, "\"#gold %s %i\"", playerName, gold);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "#item") == 0) {
        if (player->getPermissionLevel() < A_ITEM_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is #item player_name item_id");
            return false;
        }
        char* playerName = cmdo;
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is #item player_name item_id");
            return false;
        }
        int itemid = atoi(cmdo);
        if (GM_A_item(player, playerName, itemid)) {
            gmLog(player, command, "\"#item %s %i\"", playerName, itemid);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "#go") == 0) {
        if (player->getPermissionLevel() < A_GO_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is #go player_name map_id x y");
            return false;
        }
        char* playerName = cmdo;
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is #go player_name map_id x y");
            return false;
        }
        int goid = atoi(cmdo);
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is #go player_name map_id x y");
            return false;
        }
        int gox = atoi(cmdo);
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is #go player_name map_id x y");
            return false;
        }
        int goy = atoi(cmdo);
        if (GM_A_go(player, playerName, goid, gox, goy)) {
            gmLog(player, command, "\"#go %s %i %i %i\"", playerName, goid, gox, goy);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "#buff") == 0) {
        if (player->getPermissionLevel() < A_BUFF_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is #buff player_name");
            return false;
        }
        char* playerName = cmdo;
        if (GM_A_buff(player, playerName)) {
            gmLog(player, command, "\"#buff %s\"", playerName);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "#repair") == 0) {
        if (player->getPermissionLevel() < A_REPAIR_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is #repair player_name");
            return false;
        }
        char* playerName = cmdo;
        if (GM_A_repair(player, playerName)) {
            gmLog(player, command, "\"#repair %s\"", playerName);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "#heal") == 0) {
        if (player->getPermissionLevel() < A_HEAL_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is #heal player_name");
            return false;
        }
        char* playerName = cmdo;
        if (GM_A_heal(player, playerName)) {
            gmLog(player, command, "\"#heal %s\"", playerName);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "#max_stats") == 0) {
        if (player->getPermissionLevel() < A_MAXSTAT_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is #max_stats player_name");
            return false;
        }
        char* playerName = cmdo;
        if (GM_A_maxstat(player, playerName)) {
            gmLog(player, command, "\"#max_stats %s\"", playerName);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "#max_hab") == 0) {
        if (player->getPermissionLevel() < A_MAXHAB_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is #max_hab player_name");
            return false;
        }
        char* playerName = cmdo;
        if (GM_A_maxhab(player, playerName)) {
            gmLog(player, command, "\"#max_hab %s\"", playerName);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "#guild_lvl") == 0) {
        if (player->getPermissionLevel() < A_GUILDLVL_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is #guild_lvl player_name number");
            return false;
        }
        char* playerName = cmdo;
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is #guild_lvl player_name number");
            return false;
        }
        int lvl = atoi(cmdo);
        if (GM_A_guildlvl(player, playerName, lvl)) {
            gmLog(player, command, "\"#guild_lvl %s %i\"", playerName, lvl);
            return true;
        } else {
            return false;
        }
    } else if (strcmp(cmdo, "#save") == 0) {
        if (player->getPermissionLevel() < A_SAVE_PERM) {
            return false;
        }
        if ((cmdo = strtok_s(NULL, " ,.", &savePtr)) == NULL) {
        	this->serverSendPlayerMessage(player, "The correct syntax is #save player_name");
            return false;
        }
        char* playerName = cmdo;
        if (GM_A_save(player, playerName)) {
            gmLog(player, command, "\"#save %s\"", playerName);
            return true;
        } else {
            return false;
        }
        //------------------------------------------------------------------------------
    } else {
    	this->serverSendPlayerMessage(player, "Invalid command");
        gmLog(player, command, "comando invalido");
        return false;
    }
}

void WorldServer::gmLog(Player* player, string command, string message, ...) {
	va_list ap;
	va_start(ap, message);
	char formatedMessage[80];
	vsprintf(formatedMessage, message.c_str(), ap);
	va_end(ap);

	if (player->getPermissionLevel() >= ADM_LVL) {
		Log::write(ADM_ACTION, false, "%s: \"%s\": %s", player->getUsername(), command, formatedMessage);
	} else {
		Log::write(GM_ACTION, false, "%s: \"%s\": %s", player->getUsername(), command, formatedMessage);
	}
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

bool WorldServer::GM_lvl(Player* estecliente, int lvl) {
	Character* character = estecliente->getCurrentCharacter();

    if (lvl > 0) {
        if (lvl > (signed)(LVL_MAX - character->GetLevel())) {
            lvl = LVL_MAX - character->GetLevel();
        }
        this->serverSendPlayerMessage(estecliente, "You reached %i levels up!", lvl);
    } else {
        if ((character->GetLevel() + lvl) <= 0) {
            lvl = -(character->GetLevel() - 1);
        }
        this->serverSendPlayerMessage(estecliente, "You lost %i levels!", -lvl);
    }
    character->SetLevel(character->GetLevel() + lvl);
    this->savePlayer(estecliente);
    return true;
}

bool WorldServer::GM_exp(Player* estecliente, long int exp) {
	Character* character = estecliente->getCurrentCharacter();

    if (exp > 0) {
        if (exp > (signed)(EXP_MAX - character->GetExperience())) {
            exp = (EXP_MAX - character->GetExperience());
        }
        this->serverSendPlayerMessage(estecliente, "You acquired %i experience points!", exp);
    } else {
        if ((character->GetExperience() + exp) <= 0) {
            exp = -(character->GetExperience() - 1);
        }
        this->serverSendPlayerMessage(estecliente, "You lost %i experiencie points!", -exp);
    }
    character->SetExperience(character->GetExperience() + exp);
    this->savePlayer(estecliente);
    return true;
}

bool WorldServer::GM_gold(Player* estecliente, long int gold) {
    Character* character = estecliente->getCurrentCharacter();

    if (gold > 0) {
        if (gold > (signed)(GOLD_MAX - character->GetGold())) {
            gold = (GOLD_MAX - character->GetGold());
        }
        this->serverSendPlayerMessage(estecliente, "You gained %i gold!", gold);
    } else {
        if ((character->GetGold() + gold) <= 0) {
            gold = -(character->GetGold() - 1);
        }
        this->serverSendPlayerMessage(estecliente, "You lost %i gold!", -gold);
    }
    this->savePlayer(estecliente);
    character->SetGold(character->GetGold() + gold);
    return true;
}

bool WorldServer::GM_item(Player* estecliente, unsigned int itemid, unsigned int itemammount) {
    return true;
}

bool WorldServer::GM_ban(Player* estecliente, char* banid) {
    /*Player* outrocliente = GetPlayer(banid);
    if (outrocliente != NULL) {
        if (estecliente->perm > outrocliente->perm) {
            outrocliente->ban = 1;
            this->serverSendPlayerMessage(estecliente, "Player %i:%s banned", outrocliente->id, outrocliente->usuario);
            this->serverSendPlayerMessage(outrocliente, "You has been banned");
            this->savePlayer(outrocliente);
            this->disconnectPlayer(outrocliente);
            return true;
        } else {
            return false;
        }
    } else {
        Player* outrocliente = GetPlayerDB(banid);
        if (outrocliente != NULL) {
            QueryDB("UPDATE users SET ban ='1' WHERE id ='%i'", outrocliente->id);
            return true;
        } else {
        	this->serverSendPlayerMessage(estecliente, "This Player: %s does not exist or is not logged in", banid);
            return false;
        }
    }*/
	return true;
}

bool WorldServer::GM_unban(Player* estecliente, char* unbanid) {
    /*Player* outrocliente = GetPlayerDB(unbanid);
    if (outrocliente != NULL) {
        QueryDB("UPDATE users SET ban ='0' WHERE id ='%i'", outrocliente->id);
        this->serverSendPlayerMessage(estecliente, "Player %i:%s unbanned", outrocliente->id, outrocliente->usuario);
    } else {
    	this->serverSendPlayerMessage(estecliente, "This Player: %s does not exist", unbanid);
    }*/
    return true;
}

bool WorldServer::GM_kick(Player* estecliente, char* kickid) {
    /*Player* outrocliente = GetPlayer(kickid);
    if (outrocliente != NULL) {
        if (estecliente->perm > outrocliente->perm) {
        	this->serverSendPlayerMessage(estecliente, "Player %i:%s kicked", outrocliente->id, outrocliente->usuario);
			this->serverSendPlayerMessage(outrocliente, "You has been kicked");
            this->disconnectPlayer(outrocliente);
            return true;
        } else {
            return false;
        }
    } else {
    	this->serverSendPlayerMessage(estecliente, "This Player: %s does not exist or is not logged in", kickid);
        return false;
    }*/
	return true;
}

bool WorldServer::GM_warn(Player* estecliente, char* warnid, int warnnum) {
    /*Player* outrocliente = GetPlayer(warnid);
    if (outrocliente != NULL) {
        if (estecliente->perm > outrocliente->perm) {
            outrocliente->warn += warnnum;
            this->serverSendPlayerMessage(estecliente, "The player %i:%s received %i warn points", outrocliente->id, outrocliente->usuario, warnnum);
            this->serverSendPlayerMessage(outrocliente, "You have received %i warn points", warnnum);
            this->savePlayer(outrocliente);
            return true;
        } else {
            return false;
        }
    } else {
    	this->serverSendPlayerMessage(estecliente, "This Player: %s does not exist or is not logged in", warnid);
        return false;
    }*/
	return true;
}

bool WorldServer::GM_go(Player* estecliente, unsigned int goid, float gox, float goy) {
    /*estecliente->chars[estecliente->chara].map = goid;
    estecliente->chars[estecliente->chara].x = gox;
    estecliente->chars[estecliente->chara].y = goy;
    this->serverSendPlayerMessage(estecliente, "You have been teleported to map:%i X:%i Y:%i", goid, gox, goy);*/
    return true;
}

bool WorldServer::GM_buff(Player* estecliente) {
    return true;
}

bool WorldServer::GM_buy(Player* estecliente) {
    return true;
}

bool WorldServer::GM_restart(Player* estecliente) {
    server->RESTART_SERVER = 1;
    return true;
}

bool WorldServer::GM_reloaditem(Player* estecliente) {
    return true;
}

bool WorldServer::GM_reloadnpc(Player* estecliente) {
    return true;
}

bool WorldServer::GM_reloadmonster(Player* estecliente) {
    return true;
}

bool WorldServer::GM_reloadquest(Player* estecliente) {
    return true;
}

bool WorldServer::GM_reloadskill(Player* estecliente) {
    return true;
}

bool WorldServer::GM_reloadguild(Player* estecliente) {
    /*pthread_mutex_lock(&MutexLoad);
    Guilds.clear();
    LoadGuilds();
    pthread_mutex_unlock(&MutexLoad);
    this->serverSendPlayerMessage(estecliente, "The guilds list has been reloaded");*/
    return true;
}

bool WorldServer::GM_tempo(Player* estecliente, char* tempoid) {
    if (strcmp(tempoid, "day") == 0) {

    } else if (strcmp(tempoid, "night") == 0) {

    } else if (strcmp(tempoid, "rain") == 0) {

    } else if (strcmp(tempoid, "dry") == 0) {

    } else {
        return false;
    }
    return true;
}

bool WorldServer::GM_repair(Player* estecliente) {
    return true;
}

bool WorldServer::GM_summon(Player* estecliente, unsigned int summonid) {
    return true;
}

bool WorldServer::GM_clear(Player* estecliente) {
    return true;
}

bool WorldServer::GM_call(Player* estecliente, char* callid) {
    /*Player* outrocliente = GetPlayer(callid);
    if (outrocliente != NULL) {
        if (estecliente->perm > outrocliente->perm) {
            outrocliente->chars[outrocliente->chara].map = estecliente->chars[estecliente->chara].map;
            outrocliente->chars[outrocliente->chara].x = estecliente->chars[estecliente->chara].x;
            outrocliente->chars[outrocliente->chara].y = estecliente->chars[estecliente->chara].y;
            this->serverSendPlayerMessage(estecliente, "The player %i:%s has been teleported to you", outrocliente->id, outrocliente->usuario);
            this->serverSendPlayerMessage(outrocliente, "You has been teleported to %s", estecliente->chars[estecliente->chara].nome);
            return true;
        } else {
            return false;
        }
    } else {
    	this->serverSendPlayerMessage(estecliente, "This Player: %s does not exist or is not logged in", callid);
        return false;
    }*/
	return true;
}

bool WorldServer::GM_heal(Player* estecliente) {
    /*estecliente->chars[estecliente->chara].hp = estecliente->chars[estecliente->chara].hp_max;
    estecliente->chars[estecliente->chara].mp = estecliente->chars[estecliente->chara].mp_max;
    this->serverSendPlayerMessage(estecliente, "Your hp and your mp have been restaured");*/
    return true;
}

bool WorldServer::GM_hide(Player* estecliente) {
    if (estecliente->getHide() == 0) {
        estecliente->setHide(1);
        this->serverSendPlayerMessage(estecliente, "You are now non visible to other players");
    } else {
        estecliente->setHide(0);
        this->serverSendPlayerMessage(estecliente, "You are now visible to other players");
    }
    return true;
}

bool WorldServer::GM_maxstat(Player* estecliente) {
    /*estecliente->chars[estecliente->chara].hp_max = LIFE_MAX;
    estecliente->chars[estecliente->chara].mp_max = LIFE_MAX;
    estecliente->chars[estecliente->chara].sau = STATS_MAX;
    estecliente->chars[estecliente->chara].str = STATS_MAX;
    estecliente->chars[estecliente->chara].per = STATS_MAX;
    estecliente->chars[estecliente->chara].dex = STATS_MAX;
    estecliente->chars[estecliente->chara].agi = STATS_MAX;
    estecliente->chars[estecliente->chara].magia = STATS_MAX;
    this->serverSendPlayerMessage(estecliente, "All of your stats have been set to the maximum");*/
    return true;
}

bool WorldServer::GM_maxhab(Player* estecliente) {
    return true;
}

bool WorldServer::GM_who(Player* estecliente, char* whoid) {
    /*Player* outrocliente = GetPlayer(whoid);
    if (outrocliente != NULL) {
    	this->serverSendPlayerMessage(estecliente, "User: %i:%s\nChar: %i:%s\nProfission: %i\nSex: %i\nLevel: %i\nPermission: %i\nWarn: %i", outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome, outrocliente->chars[outrocliente->chara].profissao, outrocliente->chars[outrocliente->chara].sexo, outrocliente->chars[outrocliente->chara].lvl, outrocliente->perm, outrocliente->warn);
    } else {
    	this->serverSendPlayerMessage(estecliente, "This Player: %s does not exist or is not logged in", whoid);
    }*/
    return true;
}

bool WorldServer::GM_guildlvl(Player* estecliente, int lvl) {
    /*Guild* guild = GetGuildId(estecliente->chars[estecliente->chara].guild);
    if (guild != NULL) {
        if (lvl > 0) {
            if (lvl > (signed)(GUILD_LVL_MAX - guild->lvl)) {
                lvl = (GUILD_LVL_MAX - guild->lvl);
            }
            this->serverSendGuildMessage(guild, "Your guild received %i levels", lvl);
        } else {
            if ((guild->lvl + lvl) <= 0) {
                lvl = -(guild->lvl - 1);
            }
            this->serverSendGuildMessage(guild, "Your guild lost %i levels", lvl);
        }
        guild->lvl += lvl;
    } else {
    	this->serverSendPlayerMessage(estecliente, "You do not have a guild!");
    }*/
    return true;
}

bool WorldServer::GM_msg(Player* estecliente, string msg) {
    this->serverMessage(estecliente, msg);
    this->serverSendPlayerMessage(estecliente, "Your message has been sent to all players in the server");
    return true;
}

bool WorldServer::GM_save(Player* estecliente) {
    /*estecliente->chars[estecliente->chara].save_map = estecliente->chars[estecliente->chara].map;
    estecliente->chars[estecliente->chara].save_x = estecliente->chars[estecliente->chara].x;
    estecliente->chars[estecliente->chara].save_y = estecliente->chars[estecliente->chara].y;
    this->serverSendPlayerMessage(estecliente, "Your actual position has been saved as your default respawn point");*/
    return true;
}
//------------------------------------------------------------------------------

bool WorldServer::GM_A_lvl(Player* estecliente, char* player, int lvl) {
    /*Player* outrocliente = GetPlayer(player);
    if (outrocliente != NULL) {
        if (estecliente->perm > outrocliente->perm) {
            outrocliente->chars[outrocliente->chara].lvl += lvl;
            this->serverSendPlayerMessage(estecliente, "You have been gived %i levels to the player %i:%s Char:%i:%s", lvl, outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome);
            this->serverSendPlayerMessage(outrocliente, "You have received %i levels from the player: %s", lvl, estecliente->chars[estecliente->chara].nome);
            return true;
        }
        return false;
    } else {
    	this->serverSendPlayerMessage(estecliente, "This Player: %s does not exist or is not logged in", player);
        return false;
    }*/
	return true;
}

bool WorldServer::GM_A_exp(Player* estecliente, char* player, long int exp) {
    /*Player* outrocliente = GetPlayer(player);
    if (outrocliente != NULL) {
        if (estecliente->perm > outrocliente->perm) {
            outrocliente->chars[outrocliente->chara].exp += exp;
            this->serverSendPlayerMessage(estecliente, "You have been gived %i experiencie points to the player %i:%s Char:%i:%s", exp, outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome);
            this->serverSendPlayerMessage(outrocliente, "You have received %i experiencia points from the player: %s", exp, estecliente->chars[estecliente->chara].nome);
            return true;
        }
        return false;
    } else {
    	this->serverSendPlayerMessage(estecliente, "This Player: %s does not exist or is not logged in", player);
        return false;
    }*/
	return true;
}

bool WorldServer::GM_A_gold(Player* estecliente, char* player, long int gold) {
    /*Player* outrocliente = GetPlayer(player);
    if (outrocliente != NULL) {
        if (estecliente->perm > outrocliente->perm) {
            outrocliente->chars[outrocliente->chara].gold += gold;
            this->serverSendPlayerMessage(estecliente, "You have been gived %i golds to the player %i:%s Char:%i:%s", gold, outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome);
            this->serverSendPlayerMessage(outrocliente, "You have received %i golds from the player: %s", gold, estecliente->chars[estecliente->chara].nome);
            return true;
        }
        return false;
    } else {
    	this->serverSendPlayerMessage(estecliente, "This Player: %s does not exist or is not logged in", player);
        return false;
    }*/
	return true;
}

bool WorldServer::GM_A_item(Player* estecliente, char* player, unsigned int itemid) {
    /*Player* outrocliente = GetPlayer(player);
    if (outrocliente != NULL) {
        if (estecliente->perm > outrocliente->perm) {
            return true;
        }
        return false;
    } else {
    	this->serverSendPlayerMessage(estecliente, "This Player: %s does not exist or is not logged in", player);
        return false;
    }*/
	return true;
}

bool WorldServer::GM_A_go(Player* estecliente, char* player, unsigned int goid, float gox, float goy) {
    /*Player* outrocliente = GetPlayer(player);
    if (outrocliente != NULL) {
        if (estecliente->perm > outrocliente->perm) {
            outrocliente->chars[outrocliente->chara].map = goid;
            outrocliente->chars[outrocliente->chara].x = gox;
            outrocliente->chars[outrocliente->chara].y = goy;
            this->serverSendPlayerMessage(estecliente, "You have been teleported the player %i:%s Char:%i:%s to map:%i X:%i Y:%i", outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome, goid, gox, goy);
            this->serverSendPlayerMessage(outrocliente, "You has been teleported to the player: %s", estecliente->chars[estecliente->chara].nome);
            return true;
        }
        return false;
    } else {
    	this->serverSendPlayerMessage(estecliente, "This Player: %s does not exist or is not logged in", player);
        return false;
    }*/
	return true;
}

bool WorldServer::GM_A_buff(Player* estecliente, char* player) {
    /*Player* outrocliente = GetPlayer(player);
    if (outrocliente != NULL) {
        if (estecliente->perm > outrocliente->perm) {
            return true;
        }
        return false;
    } else {
    	this->serverSendPlayerMessage(estecliente, "This Player: %s does not exist or is not logged in", player);
        return false;
    }*/
	return true;
}

bool WorldServer::GM_A_repair(Player* estecliente, char* player) {
    /*Player* outrocliente = GetPlayer(player);
    if (outrocliente != NULL) {
        if (estecliente->perm > outrocliente->perm) {
            return true;
        }
        return false;
    } else {
    	this->serverSendPlayerMessage(estecliente, "This Player: %s does not exist or is not logged in", player);
        return false;
    }*/
	return true;
}

bool WorldServer::GM_A_heal(Player* estecliente, char* player) {
    /*Player* outrocliente = GetPlayer(player);
    if (outrocliente != NULL) {
        if (estecliente->perm > outrocliente->perm) {
            outrocliente->chars[outrocliente->chara].hp = outrocliente->chars[outrocliente->chara].hp_max;
            outrocliente->chars[outrocliente->chara].mp = outrocliente->chars[outrocliente->chara].mp_max;
            this->serverSendPlayerMessage(estecliente, "You have been restaured the hp and the mp of the player %i:%s Char:%i:%s", outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome);
            this->serverSendPlayerMessage(outrocliente, "Your HP and your MP has been restaured by the player: %s", estecliente->chars[estecliente->chara].nome);
            return true;
        }
        return false;
    } else {
    	this->serverSendPlayerMessage(estecliente, "This Player: %s does not exist or is not logged in", player);
        return false;
    }*/
	return true;
}

bool WorldServer::GM_A_maxstat(Player* estecliente, char* player) {
    /*Player* outrocliente = GetPlayer(player);
    if (outrocliente != NULL) {
        if (estecliente->perm > outrocliente->perm) {
            outrocliente->chars[outrocliente->chara].hp_max = LIFE_MAX;
            outrocliente->chars[outrocliente->chara].mp_max = LIFE_MAX;
            outrocliente->chars[outrocliente->chara].sau = STATS_MAX;
            outrocliente->chars[outrocliente->chara].str = STATS_MAX;
            outrocliente->chars[outrocliente->chara].per = STATS_MAX;
            outrocliente->chars[outrocliente->chara].dex = STATS_MAX;
            outrocliente->chars[outrocliente->chara].agi = STATS_MAX;
            outrocliente->chars[outrocliente->chara].magia = STATS_MAX;
            this->serverSendPlayerMessage(estecliente, "You have been set all stats of the player %i:%s Char:%i:%s to the maximum", outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome);
            this->serverSendPlayerMessage(outrocliente, "All your stats has been set to the maximum by the player: %s", estecliente->chars[estecliente->chara].nome);
            return true;
        }
        return false;
    } else {
    	this->serverSendPlayerMessage(estecliente, "This Player: %s does not exist or is not logged in", player);
        return false;
    }*/
	return true;
}

bool WorldServer::GM_A_maxhab(Player* estecliente, char* player) {
    /*Player* outrocliente = GetPlayer(player);
    if (outrocliente != NULL) {
        if (estecliente->perm > outrocliente->perm) {
            return true;
        }
        return false;
    } else {
    	this->serverSendPlayerMessage(estecliente, "This Player: %s does not exist or is not logged in", player);
        return false;
    }*/
	return true;
}

bool WorldServer::GM_A_guildlvl(Player* estecliente, char* player, int lvl) {
    /*Player* outrocliente = GetPlayer(player);
    if (outrocliente != NULL) {
        if (estecliente->perm > outrocliente->perm) {
            Guild* guild = GetGuildId(outrocliente->chars[outrocliente->chara].guild);
            if (guild != NULL) {
                guild->lvl += lvl;
                this->serverSendPlayerMessage(estecliente, "You have been gived %i levels for the guild %i:%s of the player %i:%s Char:%i:%s", lvl, guild->id, guild->nome, outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome);
                this->serverSendGuildMessage(guild, "Your guild %s received %i levels from the player: %s", guild->getName(), lvl, estecliente->chars[estecliente->chara].nome);
            } else {
            	this->serverSendPlayerMessage(estecliente, "This Player: %i:%s Char:%i:%s does not have a guild", outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome);
            }
            return true;
        }
        return false;
    } else {
    	this->serverSendPlayerMessage(estecliente, "This Player: %s does not exist or is not logged in", player);
        return false;
    }*/
	return true;
}

bool WorldServer::GM_A_save(Player* estecliente, char* player) {
    /*Player* outrocliente = GetPlayer(player);
    if (outrocliente != NULL) {
        if (estecliente->perm > outrocliente->perm) {
            outrocliente->chars[outrocliente->chara].save_map = outrocliente->chars[outrocliente->chara].map;
            outrocliente->chars[outrocliente->chara].save_x = outrocliente->chars[outrocliente->chara].x;
            outrocliente->chars[outrocliente->chara].save_y = outrocliente->chars[outrocliente->chara].y;
            this->serverSendPlayerMessage(estecliente, "You have been saved the default respawn point of the player %i:%s Char:%i:%s to map:%i X:%i Y:%i", outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome, outrocliente->chars[outrocliente->chara].map, outrocliente->chars[outrocliente->chara].x, outrocliente->chars[outrocliente->chara].y);
            this->serverSendPlayerMessage(outrocliente, "Your default respawn point has been altered to your actual position by the player: %s", estecliente->chars[estecliente->chara].nome);
            return true;
        }
        return false;
    } else {
    	this->serverSendPlayerMessage(estecliente, "This Player: %s does not exist or is not logged in", player);
        return false;
    }*/
	return true;
}
