/*
 * File:   ClientThread.h
 * Author: DougM
 *
 * Created on 4 de Dezembro de 2010, 19:08
 */

#ifndef CLIENTTHREAD_H
#define	CLIENTTHREAD_H

#include "player/Player.h"

class Player;

class ClientThread {
public:
    ClientThread(Player* player);
    virtual ~ClientThread();
private:
    Player* player;
};

#endif	/* CLIENTTHREAD_H */

