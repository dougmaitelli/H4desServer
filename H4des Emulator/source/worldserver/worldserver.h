#ifndef WORLDSERVER_H
#define WORLDSERVER_H

#include <windows.h>

#include <vector>

#include <pthread/pthread.h>
#include <mysql/mysql.h>

#define SERVER_NAME "H4des"

#define MAX_PLAYER_CHARS 5

#define ITEMS_PATH "data/items/items.csv"
#define MONSTER_PATH "data/monsters/monsters.csv"
#define NPCS_PATH "data/npcs/npcs.csv"
#define QUESTS_PATH "data/quests/quests.csv"
#define SKILLS_PATH "data/skills/skills.csv"

using namespace std;

//------------------------------------------------------------------------------

struct Transfer_Data {
    int comando;
    char char1[80];
    char char2[80];
    int int1;
    int int2;
};

//------------------------------------------------------------------------------

struct items_base {
       unsigned long id;
       char nome[255];
       unsigned int tipo;
       unsigned int ataque;
       unsigned int defesa;
       unsigned int durabilidade;
       unsigned int hp;
       unsigned int mp;
       unsigned int lvl_req;
       unsigned int str_req;
       unsigned int intl_req;
       unsigned int dex_req;
       unsigned int agi_req;
       unsigned int str;
       unsigned int intl;
       unsigned int sau;
       unsigned int per;
       unsigned int car;
       unsigned int dex;
       unsigned int agi;
       unsigned int magia;
       unsigned int map_dest;
       float x_dest;
       float y_dest;
       unsigned int venda;
};

struct monster {

};

struct npc {

};

struct skill {

};

struct quest {

};

struct guilds_base {
       unsigned long id;
       char nome[26];
       unsigned long lider;
       unsigned int lvl;
};

//------------------------------------------------------------------------------

struct item_base {
       int id;
       unsigned int vida;
};

struct skill_base {
       int id;
       int lvl;
       int pos;
};

struct friend_base {
       int id;
};

struct player_base {
       unsigned long id;
       char usuario[100];
       SOCKET sock;
       sockaddr_in client_sock;
       char* ip;
       char subnet[12];
       pthread_mutex_t mutex;
       char lang[7];
       unsigned int warn;
       unsigned short perm;
       unsigned char chara;
       unsigned char ban;
       unsigned char hide;
       bool logado;
       bool charsel;
       bool ativo;
       struct char_base {
              unsigned long id;
              char nome[255];
              unsigned short povo;
              unsigned short raca;
              unsigned short profissao;
              unsigned char sexo;
              unsigned short arma;
              unsigned short esq;
              unsigned short cabeca;
              unsigned short armadura;
              unsigned short luva;
              unsigned short bota;
              unsigned short calca;
              unsigned short cintura;
              unsigned short capa;
              vector<item_base> items;
              unsigned short lvl;
              unsigned long exp;
              unsigned long gold;
              unsigned int hp;
              unsigned int mp;
              unsigned int hp_max;
              unsigned int mp_max;
              unsigned short str;
              unsigned short intl;
              unsigned short sau;
              unsigned short per;
              unsigned short car;
              unsigned short dex;
              unsigned short agi;
              unsigned short magia;
              unsigned short sta;
              unsigned short sp;
              unsigned short skp;
              vector<skill_base> skills;
              unsigned long party;
              unsigned long guild;
              unsigned short map;
              float x;
              float y;
              unsigned short save_map;
              float save_x;
              float save_y;
              vector<friend_base> friends;
       } chars[MAX_PLAYER_CHARS];
};

//------------------------------------------------------------------------------

PVOID AtualizaPlayers(PVOID estecliente);

class Server
{
    //------------------------------------------------------------------------
    // Global
    //------------------------------------------------------------------------
    public:
    unsigned char EXIT_SERVER_PROCESS;
    unsigned char RESTART_SERVER;

    //------------------------------------------------------------------------
    // Global Config Vars
    //------------------------------------------------------------------------
    private:
    unsigned int MAX_PLAYERS;

    unsigned int LVL_MAX;
    unsigned int GUILD_LVL_MAX;
    unsigned int EXP_MAX;
    unsigned int GOLD_MAX;
    unsigned int LIFE_MAX;
    unsigned int STATS_MAX;

    unsigned int ADM_LVL;
    unsigned int GM_LVL;

