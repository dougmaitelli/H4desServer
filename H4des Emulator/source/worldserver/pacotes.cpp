#include <conio.h>
#include <windows.h>
#include <cstdio>
#include <iostream>

#include "../comum/log.h"
#include "worldserver.h"

using namespace std;

void Server::PacoteExec(player_base* estecliente, char* buffer)
{
     Transfer_Data* data = new (nothrow)Transfer_Data;
     data = (Transfer_Data*)buffer;
     if (estecliente->logado && estecliente->charsel) {
        switch(data->comando) {
            case 1:
                PlayerMenssagem(estecliente, data->char1);
                break;
            case 2:
                //Login
                break;
            case 3:
                //Char
                break;
            default:
                //
                break;
        }
     } else if (estecliente->logado && !estecliente->charsel) {
        switch(data->comando) {
            case 1:
                //Menssagem
                break;
            case 2:
                //Login
                break;
            case 3:
                CharSelect(estecliente, data->int1);
                break;
            default:
                //
                break;
        }
     } else {
        switch(data->comando) {
            case 1:
                //Menssagem
                break;
            case 2:
                Login(estecliente, data->char1, data->char2);
                break;
            case 3:
                //Char
                break;
            default:
                //
                break;
        }
     }
}
