#include <conio.h>
#include <windows.h>
#include <cstdio>
#include <iostream>

#include "../comum/log.h"
#include "worldserver.h"

using namespace std;

bool Server::GmCmd(player_base* estecliente, char Comando[])
{
     char* cmdo;
     char Comando2[255];
     strcpy(Comando2,Comando);
     cmdo = strtok(Comando," ,.");
     if (cmdo==NULL) {
        if (strcmp(estecliente->lang,"pt_BR")==0) {
             SendMessage(estecliente,"Comando inválido");
        } else if (strcmp(estecliente->lang,"en_US")==0) {
             SendMessage(estecliente,"Invalid command");
        }
        if (estecliente->perm >= ADM_LVL) {
           Log(WADM_ACTION,false,"%s: comando \"%s\" invalido", estecliente->usuario, Comando2);
        } else {
           Log(WGM_ACTION,false,"%s: comando \"%s\" invalido", estecliente->usuario, Comando2);
        }
        return false;
     } else if (strcmp(cmdo,"/lvl")==0) {
            if (estecliente->perm < LVL_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é /lvl número");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is /lvl number");
               }
               return false;
            }
            int lvl=atoi(cmdo);
            if (GM_lvl(estecliente, lvl)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/lvl %i\"", estecliente->usuario, lvl);
               } else {
                  Log(GM_ACTION,false,"%s: \"/lvl %i\"", estecliente->usuario, lvl);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/exp")==0) {
            if (estecliente->perm < EXP_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é /exp número");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is /exp number");
               }
               return false;
            }
            long int exp=atoi(cmdo);
            if (GM_exp(estecliente, exp)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/exp %i\"", estecliente->usuario, exp);
               } else {
                  Log(GM_ACTION,false,"%s: \"/exp %i\"", estecliente->usuario, exp);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/gold")==0) {
            if (estecliente->perm < GOLD_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é /gold número");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is /gold number");
               }
               return false;
            }
            int gold=atoi(cmdo);
            if (GM_gold(estecliente, gold)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/gold %i\"", estecliente->usuario, gold);
               } else {
                  Log(GM_ACTION,false,"%s: \"/gold %i\"", estecliente->usuario, gold);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/item")==0) {
            if (estecliente->perm < ITEM_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é /item item_id item_quantidade");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is /item item_id item_ammount");
               }
               return false;
            }
            int itemid=atoi(cmdo);
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é /item item_id item_quantidade");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is /item item_id item_ammount");
               }
               return false;
            }
            int itemammount=atoi(cmdo);
            if (GM_item(estecliente, itemid, itemammount)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/item %i %i\"", estecliente->usuario, itemid, itemammount);
               } else {
                  Log(GM_ACTION,false,"%s: \"/item %i %i\"", estecliente->usuario, itemid, itemammount);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/ban")==0) {
            if (estecliente->perm < BAN_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é /ban player_nome");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is /ban player_name");
               }
               return false;
            }
            char* banid=cmdo;
            if (GM_ban(estecliente, banid)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/ban %s\"", estecliente->usuario, banid);
               } else {
                  Log(GM_ACTION,false,"%s: \"/ban %s\"", estecliente->usuario, banid);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/unban")==0) {
            if (estecliente->perm < UNBAN_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é /unban player_nome");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is /unban player_name");
               }
               return false;
            }
            char* unbanid=cmdo;
            if (GM_unban(estecliente, unbanid)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/unban %s\"", estecliente->usuario, unbanid);
               } else {
                  Log(GM_ACTION,false,"%s: \"/unban %s\"", estecliente->usuario, unbanid);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/kick")==0) {
            if (estecliente->perm < KICK_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é /kick player_nome");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is /kick player_name");
               }
               return false;
            }
            char* kickid=cmdo;
            if (GM_kick(estecliente, kickid)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/kick %s\"", estecliente->usuario, kickid);
               } else {
                  Log(GM_ACTION,false,"%s: \"/kick %s\"", estecliente->usuario, kickid);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/warn")==0) {
            if (estecliente->perm < WARN_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é /warn player_nome número");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is /warn player_name number");
               }
               return false;
            }
            char* warnid=cmdo;
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é /warn player_nome número");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is /warn player_name number");
               }
               return false;
            }
            int warnnum=atoi(cmdo);
            if (GM_warn(estecliente, warnid, warnnum)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/warn %s %i\"", estecliente->usuario, warnid, warnnum);
               } else {
                  Log(GM_ACTION,false,"%s: \"/warn %s %i\"", estecliente->usuario, warnid, warnnum);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/go")==0) {
            if (estecliente->perm < GO_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é /go mapa_id");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is /go map_id");
               }
               return false;
            }
            int goid=atoi(cmdo);
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é /go mapa_id x y");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is /go map_id x y");
               }
               return false;
            }
            float gox=atoi(cmdo);
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é /go mapa_id x y");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is /go map_id x y");
               }
               return false;
            }
            float goy=atoi(cmdo);
            if (GM_go(estecliente, goid, gox, goy)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/go %i %i %i\"", estecliente->usuario, goid, gox, goy);
               } else {
                  Log(GM_ACTION,false,"%s: \"/go %i %i %i\"", estecliente->usuario, goid, gox, goy);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/buff")==0) {
            if (estecliente->perm < BUFF_PERM) {
               return false;
            }
            if (GM_buff(estecliente)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/buff\"", estecliente->usuario);
               } else {
                  Log(GM_ACTION,false,"%s: \"/buff\"", estecliente->usuario);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/buy")==0) {
            if (estecliente->perm < BUY_PERM) {
               return false;
            }
            if (GM_buy(estecliente)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/buy\"", estecliente->usuario);
               } else {
                  Log(GM_ACTION,false,"%s: \"/buy\"", estecliente->usuario);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/restart_server")==0) {
            if (estecliente->perm < RESTART_PERM) {
               return false;
            }
            if (GM_restart(estecliente)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/restart_server\"", estecliente->usuario);
               } else {
                  Log(GM_ACTION,false,"%s: \"/restart_server\"", estecliente->usuario);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/reload_item")==0) {
            if (estecliente->perm < RELOADITEM_PERM) {
               return false;
            }
            if (GM_reloaditem(estecliente)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/reload_item\"", estecliente->usuario);
               } else {
                  Log(GM_ACTION,false,"%s: \"/reload_item\"", estecliente->usuario);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/reload_npc")==0) {
            if (estecliente->perm < RELOADNPC_PERM) {
               return false;
            }
            if (GM_reloadnpc(estecliente)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/reload_npc\"", estecliente->usuario);
               } else {
                  Log(GM_ACTION,false,"%s: \"/reload_npc\"", estecliente->usuario);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/reload_monster")==0) {
            if (estecliente->perm < RELOADMONSTER_PERM) {
               return false;
            }
            if (GM_reloadmonster(estecliente)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/reload_monster\"", estecliente->usuario);
               } else {
                  Log(GM_ACTION,false,"%s: \"/reload_monster\"", estecliente->usuario);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/reload_quest")==0) {
            if (estecliente->perm < RELOADQUEST_PERM) {
               return false;
            }
            if (GM_reloadquest(estecliente)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/reload_quest\"", estecliente->usuario);
               } else {
                  Log(GM_ACTION,false,"%s: \"/reload_quest\"", estecliente->usuario);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/reload_skill")==0) {
            if (estecliente->perm < RELOADSKILL_PERM) {
               return false;
            }
            if (GM_reloadskill(estecliente)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/reload_skill\"", estecliente->usuario);
               } else {
                  Log(GM_ACTION,false,"%s: \"/reload_skill\"", estecliente->usuario);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/reload_guild")==0) {
            if (estecliente->perm < RELOADGUILD_PERM) {
               return false;
            }
            if (GM_reloadguild(estecliente)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/reload_guild\"", estecliente->usuario);
               } else {
                  Log(GM_ACTION,false,"%s: \"/reload_guild\"", estecliente->usuario);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/tempo")==0) {
            if (estecliente->perm < TEMPO_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é /tempo nome");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is /tempo name");
               }
               return false;
            }
            char* tempoid=cmdo;
            if (GM_tempo(estecliente, tempoid)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/tempo %s\"", estecliente->usuario, tempoid);
               } else {
                  Log(GM_ACTION,false,"%s: \"/tempo %s\"", estecliente->usuario, tempoid);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/repair")==0) {
            if (estecliente->perm < REPAIR_PERM) {
               return false;
            }
            if (GM_repair(estecliente)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/repair\"", estecliente->usuario);
               } else {
                  Log(GM_ACTION,false,"%s: \"/repair\"", estecliente->usuario);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/summon")==0) {
            if (estecliente->perm < SUMMON_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é /summon monstro_id");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is /summon monster_id");
               }
               return false;
            }
            int summonid=atoi(cmdo);
            if (GM_summon(estecliente, summonid)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/summon %i\"", estecliente->usuario, summonid);
               } else {
                  Log(GM_ACTION,false,"%s: \"/summon %i\"", estecliente->usuario, summonid);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/clear_map")==0) {
            if (estecliente->perm < CLEAR_PERM) {
               return false;
            }
            if (GM_clear(estecliente)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/clear_map\"", estecliente->usuario);
               } else {
                  Log(GM_ACTION,false,"%s: \"/clear_map\"", estecliente->usuario);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/call")==0) {
            if (estecliente->perm < CALL_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é /call player_nome");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is /call player_name");
               }
               return false;
            }
            char* callid=cmdo;
            if (GM_call(estecliente, callid)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/call %s\"", estecliente->usuario, callid);
               } else {
                  Log(GM_ACTION,false,"%s: \"/call %s\"", estecliente->usuario, callid);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/heal")==0) {
            if (estecliente->perm < HEAL_PERM) {
               return false;
            }
            if (GM_heal(estecliente)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/heal\"", estecliente->usuario);
               } else {
                  Log(GM_ACTION,false,"%s: \"/heal\"", estecliente->usuario);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/hide")==0) {
            if (estecliente->perm < HIDE_PERM) {
               return false;
            }
            if (GM_hide(estecliente)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/hide\"", estecliente->usuario);
               } else {
                  Log(GM_ACTION,false,"%s: \"/hide\"", estecliente->usuario);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/max_stats")==0) {
            if (estecliente->perm < MAXSTAT_PERM) {
               return false;
            }
            if (GM_maxstat(estecliente)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/max_stats\"", estecliente->usuario);
               } else {
                  Log(GM_ACTION,false,"%s: \"/max_stats\"", estecliente->usuario);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/max_hab")==0) {
            if (estecliente->perm < MAXHAB_PERM) {
               return false;
            }
            if (GM_maxhab(estecliente)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/max_hab\"", estecliente->usuario);
               } else {
                  Log(GM_ACTION,false,"%s: \"/max_hab\"", estecliente->usuario);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/who")==0) {
            if (estecliente->perm < WHO_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é /who player_nome");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is /who player_name");
               }
               return false;
            }
            char* whoid=cmdo;
            if (GM_who(estecliente, whoid)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/who %s\"", estecliente->usuario, whoid);
               } else {
                  Log(GM_ACTION,false,"%s: \"/who %s\"", estecliente->usuario, whoid);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/guild_lvl")==0) {
            if (estecliente->perm < GUILDLVL_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é /guild_lvl número");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is /guild_lvl number");
               }
               return false;
            }
            int lvl=atoi(cmdo);
            if (GM_guildlvl(estecliente, lvl)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/guild_lvl %i\"", estecliente->usuario, lvl);
               } else {
                  Log(GM_ACTION,false,"%s: \"/guild_lvl %i\"", estecliente->usuario, lvl);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/msg")==0) {
            if (estecliente->perm < MSG_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é /msg texto");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is /msg text");
               }
               return false;
            }
            char* msg=Comando2;
            CortaStr(msg, 5);
            if (GM_msg(estecliente, msg)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/msg %s\"", estecliente->usuario, msg);
               } else {
                  Log(GM_ACTION,false,"%s: \"/msg %s\"", estecliente->usuario, msg);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"/save")==0) {
            if (estecliente->perm < SAVE_PERM) {
               return false;
            }
            if (GM_save(estecliente)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"/save\"", estecliente->usuario);
               } else {
                  Log(GM_ACTION,false,"%s: \"/save\"", estecliente->usuario);
               }
               return true;
            } else {
               return false;
            }