    unsigned int LVL_PERM;
    unsigned int EXP_PERM;
    unsigned int GOLD_PERM;
    unsigned int ITEM_PERM;
    unsigned int BAN_PERM;
    unsigned int UNBAN_PERM;
    unsigned int KICK_PERM;
    unsigned int WARN_PERM;
    unsigned int GO_PERM;
    unsigned int BUFF_PERM;
    unsigned int BUY_PERM;
    unsigned int RESTART_PERM;
    unsigned int RELOADITEM_PERM;
    unsigned int RELOADNPC_PERM;
    unsigned int RELOADMONSTER_PERM;
    unsigned int RELOADQUEST_PERM;
    unsigned int RELOADSKILL_PERM;
    unsigned int RELOADGUILD_PERM;
    unsigned int TEMPO_PERM;
    unsigned int REPAIR_PERM;
    unsigned int SUMMON_PERM;
    unsigned int CLEAR_PERM;
    unsigned int CALL_PERM;
    unsigned int HEAL_PERM;
    unsigned int HIDE_PERM;
    unsigned int MAXSTAT_PERM;
    unsigned int MAXHAB_PERM;
    unsigned int WHO_PERM;
    unsigned int GUILDLVL_PERM;
    unsigned int MSG_PERM;
    unsigned int SAVE_PERM;
    unsigned int A_LVL_PERM;
    unsigned int A_EXP_PERM;
    unsigned int A_GOLD_PERM;
    unsigned int A_ITEM_PERM;
    unsigned int A_GO_PERM;
    unsigned int A_BUFF_PERM;
    unsigned int A_REPAIR_PERM;
    unsigned int A_HEAL_PERM;
    unsigned int A_MAXSTAT_PERM;
    unsigned int A_MAXHAB_PERM;
    unsigned int A_GUILDLVL_PERM;
    unsigned int A_SAVE_PERM;

    //------------------------------------------------------------------------
    // Server
    //------------------------------------------------------------------------
    public:
    pthread_attr_t at;
    Server();
    ~Server();
    bool InitServer();
    void DesconectaPlayer(player_base* estecliente);
    void DeletaPlayer(player_base* estecliente);
    private:
    SOCKET s;
    vector<player_base*> Players;
    vector<items_base*> Items;
    vector<guilds_base*> Guilds;
    pthread_t thread[65535];
    pthread_mutex_t MutexDeleta;
    bool ServerLoad();
    bool LoadConfig();
    bool ResetOnlines();
    bool LoadItems();
    bool LoadMonsters();
    bool LoadNPCS();
    bool LoadQuests();
    bool LoadSkills();
    bool LoadGuilds();
    void Cls();
    void ServerLoop();
    void AdicionaPlayer(SOCKET novocliente, sockaddr_in* client_sock);

    //------------------------------------------------------------------------
    // DB
    //------------------------------------------------------------------------
    private:
    MYSQL *mysql;
    pthread_mutex_t MutexSQL;
    bool InitDB();
    bool CloseDB();
    bool PingDB();
    bool WaitDB();
    bool QueryDB(char* Querycmd, ...);
    MYSQL_RES* QueryResult(char* Querycmd, ...);

    //------------------------------------------------------------------------
    // Player
    //------------------------------------------------------------------------

    bool Login(player_base* estecliente, char* usuario, char* senha);
    bool CharSelect(player_base* estecliente, int charid);
    bool CharCreate(player_base* estecliente);
    bool CharDelete(player_base* estecliente);

    //------------------------------------------------------------------------
    // Pacotes
    //------------------------------------------------------------------------
    public:
    void PacoteExec(player_base* estecliente, char* buffer);

    //------------------------------------------------------------------------
    // World
    //------------------------------------------------------------------------
    private:
    void PlayerMenssagem(player_base* estecliente, char* msg);
    void PlayerCaminha(player_base* estecliente);
    void PlayerNpc(player_base* estecliente);
    void PlayerMonstro(player_base* estecliente);
    void PlayerBuy(player_base* estecliente);
    void PlayerFriendAdd(player_base* estecliente);
    void PlayerFriendDelete(player_base* estecliente);

