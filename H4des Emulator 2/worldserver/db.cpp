#include <conio.h>
#include <windows.h>
#include <cstdio>
#include <iostream>

#include "../commom/log.h"
#include "worldserver.h"

using namespace std;

bool Server::Login(player_base* estecliente, char* usuario, char* senha)
{
     MYSQL_RES* res;
     MYSQL_ROW row;
     player_base* outrocliente = GetUser(usuario);
     if (outrocliente == NULL) {
        if (AddSlashes(usuario) or AddSlashes(senha)) {
           Log(HACK,false,"Tentativa hacker no ip: %s!", estecliente->ip);
        }
        res = QueryResult("SELECT * FROM users WHERE usuario ='%s' AND senha =MD5('%s')", usuario, senha);
        if (mysql_num_rows(res) > 0) {
           row = mysql_fetch_row(res);
           mysql_free_result(res);
           estecliente->id = atoi(row[0]);
           sprintf(estecliente->usuario, row[1]);
           estecliente->perm = atoi(row[3]);
           estecliente->warn = atoi(row[4]);
           estecliente->ban = atoi(row[5]);
           sprintf(estecliente->lang, row[6]);

           if (!QueryDB("UPDATE users SET ip ='%s' WHERE id ='%i'", estecliente->ip, estecliente->id)) {
              Log(ERRO,false,"N�o foi poss�vel atualizar o ip do player: %i:%s para: %s", estecliente->id, estecliente->usuario, estecliente->ip);
           }

           if (!QueryDB("UPDATE users SET online ='1' WHERE id ='%i'", estecliente->id)) {
              Log(ERRO,false,"N�o foi poss�vel atualizar o status do player: %i:%s para online", estecliente->id, estecliente->usuario);
           }

           if (estecliente->ban == 1) {
              if (strcmp(estecliente->lang,"pt_BR")==0) {
                 SendMessage(estecliente,"Esta conta est� banida");
              } else if (strcmp(estecliente->lang,"en_US")==0) {
                 SendMessage(estecliente,"This account has been banned");
              }
              DesconectaPlayer(estecliente);
              return false;
           }

           res = QueryResult("SELECT * FROM chars WHERE user ='%i'", estecliente->id);

           while (row = mysql_fetch_row(res)) {
               estecliente->chars[atoi(row[2])-1].id = atoi(row[0]);
               sprintf(estecliente->chars[atoi(row[2])-1].nome, row[3]);
               estecliente->chars[atoi(row[2])-1].povo = atoi(row[4]);
               estecliente->chars[atoi(row[2])-1].raca = atoi(row[5]);
               estecliente->chars[atoi(row[2])-1].profissao = atoi(row[6]);
               estecliente->chars[atoi(row[2])-1].sexo = atoi(row[7]);
               estecliente->chars[atoi(row[2])-1].arma = atoi(row[8]);
               estecliente->chars[atoi(row[2])-1].esq = atoi(row[9]);
               estecliente->chars[atoi(row[2])-1].cabeca = atoi(row[10]);
               estecliente->chars[atoi(row[2])-1].armadura = atoi(row[11]);
               estecliente->chars[atoi(row[2])-1].luva = atoi(row[12]);
               estecliente->chars[atoi(row[2])-1].bota = atoi(row[13]);
               estecliente->chars[atoi(row[2])-1].calca = atoi(row[14]);
               estecliente->chars[atoi(row[2])-1].cintura = atoi(row[15]);
               estecliente->chars[atoi(row[2])-1].capa = atoi(row[16]);
               estecliente->chars[atoi(row[2])-1].lvl = atoi(row[17]);
               estecliente->chars[atoi(row[2])-1].exp = atoi(row[18]);
               estecliente->chars[atoi(row[2])-1].gold = atoi(row[19]);
               estecliente->chars[atoi(row[2])-1].hp = atoi(row[20]);
               estecliente->chars[atoi(row[2])-1].mp = atoi(row[21]);
               estecliente->chars[atoi(row[2])-1].hp_max = atoi(row[22]);
               estecliente->chars[atoi(row[2])-1].mp_max = atoi(row[23]);
               estecliente->chars[atoi(row[2])-1].str = atoi(row[24]);
               estecliente->chars[atoi(row[2])-1].intl = atoi(row[25]);
               estecliente->chars[atoi(row[2])-1].sau = atoi(row[26]);
               estecliente->chars[atoi(row[2])-1].per = atoi(row[27]);
               estecliente->chars[atoi(row[2])-1].car = atoi(row[28]);
               estecliente->chars[atoi(row[2])-1].dex = atoi(row[29]);
               estecliente->chars[atoi(row[2])-1].agi = atoi(row[30]);
               estecliente->chars[atoi(row[2])-1].magia = atoi(row[31]);
               estecliente->chars[atoi(row[2])-1].sta = atoi(row[32]);
               estecliente->chars[atoi(row[2])-1].sp = atoi(row[33]);
               estecliente->chars[atoi(row[2])-1].skp = atoi(row[34]);
               estecliente->chars[atoi(row[2])-1].guild = atoi(row[35]);
               estecliente->chars[atoi(row[2])-1].map = atoi(row[36]);
               estecliente->chars[atoi(row[2])-1].x = atoi(row[37]);
               estecliente->chars[atoi(row[2])-1].y = atoi(row[38]);
               estecliente->chars[atoi(row[2])-1].save_map = atoi(row[39]);
               estecliente->chars[atoi(row[2])-1].save_x = atoi(row[40]);
               estecliente->chars[atoi(row[2])-1].save_y = atoi(row[41]);
           }

           mysql_free_result(res);

           estecliente->charsel = false;
           estecliente->logado = true;

           if (strcmp(estecliente->lang,"pt_BR")==0) {
              SendMessage(estecliente,"Voc� foi logado com sucesso com a conta: %i:%s no server %s!", estecliente->id, estecliente->usuario, SERVER_NAME);
           } else if (strcmp(estecliente->lang,"en_US")==0) {
              SendMessage(estecliente,"You have been logged in with the account: %i:%s in %s server!", estecliente->id, estecliente->usuario, SERVER_NAME);
           }
           Log(CLIENT,false,"[%i]Cliente logou como %i: %s!", estecliente->sock, estecliente->id, estecliente->usuario);
           return true;
        } else {
           SendMessage(estecliente, "Esta conta n�o existe");
           DesconectaPlayer(estecliente);
           return false;
        }
     } else {
        if (strcmp(outrocliente->lang,"pt_BR")==0) {
           SendMessage(estecliente,"Esta conta j� est� logada");
        } else if (strcmp(outrocliente->lang,"en_US")==0) {
           SendMessage(estecliente,"This account is already logged in");
        }
        DesconectaPlayer(estecliente);
        return false;
     }
}

bool Server::CharSelect(player_base* estecliente, int charid)
{
     if (charid < MAX_PLAYER_CHARS && charid > 0) {
        estecliente->chara = charid-1;
        estecliente->charsel = true;
        return true;
     } else {
        return false;
     }
}