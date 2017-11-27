/*
 * File:   WorldServer.h
 * Author: Douglas Maitelli
 *
 * Created on December, 4 2010, 19:37
 */

#ifndef WORLDSERVER_H
#define	WORLDSERVER_H

#include <stdio.h>

#include <stdlib.h>
#include <stdarg.h>
#include <vector>
#include <string>

using namespace std;

class Log;
class Utils;
class Server;
class Player;
class Guild;
class Party;
class Item;

struct Transfer_Data {
    int command;
    string text;
};

class WorldServer {
private:
	Server* server;

	vector<Item*> items;
	vector<Guild*> guilds;

public:
    WorldServer(Server*);
    virtual ~WorldServer();

	// General
	bool loadServer();

	// Data
	bool loadItems();
	bool loadMonsters();
	bool loadNPCS();
	bool loadQuests();
	bool loadSkills();
	bool loadGuilds();

    //------------------------------------------------------------------------
	// Global Config Vars
	//------------------------------------------------------------------------
	static unsigned int MAX_PLAYERS;

	static unsigned int LVL_MAX;
	static unsigned int GUILD_LVL_MAX;
	static unsigned int EXP_MAX;
	static unsigned int GOLD_MAX;
	static unsigned int LIFE_MAX;
	static unsigned int STATS_MAX;

	static unsigned int ADM_LVL;
	static unsigned int GM_LVL;

	static unsigned int LVL_PERM;
	static unsigned int EXP_PERM;
	static unsigned int GOLD_PERM;
	static unsigned int ITEM_PERM;
	static unsigned int BAN_PERM;
	static unsigned int UNBAN_PERM;
	static unsigned int KICK_PERM;
	static unsigned int WARN_PERM;
	static unsigned int GO_PERM;
	static unsigned int BUFF_PERM;
	static unsigned int BUY_PERM;
	static unsigned int RESTART_PERM;
	static unsigned int RELOADITEM_PERM;
	static unsigned int RELOADNPC_PERM;
	static unsigned int RELOADMONSTER_PERM;
	static unsigned int RELOADQUEST_PERM;
	static unsigned int RELOADSKILL_PERM;
	static unsigned int RELOADGUILD_PERM;
	static unsigned int TEMPO_PERM;
	static unsigned int REPAIR_PERM;
	static unsigned int SUMMON_PERM;
	static unsigned int CLEAR_PERM;
	static unsigned int CALL_PERM;
	static unsigned int HEAL_PERM;
	static unsigned int HIDE_PERM;
	static unsigned int MAXSTAT_PERM;
	static unsigned int MAXHAB_PERM;
	static unsigned int WHO_PERM;
	static unsigned int GUILDLVL_PERM;
	static unsigned int MSG_PERM;
	static unsigned int SAVE_PERM;
	static unsigned int A_LVL_PERM;
	static unsigned int A_EXP_PERM;
	static unsigned int A_GOLD_PERM;
	static unsigned int A_ITEM_PERM;
	static unsigned int A_GO_PERM;
	static unsigned int A_BUFF_PERM;
	static unsigned int A_REPAIR_PERM;
	static unsigned int A_HEAL_PERM;
	static unsigned int A_MAXSTAT_PERM;
	static unsigned int A_MAXHAB_PERM;
	static unsigned int A_GUILDLVL_PERM;
	static unsigned int A_SAVE_PERM;

	// Message
    void playerMessage(Player*, string);
    void serverSendAllMessage(string, ...);
    void serverSendPlayerMessage(Player*, string, ...);
    void serverSendGuildMessage(Guild*, string, ...);
    void serverSendPartyMessage(Party*, string, ...);
    void serverMessage(Player*, string);
    void chatMessage(Player*, string);
    bool privateMessage(Player*, Player*, string);
    void guildMessage(Player*, string);
    void partyMessage(Player*, string);

    //------------------------------------------------------------------------
	// GM Commands
	//------------------------------------------------------------------------
    bool gmCmd(Player*, string);
    void gmLog(Player*, string, string, ...);

	bool GM_lvl(Player*, int);
	bool GM_exp(Player*, long int);
	bool GM_gold(Player*, long int);
	bool GM_item(Player*, unsigned int, unsigned int itemammount);
	bool GM_ban(Player*, char*);
	bool GM_unban(Player*, char*);
	bool GM_kick(Player*, char*);
	bool GM_warn(Player*, char*, int);
	bool GM_go(Player*, unsigned int, float, float);
	bool GM_buff(Player*);
	bool GM_buy(Player*);
	bool GM_restart(Player*);
	bool GM_reloaditem(Player*);
	bool GM_reloadnpc(Player*);
	bool GM_reloadmonster(Player*);
	bool GM_reloadquest(Player*);
	bool GM_reloadskill(Player*);
	bool GM_reloadguild(Player*);
	bool GM_tempo(Player*, char*);
	bool GM_repair(Player*);
	bool GM_summon(Player*, unsigned int);
	bool GM_clear(Player*);
	bool GM_call(Player*, char*);
	bool GM_heal(Player*);
	bool GM_hide(Player*);
	bool GM_maxstat(Player*);
	bool GM_maxhab(Player*);
	bool GM_who(Player*, char*);
	bool GM_guildlvl(Player*, int);
	bool GM_msg(Player*, string);
	bool GM_save(Player*);
	//------------------------------------------------------------------------
	bool GM_A_lvl(Player*, char*, int);
	bool GM_A_exp(Player*, char*, long int);
	bool GM_A_gold(Player*, char*, long int);
	bool GM_A_item(Player*, char*, unsigned int);
	bool GM_A_go(Player*, char*, unsigned int, float, float);
	bool GM_A_buff(Player*, char*);
	bool GM_A_repair(Player*, char*);
	bool GM_A_heal(Player*, char*);
	bool GM_A_maxstat(Player*, char*);
	bool GM_A_maxhab(Player*, char*);
	bool GM_A_guildlvl(Player*, char*, int);
	bool GM_A_save(Player*, char*);

	// Player
	void savePlayer(Player*);
    void disconnectPlayer(Player*);
};

#endif	/* WORLDSERVER_H */