    //------------------------------------------------------------------------
    // Menssagem
    //------------------------------------------------------------------------
    private:
    void SendMessage(player_base* estecliente, char* Menssagem, ...);
    void SendAll(char* Menssagempt_BR, char* Menssagemen_US, ...);
    void SendMessageGuild(unsigned int guildid, char* Menssagempt_BR, char* Menssagemen_US, ...);
    void SendMessageParty(unsigned int partyid, char* Menssagempt_BR, char* Menssagemen_US, ...);
    void MenssagemServer(player_base* estecliente, char* Menssagem);
    bool MenssagemPrivada(player_base* estecliente, char Menssagem[]);
    void MenssagemGuild(player_base* estecliente, char* Menssagem);
    void MenssagemParty(player_base* estecliente, char* Menssagem);
    void MenssagemChat(player_base* estecliente, char* Menssagem);

    //------------------------------------------------------------------------
    // Extras
    //------------------------------------------------------------------------
    private:
    player_base* GetUser(char* nome);
    player_base* GetPlayer(char* nome);
    player_base* GetPlayerDB(char* nome);
    player_base* GetPlayerId(unsigned long id);
    guilds_base* GetGuild(char* nome);
    guilds_base* GetGuildId(unsigned long id);
    //------------------------------------------------------------------------
    void SalvaPlayer(player_base* estecliente);
    //------------------------------------------------------------------------
    bool AddSlashes(char* str);
    void CortaStr(char* str, int pos);
    bool TrimStr(char* str);

    //------------------------------------------------------------------------
    // Comandos de GM
    //------------------------------------------------------------------------
    private:
    pthread_mutex_t MutexLoad;
    bool GmCmd(player_base* estecliente, char Comando[]);

    bool GM_lvl(player_base* estecliente, int lvl);
    bool GM_exp(player_base* estecliente, long int exp);
    bool GM_gold(player_base* estecliente, long int gold);
    bool GM_item(player_base* estecliente, unsigned int itemid, unsigned int itemammount);
    bool GM_ban(player_base* estecliente, char* banid);
    bool GM_unban(player_base* estecliente, char* unbanid);
    bool GM_kick(player_base* estecliente, char* kickid);
    bool GM_warn(player_base* estecliente, char* warnid, int warnnum);
    bool GM_go(player_base* estecliente, unsigned int goid, float gox, float goy);
    bool GM_buff(player_base* estecliente);
    bool GM_buy(player_base* estecliente);
    bool GM_restart(player_base* estecliente);
    bool GM_reloaditem(player_base* estecliente);
    bool GM_reloadnpc(player_base* estecliente);
    bool GM_reloadmonster(player_base* estecliente);
    bool GM_reloadquest(player_base* estecliente);
    bool GM_reloadskill(player_base* estecliente);
    bool GM_reloadguild(player_base* estecliente);
    bool GM_tempo(player_base* estecliente, char* tempoid);
    bool GM_repair(player_base* estecliente);
    bool GM_summon(player_base* estecliente, unsigned int summonid);
    bool GM_clear(player_base* estecliente);
    bool GM_call(player_base* estecliente, char* callid);
    bool GM_heal(player_base* estecliente);
    bool GM_hide(player_base* estecliente);
    bool GM_maxstat(player_base* estecliente);
    bool GM_maxhab(player_base* estecliente);
    bool GM_who(player_base* estecliente, char* whoid);
    bool GM_guildlvl(player_base* estecliente, int lvl);
    bool GM_msg(player_base* estecliente, char* msg);
    bool GM_save(player_base* estecliente);
    //------------------------------------------------------------------------
    bool GM_A_lvl(player_base* estecliente, char* player, int lvl);
    bool GM_A_exp(player_base* estecliente, char* player, long int exp);
    bool GM_A_gold(player_base* estecliente, char* player, long int gold);
    bool GM_A_item(player_base* estecliente, char* player, unsigned int itemid);
    bool GM_A_go(player_base* estecliente, char* player, unsigned int goid, float gox, float goy);
    bool GM_A_buff(player_base* estecliente, char* player);
    bool GM_A_repair(player_base* estecliente, char* player);
    bool GM_A_heal(player_base* estecliente, char* player);
    bool GM_A_maxstat(player_base* estecliente, char* player);
    bool GM_A_maxhab(player_base* estecliente, char* player);
    bool GM_A_guildlvl(player_base* estecliente, char* player, int lvl);
    bool GM_A_save(player_base* estecliente, char* player);
};

extern class Server* server;
#endif