//------------------------------------------------------------------------------
     } else if (strcmp(cmdo,"#lvl")==0) {
            if (estecliente->perm < A_LVL_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é #lvl player_nome número");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is #lvl player_name number");
               }
               return false;
            }
            char* player=cmdo;
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é #lvl player_nome número");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is #lvl player_name number");
               }
               return false;
            }
            int lvl=atoi(cmdo);
            if (GM_A_lvl(estecliente, player, lvl)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"#lvl %s %i\"", estecliente->usuario, player, lvl);
               } else {
                  Log(GM_ACTION,false,"%s: \"#lvl %s %i\"", estecliente->usuario, player, lvl);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"#exp")==0) {
            if (estecliente->perm < A_EXP_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é #exp player_nome número");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is #exp player_name number");
               }
               return false;
            }
            char* player=cmdo;
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é #exp player_nome número");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is #exp player_name number");
               }
               return false;
            }
            long int exp=atoi(cmdo);
            if (GM_A_exp(estecliente, player, exp)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"#exp %s %i\"", estecliente->usuario, player, exp);
               } else {
                  Log(GM_ACTION,false,"%s: \"#exp %s %i\"", estecliente->usuario, player, exp);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"#gold")==0) {
            if (estecliente->perm < A_GOLD_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é #gold player_nome número");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is #gold player_name number");
               }
               return false;
            }
            char* player=cmdo;
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é #gold player_nome número");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is #gold player_name number");
               }
               return false;
            }
            int gold=atoi(cmdo);
            if (GM_A_gold(estecliente, player, gold)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"#gold %s %i\"", estecliente->usuario, player, gold);
               } else {
                  Log(GM_ACTION,false,"%s: \"#gold %s %i\"", estecliente->usuario, player, gold);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"#item")==0) {
            if (estecliente->perm < A_ITEM_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é #item player_nome item_id");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is #item player_name item_id");
               }
               return false;
            }
            char* player=cmdo;
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é #item player_nome item_id");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is #item player_name item_id");
               }
               return false;
            }
            int itemid=atoi(cmdo);
            if (GM_A_item(estecliente, player, itemid)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"#item %s %i\"", estecliente->usuario, player, itemid);
               } else {
                  Log(GM_ACTION,false,"%s: \"#item %s %i\"", estecliente->usuario, player, itemid);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"#go")==0) {
            if (estecliente->perm < A_GO_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é #go player_nome map_id x y");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is #go player_name map_id x y");
               }
               return false;
            }
            char* player=cmdo;
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é #go player_nome map_id x y");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is #go player_name map_id x y");
               }
               return false;
            }
            int goid=atoi(cmdo);
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é #go player_nome map_id x y");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is #go player_name map_id x y");
               }
               return false;
            }
            int gox=atoi(cmdo);
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é #go player_nome map_id x y");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is #go player_name map_id x y");
               }
               return false;
            }
            int goy=atoi(cmdo);
            if (GM_A_go(estecliente, player, goid, gox, goy)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"#go %s %i %i %i\"", estecliente->usuario, player, goid, gox, goy);
               } else {
                  Log(GM_ACTION,false,"%s: \"#go %s %i %i %i\"", estecliente->usuario, player, goid, gox, goy);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"#buff")==0) {
            if (estecliente->perm < A_BUFF_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é #buff player_nome");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is #buff player_name");
               }
               return false;
            }
            char* player=cmdo;
            if (GM_A_buff(estecliente, player)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"#buff %s\"", estecliente->usuario, player);
               } else {
                  Log(GM_ACTION,false,"%s: \"#buff %s\"", estecliente->usuario, player);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"#repair")==0) {
            if (estecliente->perm < A_REPAIR_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é #repair player_nome");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is #repair player_name");
               }
               return false;
            }
            char* player=cmdo;
            if (GM_A_repair(estecliente, player)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"#repair %s\"", estecliente->usuario, player);
               } else {
                  Log(GM_ACTION,false,"%s: \"#repair %s\"", estecliente->usuario, player);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"#heal")==0) {
            if (estecliente->perm < A_HEAL_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é #heal player_nome");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is #heal player_name");
               }
               return false;
            }
            char* player=cmdo;
            if (GM_A_heal(estecliente, player)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"#heal %s\"", estecliente->usuario, player);
               } else {
                  Log(GM_ACTION,false,"%s: \"#heal %s\"", estecliente->usuario, player);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"#max_stats")==0) {
            if (estecliente->perm < A_MAXSTAT_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é #max_stats player_nome");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is #max_stats player_name");
               }
               return false;
            }
            char* player=cmdo;
            if (GM_A_maxstat(estecliente, player)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"#max_stats %s\"", estecliente->usuario, player);
               } else {
                  Log(GM_ACTION,false,"%s: \"#max_stats %s\"", estecliente->usuario, player);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"#max_hab")==0) {
            if (estecliente->perm < A_MAXHAB_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é #max_hab player_nome");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is #max_hab player_name");
               }
               return false;
            }
            char* player=cmdo;
            if (GM_A_maxhab(estecliente, player)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"#max_hab %s\"", estecliente->usuario, player);
               } else {
                  Log(GM_ACTION,false,"%s: \"#max_hab %s\"", estecliente->usuario, player);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"#guild_lvl")==0) {
            if (estecliente->perm < A_GUILDLVL_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é #guild_lvl player_nome número");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is #guild_lvl player_name number");
               }
               return false;
            }
            char* player=cmdo;
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é #guild_lvl player_nome número");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is #guild_lvl player_name number");
               }
               return false;
            }
            int lvl=atoi(cmdo);
            if (GM_A_guildlvl(estecliente, player, lvl)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"#guild_lvl %s %i\"", estecliente->usuario, player, lvl);
               } else {
                  Log(GM_ACTION,false,"%s: \"#guild_lvl %s %i\"", estecliente->usuario, player, lvl);
               }
               return true;
            } else {
               return false;
            }
     } else if (strcmp(cmdo,"#save")==0) {
            if (estecliente->perm < A_SAVE_PERM) {
               return false;
            }
            if ((cmdo = strtok(NULL," ,."))==NULL) {
               if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"A sintaxe correta é #save player_nome");
               } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"The correct syntax is #save player_name");
               }
               return false;
            }
            char* player=cmdo;
            if (GM_A_save(estecliente, player)) {
               if (estecliente->perm >= ADM_LVL) {
                  Log(ADM_ACTION,false,"%s: \"#save %s\"", estecliente->usuario, player);
               } else {
                  Log(GM_ACTION,false,"%s: \"#save %s\"", estecliente->usuario, player);
               }
               return true;
            } else {
               return false;
            }
