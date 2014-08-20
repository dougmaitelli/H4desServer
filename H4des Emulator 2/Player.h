/* 
 * File:   Player.h
 * Author: DougM
 *
 * Created on 4 de Dezembro de 2010, 19:08
 */

#ifndef PLAYER_H
#define	PLAYER_H

class Player {
public:
    Player();
    virtual ~Player();
private:
    unsigned long id;
    char user[100];
    SOCKET socket;
    sockaddr_in client_socket;
    char ip[16];
    char subnet[12];
    Lang lang;
    unsigned int warn;
    unsigned short perm;
    unsigned char character;
    unsigned char ban;
    unsigned char hide;
};

#endif	/* PLAYER_H */

