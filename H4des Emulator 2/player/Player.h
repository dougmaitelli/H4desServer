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
    string username;
    unsigned short permissionLevel;
    unsigned short warnLevel;
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

    unsigned long getId() const;
    string getUsername() const;
	unsigned short getPermissionLevel() const;
	void setPermissionLevel(unsigned short);
	unsigned short getWarnLevel() const;
	void setWarnLevel(unsigned short);
	unsigned char getBan() const;
	void setBan(unsigned char);
	unsigned char getHide() const;
	void setHide(unsigned char);

    Character* getCurrentCharacter() const;
    void setCurrentCharacter(Character*);

    int getSocket() const;
    char* getIp() const;
    char* getSubnet() const;
};

#endif	/* PLAYER_H */