//------------------------------------------------------------------------------
     } else {
            if (strcmp(estecliente->lang,"pt_BR")==0) {
                 SendMessage(estecliente,"Comando inválido");
            } else if (strcmp(estecliente->lang,"en_US")==0) {
                 SendMessage(estecliente,"Invalid command");
            }
            if (estecliente->perm >= ADM_LVL) {
               Log(WADM_ACTION,false,"%s: comando \"%s\" invalido", estecliente->usuario, Comando2);
            } else {
               Log(WGM_ACTION,false,"%s: comando \"%s\" invalido", estecliente->usuario, Comando2);
            }
            return false;
     }
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

bool Server::GM_lvl(player_base* estecliente, int lvl)
{
     if (lvl > 0) {
        if (lvl > (signed)(LVL_MAX - estecliente->chars[estecliente->chara].lvl)) {
           lvl = (LVL_MAX - estecliente->chars[estecliente->chara].lvl);
        }
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Você subiu %i leveis!", lvl);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"You reached %i levels up!", lvl);
        }
     } else {
        if ((estecliente->chars[estecliente->chara].lvl + lvl) <= 0) {
           lvl = -(estecliente->chars[estecliente->chara].lvl - 1);
        }
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Você desceu %i leveis!", -lvl);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"You lost %i levels!", -lvl);
        }
     }
     estecliente->chars[estecliente->chara].lvl += lvl;
     SalvaPlayer(estecliente);
     return true;
}

