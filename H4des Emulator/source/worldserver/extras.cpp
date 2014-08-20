#include <conio.h>
#include <windows.h>
#include <cstdio>
#include <iostream>

#include "../comum/log.h"
#include "worldserver.h"

using namespace std;

player_base* Server::GetUser(char* nome)
{
    for (UINT i=0;i<Players.size();i++) {
        player_base* estecliente = Players.at(i);
        if (estecliente->logado) {
            if (strcasecmp(estecliente->usuario,nome) == 0) {
                return estecliente;
            }
        }
    }
    return NULL;
}

player_base* Server::GetPlayer(char* nome)
{
    for (UINT i=0;i<Players.size();i++) {
        player_base* estecliente = Players.at(i);
        if (estecliente->charsel) {
            if ((strcasecmp(estecliente->usuario,nome) == 0) || (strcasecmp(estecliente->chars[estecliente->chara].nome,nome) == 0)) {
                return estecliente;
            }
        }
    }
    return NULL;
}

player_base* Server::GetPlayerDB(char* nome)
{
    MYSQL_RES* res;
    MYSQL_ROW row;
    player_base* estecliente = new (nothrow)player_base;
    AddSlashes(nome);
    res = QueryResult("SELECT * FROM users WHERE usuario ='%s'", nome);
    if (mysql_num_rows(res) <= 0) {
        mysql_free_result(res);
        res = QueryResult("SELECT * FROM chars WHERE nome ='%s'", nome);
        if (mysql_num_rows(res) > 0) {
            row = mysql_fetch_row(res);
            mysql_free_result(res);
            res = QueryResult("SELECT * FROM users WHERE id ='%i'", atoi(row[1]));
        }
    }
    if (mysql_num_rows(res) > 0) {
        row = mysql_fetch_row(res);
        mysql_free_result(res);
        estecliente->id = atoi(row[0]);
        sprintf(estecliente->usuario, row[1]);
        estecliente->perm = atoi(row[3]);
        estecliente->warn = atoi(row[4]);
        estecliente->ban = atoi(row[5]);
        sprintf(estecliente->lang, row[6]);

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

        return estecliente;
    }
    return NULL;
}

player_base* Server::GetPlayerId(unsigned long id)
{
    for (UINT i=0;i<Players.size();i++) {
        player_base* estecliente = Players.at(i);
        if (estecliente->charsel) {
            if ((estecliente->id || estecliente->chars[estecliente->chara].id) == id) {
                return estecliente;
            }
        }
    }
    return NULL;
}

guilds_base* Server::GetGuild(char* nome)
{
    for (UINT i=0;i<Guilds.size();i++) {
        guilds_base* guild = Guilds.at(i);
        if (strcasecmp(guild->nome, nome)==0) {
            return guild;
        }
    }
    return NULL;
}

guilds_base* Server::GetGuildId(unsigned long id)
{
    for (UINT i=0;i<Guilds.size();i++) {
        guilds_base* guild = Guilds.at(i);
        if (guild->id == id) {
            return guild;
        }
    }
    return NULL;
}

//------------------------------------------------------------------------------

void Server::SalvaPlayer(player_base* estecliente)
{
    QueryDB("UPDATE users SET warn='%i', ban='%i', lang='%s' WHERE id ='%i'", estecliente->warn, estecliente->ban, estecliente->lang, estecliente->id);
    //QueryDB("UPDATE chars SET povo='%i', profissao='%i', raca='%i', arma='%i', esq='%i', cabeca='%i', armadura='%i', luva='%i', bota='%i', calca='%i', cintura='%i', capa='%i', lvl='%i', exp='%i', gold='%i', hp='%i', mp='%i', hp_max='%i', mp_max='%i', sau='%i', str='%i', per='%i', dex='%i', agi='%i', magia='%i', sp='%i', skp='%i', guild='%i', map='%i', x='%i', y='%i' WHERE id ='%i'", estecliente->chars[estecliente->chara].povo, estecliente->chars[estecliente->chara].profissao, estecliente->chars[estecliente->chara].raca, estecliente->chars[estecliente->chara].arma, estecliente->chars[estecliente->chara].esq, estecliente->chars[estecliente->chara].cabeca, estecliente->chars[estecliente->chara].armadura, estecliente->chars[estecliente->chara].luva, estecliente->chars[estecliente->chara].bota, estecliente->chars[estecliente->chara].calca, estecliente->chars[estecliente->chara].cintura, estecliente->chars[estecliente->chara].capa, estecliente->chars[estecliente->chara].lvl, estecliente->chars[estecliente->chara].exp, estecliente->chars[estecliente->chara].gold, estecliente->chars[estecliente->chara].hp, estecliente->chars[estecliente->chara].mp, estecliente->chars[estecliente->chara].hp_max, estecliente->chars[estecliente->chara].mp_max, estecliente->chars[estecliente->chara].sau, estecliente->chars[estecliente->chara].str, estecliente->chars[estecliente->chara].per, estecliente->chars[estecliente->chara].dex, estecliente->chars[estecliente->chara].agi, estecliente->chars[estecliente->chara].magia, estecliente->chars[estecliente->chara].sp, estecliente->chars[estecliente->chara].skp, estecliente->chars[estecliente->chara].guild, estecliente->chars[estecliente->chara].map, estecliente->chars[estecliente->chara].x, estecliente->chars[estecliente->chara].y, estecliente->chars[estecliente->chara].id);
}

//------------------------------------------------------------------------------

bool Server::AddSlashes(char* str)
{
    char str2[255];
    unsigned int i = 0;
    int slashes = 0;
    bool hack = false;
    for ( ; i < strlen(str); i++) {
        if ((str[i] == '\\') or (str[i] == '"') or (str[i] == '\'')) {
            str2[i + slashes] = '\\';
            slashes++;
            hack = true;
        }
        str2[i + slashes] = str[i];
    }
    str2[i + slashes] = '\0';
    sprintf(str, str2);
    return hack;
}

void Server::CortaStr(char* str, int pos)
{
    for (unsigned int i = 0; i < strlen(str); i++) {
        str[i] = str[i + pos];
    }
}

bool Server::TrimStr(char* str)
{
    for (unsigned int i = 0; i < strlen(str); i++) {
        if (str[i] != ' ') {
            return true;
        }
    }
    return false;
}
