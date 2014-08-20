/* 
 * File:   Guild.h
 * Author: DougM
 *
 * Created on 4 de Dezembro de 2010, 19:54
 */

#ifndef GUILD_H
#define	GUILD_H

class Guild {
public:
    Guild();
    virtual ~Guild();

private:
    unsigned long id;
    char nome[26];
    unsigned long lider;
    unsigned int lvl;
};

#endif	/* GUILD_H */