bool Server::GM_exp(player_base* estecliente, long int exp)
{
     if (exp > 0 ) {
        if (exp > (signed)(EXP_MAX - estecliente->chars[estecliente->chara].exp)) {
           exp = (EXP_MAX - estecliente->chars[estecliente->chara].exp);
        }
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Você ganhou %i pontos de experiência!", exp);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"You acquired %i experience points!", exp);
        }
     } else {
        if ((estecliente->chars[estecliente->chara].exp + exp) <= 0) {
           exp = -(estecliente->chars[estecliente->chara].exp - 1);
        }
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Você perdeu %i pontos de experiência!", -exp);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"You lost %i experiencie points!", -exp);
        }
     }
     SalvaPlayer(estecliente);
     estecliente->chars[estecliente->chara].exp += exp;
     return true;
}

bool Server::GM_gold(player_base* estecliente, long int gold)
{
     if (gold > 0 ) {
        if (gold > (signed)(GOLD_MAX - estecliente->chars[estecliente->chara].gold)) {
           gold = (GOLD_MAX - estecliente->chars[estecliente->chara].gold);
        }
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Você ganhou %i golds!", gold);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"You gained %i golds!", gold);
        }
     } else {
        if ((estecliente->chars[estecliente->chara].exp + gold) <= 0) {
           gold = -(estecliente->chars[estecliente->chara].gold - 1);
        }
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Você perdeu %i golds!", -gold);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"You lost %i golds!", -gold);
        }
     }
     SalvaPlayer(estecliente);
     estecliente->chars[estecliente->chara].gold += gold;
     return true;
}

bool Server::GM_item(player_base* estecliente, unsigned int itemid, unsigned int itemammount)
{
     return true;
}

bool Server::GM_ban(player_base* estecliente, char* banid)
{
     player_base* outrocliente = GetPlayer(banid);
     if (outrocliente != NULL) {
        if (estecliente->perm > outrocliente->perm) {
            outrocliente->ban = 1;
            if (strcmp(estecliente->lang,"pt_BR")==0) {
                SendMessage(estecliente,"Player %i:%s banido", outrocliente->id, outrocliente->usuario);
            } else if (strcmp(estecliente->lang,"en_US")==0) {
                SendMessage(estecliente,"Player %i:%s banned", outrocliente->id, outrocliente->usuario);
            }
            if (strcmp(outrocliente->lang,"pt_BR")==0) {
                SendMessage(outrocliente,"Você foi banido");
            } else if (strcmp(outrocliente->lang,"en_US")==0) {
                SendMessage(outrocliente,"You has been banned");
            }
            SalvaPlayer(outrocliente);
            DesconectaPlayer(outrocliente);
            return true;
        } else {
            return false;
        }
     } else {
        player_base* outrocliente = GetPlayerDB(banid);
        if (outrocliente != NULL) {
            QueryDB("UPDATE users SET ban ='1' WHERE id ='%i'", outrocliente->id);
            return true;
        } else {
            if (strcmp(estecliente->lang,"pt_BR")==0) {
               SendMessage(estecliente,"Este player: %s não existe ou não está logado", banid);
            } else if (strcmp(estecliente->lang,"en_US")==0) {
               SendMessage(estecliente,"This Player: %s does not exist or is not logged in", banid);
            }
            return false;
        }
     }
}

bool Server::GM_unban(player_base* estecliente, char* unbanid)
{
     player_base* outrocliente = GetPlayerDB(unbanid);
     if (outrocliente != NULL) {
        QueryDB("UPDATE users SET ban ='0' WHERE id ='%i'", outrocliente->id);
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Player %i:%s desbanido", outrocliente->id, outrocliente->usuario);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"Player %i:%s unbanned", outrocliente->id, outrocliente->usuario);
        }
     } else {
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Este player: %s não existe", unbanid);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"This Player: %s does not exist", unbanid);
        }
     }
     return true;
}

