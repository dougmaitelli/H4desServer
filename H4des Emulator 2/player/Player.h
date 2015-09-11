/* 
 * File:   Player.h
 * Author: DougM
 *
 * Created on 4 de Dezembro de 2010, 19:08
 */

#ifndef PLAYER_H
#define	PLAYER_H

class Player {
private:
    unsigned long id;
    char user[100];
    Lang lang;
    unsigned int warn;
    unsigned short perm;
    unsigned char ban;
    unsigned char hide;

    Character* currentCharacter;

public:
    Player();
    virtual ~Player();

	SOCKET socket;
	sockaddr_in sockeAddr;
	char ip[16];
	char subnet[12];
	bool active;

    const Character*& getCurrentCharacter() const;
    void setCurrentCharacter(Character*&);
    
    SOCKET getSocket() const;
    char* getIp() const;
    char* getSubnet() const;
};

#endif	/* PLAYER_H */

