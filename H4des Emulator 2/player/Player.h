/*
 * File:   Player.h
 * Author: DougM
 *
 * Created on 4 de Dezembro de 2010, 19:08
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include <netinet/in.h>

#include "../Server.h"
#include "Character.h"

class Server;
class Character;

class Player {
private:
    Server* server;

    unsigned long id;
    char user[100];
    unsigned int warn;
    unsigned short perm;
    unsigned char ban;
    unsigned char hide;

    Character* currentCharacter;

public:
    Player(Server* server);
    virtual ~Player();

	int socket;
	sockaddr_in sockeAddr;
	char ip[16];
	char subnet[12];
	bool active;

	Server* getServer() const;

    Character* getCurrentCharacter() const;
    void setCurrentCharacter(Character*);

    int getSocket() const;
    char* getIp() const;
    char* getSubnet() const;
};

#endif	/* PLAYER_H */