bool Server::GM_kick(player_base* estecliente, char* kickid)
{
     player_base* outrocliente = GetPlayer(kickid);
     if (outrocliente != NULL) {
         if (estecliente->perm > outrocliente->perm) {
            if (strcmp(estecliente->lang,"pt_BR")==0) {
                SendMessage(estecliente,"Player %i:%s kickado", outrocliente->id, outrocliente->usuario);
            } else if (strcmp(estecliente->lang,"en_US")==0) {
                SendMessage(estecliente,"Player %i:%s kicked", outrocliente->id, outrocliente->usuario);
            }
            if (strcmp(outrocliente->lang,"pt_BR")==0) {
                SendMessage(outrocliente,"Você foi kickado");
            } else if (strcmp(outrocliente->lang,"en_US")==0) {
                SendMessage(outrocliente,"You has been kicked");
            }
            DesconectaPlayer(outrocliente);
            return true;
         } else {
            return false;
         }
     } else {
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Este player: %s não existe ou não está logado", kickid);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"This Player: %s does not exist or is not logged in", kickid);
        }
        return false;
     }
}

bool Server::GM_warn(player_base* estecliente, char* warnid, int warnnum)
{
    player_base* outrocliente = GetPlayer(warnid);
    if (outrocliente != NULL) {
        if (estecliente->perm > outrocliente->perm) {
            outrocliente->warn += warnnum;
            if (strcmp(estecliente->lang,"pt_BR")==0) {
                SendMessage(estecliente,"O player %i:%s recebeu %i pontos de warn", outrocliente->id, outrocliente->usuario, warnnum);
            } else if (strcmp(estecliente->lang,"en_US")==0) {
                SendMessage(estecliente,"The player %i:%s received %i warn points", outrocliente->id, outrocliente->usuario, warnnum);
            }
            if (strcmp(outrocliente->lang,"pt_BR")==0) {
                SendMessage(outrocliente,"Você recebeu %i pontos de warn", warnnum);
            } else if (strcmp(outrocliente->lang,"en_US")==0) {
                SendMessage(outrocliente,"You have received %i warn points", warnnum);
            }
            SalvaPlayer(outrocliente);
            return true;
        } else {
            return false;
        }
    } else {
        if (strcmp(estecliente->lang,"pt_BR")==0) {
            SendMessage(estecliente,"Este player: %s não existe ou não está logado", warnid);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
            SendMessage(estecliente,"This Player: %s does not exist or is not logged in", warnid);
        }
        return false;
    }
}

bool Server::GM_go(player_base* estecliente, unsigned int goid, float gox, float goy)
{
    estecliente->chars[estecliente->chara].map = goid;
    estecliente->chars[estecliente->chara].x = gox;
    estecliente->chars[estecliente->chara].y = goy;
    if (strcmp(estecliente->lang,"pt_BR")==0) {
        SendMessage(estecliente,"Você foi teleportado para o mapa:%i X:%i Y:%i", goid, gox, goy);
    } else if (strcmp(estecliente->lang,"en_US")==0) {
        SendMessage(estecliente,"You have been teleported to map:%i X:%i Y:%i", goid, gox, goy);
    }
    return true;
}

bool Server::GM_buff(player_base* estecliente)
{
    return true;
}

bool Server::GM_buy(player_base* estecliente)
{
    return true;
}

bool Server::GM_restart(player_base* estecliente)
{
    RESTART_SERVER = 1;
    return true;
}

bool Server::GM_reloaditem(player_base* estecliente)
{
    return true;
}

bool Server::GM_reloadnpc(player_base* estecliente)
{
    return true;
}

bool Server::GM_reloadmonster(player_base* estecliente)
{
    return true;
}

bool Server::GM_reloadquest(player_base* estecliente)
{
    return true;
}

bool Server::GM_reloadskill(player_base* estecliente)
{
    return true;
}

bool Server::GM_reloadguild(player_base* estecliente)
{
    pthread_mutex_lock(&MutexLoad);
    Guilds.clear();
    LoadGuilds();
    pthread_mutex_unlock(&MutexLoad);
    if (strcmp(estecliente->lang,"pt_BR")==0) {
        SendMessage(estecliente,"A lista de guilds foi recarregada");
    } else if (strcmp(estecliente->lang,"en_US")==0) {
        SendMessage(estecliente,"The guilds list has been reloaded");
    }
    return true;
}

bool Server::GM_tempo(player_base* estecliente, char* tempoid)
{
     if (strcmp(tempoid,"dia")==0) {

     } else if (strcmp(tempoid,"noite")==0) {

     } else if (strcmp(tempoid,"chuva")==0) {

     } else if (strcmp(tempoid,"seco")==0) {

     } else {
        return false;
     }
     return true;
}

bool Server::GM_repair(player_base* estecliente)
{
     return true;
}

bool Server::GM_summon(player_base* estecliente, unsigned int summonid)
{
     return true;
}

bool Server::GM_clear(player_base* estecliente)
{
     return true;
}

bool Server::GM_call(player_base* estecliente, char* callid)
{
     player_base* outrocliente = GetPlayer(callid);
     if (outrocliente != NULL) {
         if (estecliente->perm > outrocliente->perm) {
            outrocliente->chars[outrocliente->chara].map = estecliente->chars[estecliente->chara].map;
            outrocliente->chars[outrocliente->chara].x = estecliente->chars[estecliente->chara].x;
            outrocliente->chars[outrocliente->chara].y = estecliente->chars[estecliente->chara].y;
            if (strcmp(estecliente->lang,"pt_BR")==0) {
                SendMessage(estecliente,"O player %i:%s foi teleportado até você", outrocliente->id, outrocliente->usuario);
            } else if (strcmp(estecliente->lang,"en_US")==0) {
                SendMessage(estecliente,"The player %i:%s has been teleported to you", outrocliente->id, outrocliente->usuario);
            }
            if (strcmp(outrocliente->lang,"pt_BR")==0) {
                SendMessage(outrocliente,"Você foi teleportado até %s", estecliente->chars[estecliente->chara].nome);
            } else if (strcmp(outrocliente->lang,"en_US")==0) {
                SendMessage(outrocliente,"You has been teleported to %s", estecliente->chars[estecliente->chara].nome);
            }
            return true;
         } else {
            return false;
         }
     } else {
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Este player: %s não existe ou não está logado", callid);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"This Player: %s does not exist or is not logged in", callid);
        }
        return false;
     }
}

