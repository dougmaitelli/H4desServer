/*
 * File:   WorldServer.h
 * Author: Douglas Maitelli
 *
 * Created on December, 4 2010, 19:37
 */

#ifndef WORLDSERVER_H
#define	WORLDSERVER_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <pthread.h>

#include "../commom/Utils.h"
#include "../Server.h"
#include "../player/Player.h"

class Utils;
class Server;
class Player;

struct Transfer_Data {
    int command;
    string text;
};

class WorldServer {
private:
	Server* server;

    vector<Player*> players;

public:
    WorldServer(Server*);
    virtual ~WorldServer();

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

	bool GM_lvl(Player* estecliente, int lvl);
	bool GM_exp(Player* estecliente, long int exp);
	bool GM_gold(Player* estecliente, long int gold);
	bool GM_item(Player* estecliente, unsigned int itemid, unsigned int itemammount);
	bool GM_ban(Player* estecliente, char* banid);
	bool GM_unban(Player* estecliente, char* unbanid);
	bool GM_kick(Player* estecliente, char* kickid);
	bool GM_warn(Player* estecliente, char* warnid, int warnnum);
	bool GM_go(Player* estecliente, unsigned int goid, float gox, float goy);
	bool GM_buff(Player* estecliente);
	bool GM_buy(Player* estecliente);
	bool GM_restart(Player* estecliente);
	bool GM_reloaditem(Player* estecliente);
	bool GM_reloadnpc(Player* estecliente);
	bool GM_reloadmonster(Player* estecliente);
	bool GM_reloadquest(Player* estecliente);
	bool GM_reloadskill(Player* estecliente);
	bool GM_reloadguild(Player* estecliente);
	bool GM_tempo(Player* estecliente, char* tempoid);
	bool GM_repair(Player* estecliente);
	bool GM_summon(Player* estecliente, unsigned int summonid);
	bool GM_clear(Player* estecliente);
	bool GM_call(Player* estecliente, char* callid);
	bool GM_heal(Player* estecliente);
	bool GM_hide(Player* estecliente);
	bool GM_maxstat(Player* estecliente);
	bool GM_maxhab(Player* estecliente);
	bool GM_who(Player* estecliente, char* whoid);
	bool GM_guildlvl(Player* estecliente, int lvl);
	bool GM_msg(Player* estecliente, char* msg);
	bool GM_save(Player* estecliente);
	//------------------------------------------------------------------------
	bool GM_A_lvl(Player* estecliente, char* player, int lvl);
	bool GM_A_exp(Player* estecliente, char* player, long int exp);
	bool GM_A_gold(Player* estecliente, char* player, long int gold);
	bool GM_A_item(Player* estecliente, char* player, unsigned int itemid);
	bool GM_A_go(Player* estecliente, char* player, unsigned int goid, float gox, float goy);
	bool GM_A_buff(Player* estecliente, char* player);
	bool GM_A_repair(Player* estecliente, char* player);
	bool GM_A_heal(Player* estecliente, char* player);
	bool GM_A_maxstat(Player* estecliente, char* player);
	bool GM_A_maxhab(Player* estecliente, char* player);
	bool GM_A_guildlvl(Player* estecliente, char* player, int lvl);
	bool GM_A_save(Player* estecliente, char* player);

	// Player
	void savePlayer(Player*);
    void disconnectPlayer(Player*);
};

#endif	/* WORLDSERVER_H */
