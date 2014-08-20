/* 
 * File:   WorldServer.h
 * Author: DougM
 *
 * Created on 4 de Dezembro de 2010, 19:37
 */

#ifndef WORLDSERVER_H
#define	WORLDSERVER_H

#include <pthread.h>
#include <mysql.h>

#include "Utilitarios.h"

#define SERVER_NAME "H4des"

#define MAX_PLAYER_CHARS 5

#define ITEMS_PATH "data/items/items.csv"
#define MONSTER_PATH "data/monsters/monsters.csv"
#define NPCS_PATH "data/npcs/npcs.csv"
#define QUESTS_PATH "data/quests/quests.csv"
#define SKILLS_PATH "data/skills/skills.csv"

struct Transfer_Data {
    int command;
    string text;
};

enum Sex {
    MALE,
    FEMALE
};

enum Lang {
    PT_BR,
    EN_US
};

enum ItemType {
};

class WorldServer {
public:
    WorldServer();
    virtual ~WorldServer();
    void playerMessage(player_base*, string);
    void gmCmd(player_base*, string);
    void sendMessage(player_base* estecliente, string, ...);
    void sendAll(string, ...);
    void sendMessageGuild(Guild, string, ...);
    void sendMessageParty(Party, string, ...);
    void serverMessage(player_base*, string);
    bool privateMessage(player_base*, string);
    void guildMessage(player_base*, string);
    void partyMessage(player_base*, string);
    void chatMessage(player_base*, string);

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

private:

};

#endif	/* WORLDSERVER_H */