bool Server::GM_heal(player_base* estecliente)
{
     estecliente->chars[estecliente->chara].hp = estecliente->chars[estecliente->chara].hp_max;
     estecliente->chars[estecliente->chara].mp = estecliente->chars[estecliente->chara].mp_max;
     if (strcmp(estecliente->lang,"pt_BR")==0) {
        SendMessage(estecliente,"Sua hp e seu mp foram restaurados");
     } else if (strcmp(estecliente->lang,"en_US")==0) {
        SendMessage(estecliente,"Your hp and your mp have been restaured");
     }
     return true;
}

bool Server::GM_hide(player_base* estecliente)
{
     if (estecliente->hide == 0) {
        estecliente->hide = 1;
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Você agora não está visível para outros players");
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"You are now non visible to other players");
        }
     } else {
        estecliente->hide = 0;
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Você agora está visível para outros players");
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"You are now visible to other players");
        }
     }
     return true;
}

bool Server::GM_maxstat(player_base* estecliente)
{
     estecliente->chars[estecliente->chara].hp_max = LIFE_MAX;
     estecliente->chars[estecliente->chara].mp_max = LIFE_MAX;
     estecliente->chars[estecliente->chara].sau = STATS_MAX;
     estecliente->chars[estecliente->chara].str = STATS_MAX;
     estecliente->chars[estecliente->chara].per = STATS_MAX;
     estecliente->chars[estecliente->chara].dex = STATS_MAX;
     estecliente->chars[estecliente->chara].agi = STATS_MAX;
     estecliente->chars[estecliente->chara].magia = STATS_MAX;
     if (strcmp(estecliente->lang,"pt_BR")==0) {
        SendMessage(estecliente,"Todos os seus status foram setados para o máximo");
     } else if (strcmp(estecliente->lang,"en_US")==0) {
        SendMessage(estecliente,"All of your stats have been set to the maximum");
     }
     return true;
}

bool Server::GM_maxhab(player_base* estecliente)
{
     return true;
}

bool Server::GM_who(player_base* estecliente, char* whoid)
{
     player_base* outrocliente = GetPlayer(whoid);
     if (outrocliente != NULL) {
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente, "Usuário: %i:%s\nChar: %i:%s\nProfissão: %i\nSexo: %i\nLevel: %i\nPermissão: %i\nWarn: %i", outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome, outrocliente->chars[outrocliente->chara].profissao, outrocliente->chars[outrocliente->chara].sexo, outrocliente->chars[outrocliente->chara].lvl, outrocliente->perm, outrocliente->warn);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente, "User: %i:%s\nChar: %i:%s\nProfission: %i\nSex: %i\nLevel: %i\nPermission: %i\nWarn: %i", outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome, outrocliente->chars[outrocliente->chara].profissao, outrocliente->chars[outrocliente->chara].sexo, outrocliente->chars[outrocliente->chara].lvl, outrocliente->perm, outrocliente->warn);
        }
     } else {
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Este player: %s não existe ou não está logado", whoid);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"This Player: %s does not exist or is not logged in", whoid);
        }
     }
     return true;
}

bool Server::GM_guildlvl(player_base* estecliente, int lvl)
{
     guilds_base* guild = GetGuildId(estecliente->chars[estecliente->chara].guild);
     if (guild != NULL) {
        if (lvl > 0) {
            if (lvl > (signed)(GUILD_LVL_MAX - guild->lvl)) {
               lvl = (GUILD_LVL_MAX - guild->lvl);
            }
            SendMessageGuild(guild->id, "Sua guild recebeu %i leveis", "Your guild received %i levels", lvl);
        } else {
            if ((guild->lvl + lvl) <= 0) {
               lvl = -(guild->lvl - 1);
            }
            SendMessageGuild(guild->id, "Sua guild perdeu %i leveis", "Your guild lost %i levels", lvl);
        }
        guild->lvl += lvl;
     } else {
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Você não pertence a nenhuma guild!");
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"You do not have a guild!");
        }
     }
     return true;
}

bool Server::GM_msg(player_base* estecliente, char* msg)
{
     MenssagemServer(estecliente, msg);
     if (strcmp(estecliente->lang,"pt_BR")==0) {
        SendMessage(estecliente,"Sua menssagem foi enviada para todos os players no servidor");
     } else if (strcmp(estecliente->lang,"en_US")==0) {
        SendMessage(estecliente,"Your message has been sent to all players in the server");
     }
     return true;
}

bool Server::GM_save(player_base* estecliente)
{
     estecliente->chars[estecliente->chara].save_map = estecliente->chars[estecliente->chara].map;
     estecliente->chars[estecliente->chara].save_x = estecliente->chars[estecliente->chara].x;
     estecliente->chars[estecliente->chara].save_y = estecliente->chars[estecliente->chara].y;
     if (strcmp(estecliente->lang,"pt_BR")==0) {
        SendMessage(estecliente,"Sua posição atual foi salva como seu ponto de respawn padrão");
     } else if (strcmp(estecliente->lang,"en_US")==0) {
        SendMessage(estecliente,"Your actual position has been saved as your default respawn point");
     }
     return true;
}
//------------------------------------------------------------------------------
bool Server::GM_A_lvl(player_base* estecliente, char* player, int lvl)
{
     player_base* outrocliente = GetPlayer(player);
     if (outrocliente != NULL) {
         if (estecliente->perm > outrocliente->perm) {
            outrocliente->chars[outrocliente->chara].lvl += lvl;
            if (strcmp(estecliente->lang,"pt_BR")==0) {
                SendMessage(estecliente,"Você concedeu %i leveis para o player %i:%s Char:%i:%s", lvl, outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome);
            } else if (strcmp(estecliente->lang,"en_US")==0) {
                SendMessage(estecliente,"You have been gived %i levels to the player %i:%s Char:%i:%s", lvl, outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome);
            }
            if (strcmp(outrocliente->lang,"pt_BR")==0) {
                SendMessage(outrocliente,"Você recebeu %i leveis do player: %s", lvl, estecliente->chars[estecliente->chara].nome);
            } else if (strcmp(outrocliente->lang,"en_US")==0) {
                SendMessage(outrocliente,"You have received %i levels from the player: %s", lvl, estecliente->chars[estecliente->chara].nome);
            }
            return true;
         }
         return false;
     } else {
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Este player: %s não existe ou não está logado", player);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"This Player: %s does not exist or is not logged in", player);
        }
        return false;
     }
}

