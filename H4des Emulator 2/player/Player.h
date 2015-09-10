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
    SOCKET socket;
    sockaddr_in client_socket;
    char ip[16];
    char subnet[12];
    Lang lang;
    unsigned int warn;
    unsigned short perm;
    Character* currentCharacter;
    unsigned char ban;
    unsigned char hide;

public:
    Player();
    virtual ~Player();

    SOCKET getSocket() const;
    const Character*& getCurrentCharacter() const;
    void setCurrentCharacter(Character*&);
};

#endif	/* PLAYER_H */