bool Server::GM_A_exp(player_base* estecliente, char* player, long int exp)
{
    player_base* outrocliente = GetPlayer(player);
    if (outrocliente != NULL) {
        if (estecliente->perm > outrocliente->perm) {
            outrocliente->chars[outrocliente->chara].exp += exp;
            if (strcmp(estecliente->lang,"pt_BR")==0) {
                SendMessage(estecliente,"Você concedeu %i pontos de experiência para o player %i:%s Char:%i:%s", exp, outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome);
            } else if (strcmp(estecliente->lang,"en_US")==0) {
                SendMessage(estecliente,"You have been gived %i experiencie points to the player %i:%s Char:%i:%s", exp, outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome);
            }
            if (strcmp(outrocliente->lang,"pt_BR")==0) {
                SendMessage(outrocliente,"Você recebeu %i pontos de experiência do player: %s", exp, estecliente->chars[estecliente->chara].nome);
            } else if (strcmp(outrocliente->lang,"en_US")==0) {
                SendMessage(outrocliente,"You have received %i experiencia points from the player: %s", exp, estecliente->chars[estecliente->chara].nome);
            }
            return true;
        }
        return false;
    } else {
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Este player: %s não existe ou não está logado", player);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"This Player: %s does not exist or is not logged in", player);
        }
        return false;
    }
}

bool Server::GM_A_gold(player_base* estecliente, char* player, long int gold)
{
     player_base* outrocliente = GetPlayer(player);
     if (outrocliente != NULL) {
         if (estecliente->perm > outrocliente->perm) {
            outrocliente->chars[outrocliente->chara].gold += gold;
            if (strcmp(estecliente->lang,"pt_BR")==0) {
                SendMessage(estecliente,"Você concedeu %i golds para o player %i:%s Char:%i:%s", gold, outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome);
            } else if (strcmp(estecliente->lang,"en_US")==0) {
                SendMessage(estecliente,"You have been gived %i golds to the player %i:%s Char:%i:%s", gold, outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome);
            }
            if (strcmp(outrocliente->lang,"pt_BR")==0) {
                SendMessage(outrocliente,"Você recebeu %i golds do player: %s", gold, estecliente->chars[estecliente->chara].nome);
            } else if (strcmp(outrocliente->lang,"en_US")==0) {
                SendMessage(outrocliente,"You have received %i golds from the player: %s", gold, estecliente->chars[estecliente->chara].nome);
            }
            return true;
         }
         return false;
     } else {
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Este player: %s não existe ou não está logado", player);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"This Player: %s does not exist or is not logged in", player);
        }
        return false;
     }
}

bool Server::GM_A_item(player_base* estecliente, char* player, unsigned int itemid)
{
     player_base* outrocliente = GetPlayer(player);
     if (outrocliente != NULL) {
         if (estecliente->perm > outrocliente->perm) {
            return true;
         }
         return false;
     } else {
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Este player: %s não existe ou não está logado", player);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"This Player: %s does not exist or is not logged in", player);
        }
        return false;
     }
}

bool Server::GM_A_go(player_base* estecliente, char* player, unsigned int goid, float gox, float goy)
{
     player_base* outrocliente = GetPlayer(player);
     if (outrocliente != NULL) {
         if (estecliente->perm > outrocliente->perm) {
            outrocliente->chars[outrocliente->chara].map = goid;
            outrocliente->chars[outrocliente->chara].x = gox;
            outrocliente->chars[outrocliente->chara].y = goy;
            if (strcmp(estecliente->lang,"pt_BR")==0) {
                SendMessage(estecliente,"Você teleportou o player %i:%s Char:%i:%s para mapa:%i X:%i Y:%i", outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome, goid, gox, goy);
            } else if (strcmp(estecliente->lang,"en_US")==0) {
                SendMessage(estecliente,"You have been teleported the player %i:%s Char:%i:%s to map:%i X:%i Y:%i", outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome, goid, gox, goy);
            }
            if (strcmp(outrocliente->lang,"pt_BR")==0) {
                SendMessage(outrocliente,"Você foi teleportado até o player: %s", estecliente->chars[estecliente->chara].nome);
            } else if (strcmp(outrocliente->lang,"en_US")==0) {
                SendMessage(outrocliente,"You has been teleported to the player: %s", estecliente->chars[estecliente->chara].nome);
            }
            return true;
         }
         return false;
     } else {
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Este player: %s não existe ou não está logado", player);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"This Player: %s does not exist or is not logged in", player);
        }
        return false;
     }
}

bool Server::GM_A_buff(player_base* estecliente, char* player)
{
     player_base* outrocliente = GetPlayer(player);
     if (outrocliente != NULL) {
         if (estecliente->perm > outrocliente->perm) {
            return true;
         }
         return false;
     } else {
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Este player: %s não existe ou não está logado", player);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"This Player: %s does not exist or is not logged in", player);
        }
        return false;
     }
}

bool Server::GM_A_repair(player_base* estecliente, char* player)
{
     player_base* outrocliente = GetPlayer(player);
     if (outrocliente != NULL) {
         if (estecliente->perm > outrocliente->perm) {
            return true;
         }
         return false;
     } else {
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Este player: %s não existe ou não está logado", player);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"This Player: %s does not exist or is not logged in", player);
        }
        return false;
     }
}

bool Server::GM_A_heal(player_base* estecliente, char* player)
{
     player_base* outrocliente = GetPlayer(player);
     if (outrocliente != NULL) {
         if (estecliente->perm > outrocliente->perm) {
            outrocliente->chars[outrocliente->chara].hp = outrocliente->chars[outrocliente->chara].hp_max;
            outrocliente->chars[outrocliente->chara].mp = outrocliente->chars[outrocliente->chara].mp_max;
            if (strcmp(estecliente->lang,"pt_BR")==0) {
                SendMessage(estecliente,"Você restaurou o hp e o mp do player %i:%s Char:%i:%s", outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome);
            } else if (strcmp(estecliente->lang,"en_US")==0) {
                SendMessage(estecliente,"You have been restaured the hp and the mp of the player %i:%s Char:%i:%s", outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome);
            }
            if (strcmp(outrocliente->lang,"pt_BR")==0) {
                SendMessage(outrocliente,"Seu HP e seu MP foram restaurados pelo player: %s", estecliente->chars[estecliente->chara].nome);
            } else if (strcmp(outrocliente->lang,"en_US")==0) {
                SendMessage(outrocliente,"Your HP and your MP has been restaured by the player: %s", estecliente->chars[estecliente->chara].nome);
            }
            return true;
         }
         return false;
     } else {
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Este player: %s não existe ou não está logado", player);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"This Player: %s does not exist or is not logged in", player);
        }
        return false;
     }
}

bool Server::GM_A_maxstat(player_base* estecliente, char* player)
{
     player_base* outrocliente = GetPlayer(player);
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
            if (strcmp(estecliente->lang,"pt_BR")==0) {
                SendMessage(estecliente,"Você setou todos os status do player %i:%s Char:%i:%s para o máximo", outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome);
            } else if (strcmp(estecliente->lang,"en_US")==0) {
                SendMessage(estecliente,"You have been set all stats of the player %i:%s Char:%i:%s to the maximum", outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome);
            }
            if (strcmp(outrocliente->lang,"pt_BR")==0) {
                SendMessage(outrocliente,"Todos seus status foram setatos para o máximo pelo player: %s", estecliente->chars[estecliente->chara].nome);
            } else if (strcmp(outrocliente->lang,"en_US")==0) {
                SendMessage(outrocliente,"All your stats has been set to the maximum by the player: %s", estecliente->chars[estecliente->chara].nome);
            }
            return true;
         }
         return false;
     } else {
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Este player: %s não existe ou não está logado", player);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"This Player: %s does not exist or is not logged in", player);
        }
        return false;
     }
}

bool Server::GM_A_maxhab(player_base* estecliente, char* player)
{
     player_base* outrocliente = GetPlayer(player);
     if (outrocliente != NULL) {
         if (estecliente->perm > outrocliente->perm) {
            return true;
         }
         return false;
     } else {
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Este player: %s não existe ou não está logado", player);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"This Player: %s does not exist or is not logged in", player);
        }
        return false;
     }
}

bool Server::GM_A_guildlvl(player_base* estecliente, char* player, int lvl)
{
     player_base* outrocliente = GetPlayer(player);
     if (outrocliente != NULL) {
         if (estecliente->perm > outrocliente->perm) {
            guilds_base* guild = GetGuildId(outrocliente->chars[outrocliente->chara].guild);
            if (guild != NULL) {
                guild->lvl += lvl;
                if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"Você concedeu %i leveis para a guild %i:%s do player %i:%s Char:%i:%s", lvl, guild->id, guild->nome, outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome);
                } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"You have been gived %i levels for the guild %i:%s of the player %i:%s Char:%i:%s", lvl, guild->id, guild->nome, outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome);
                }
                SendMessageGuild(guild->id, "Sua guild %s recebeu %i leveis do player: %s", "Your guild %s received %i levels from the player: %s", guild->nome, lvl, estecliente->chars[estecliente->chara].nome);
            } else {
                if (strcmp(estecliente->lang,"pt_BR")==0) {
                    SendMessage(estecliente,"Este player: %i:%s Char:%i:%s não possui uma guild", outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome);
                } else if (strcmp(estecliente->lang,"en_US")==0) {
                    SendMessage(estecliente,"This Player: %i:%s Char:%i:%s does not have a guild", outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome);
                }
            }
            return true;
         }
         return false;
     } else {
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Este player: %s não existe ou não está logado", player);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"This Player: %s does not exist or is not logged in", player);
        }
        return false;
     }
}

bool Server::GM_A_save(player_base* estecliente, char* player)
{
     player_base* outrocliente = GetPlayer(player);
     if (outrocliente != NULL) {
         if (estecliente->perm > outrocliente->perm) {
            outrocliente->chars[outrocliente->chara].save_map = outrocliente->chars[outrocliente->chara].map;
            outrocliente->chars[outrocliente->chara].save_x = outrocliente->chars[outrocliente->chara].x;
            outrocliente->chars[outrocliente->chara].save_y = outrocliente->chars[outrocliente->chara].y;
            if (strcmp(estecliente->lang,"pt_BR")==0) {
                SendMessage(estecliente,"Você salvou o ponto de respaw padrão do player %i:%s Char:%i:%s como mapa:%i X:%i Y:%i", outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome, outrocliente->chars[outrocliente->chara].map, outrocliente->chars[outrocliente->chara].x, outrocliente->chars[outrocliente->chara].y);
            } else if (strcmp(estecliente->lang,"en_US")==0) {
                SendMessage(estecliente,"You have been saved the default respaw point of the player %i:%s Char:%i:%s to map:%i X:%i Y:%i", outrocliente->id, outrocliente->usuario, outrocliente->chars[outrocliente->chara].id, outrocliente->chars[outrocliente->chara].nome, outrocliente->chars[outrocliente->chara].map, outrocliente->chars[outrocliente->chara].x, outrocliente->chars[outrocliente->chara].y);
            }
            if (strcmp(outrocliente->lang,"pt_BR")==0) {
                SendMessage(outrocliente,"Seu ponto de respaw padrão foi alterado para sua posição atual pelo player: %s", estecliente->chars[estecliente->chara].nome);
            } else if (strcmp(outrocliente->lang,"en_US")==0) {
                SendMessage(outrocliente,"Your default respawn point has been altered to your actual position by the player: %s", estecliente->chars[estecliente->chara].nome);
            }
            return true;
         }
         return false;
     } else {
        if (strcmp(estecliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Este player: %s não existe ou não está logado", player);
        } else if (strcmp(estecliente->lang,"en_US")==0) {
           SendMessage(estecliente,"This Player: %s does not exist or is not logged in", player);
        }
        return false;
     }
}
