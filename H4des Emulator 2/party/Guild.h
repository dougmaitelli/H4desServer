/*
 * File:   Guild.h
 * Author: Douglas Maitelli
 *
 * Created Dezember, 4 2010, 19:54
 */

#ifndef GUILD_H
#define	GUILD_H

#include <string>
#include <vector>

#include "../player/Player.h"

using namespace std;

class Player;

class Guild {
private:
	//General
    unsigned long id;
    string name;
    Player* leader;
    unsigned int lvl;
    unsigned long experience;

    vector<Player*> players;

public:
    Guild();
    virtual ~Guild();

    // General
    unsigned long getId() const;
    const string getName() const;
    void setName(string);
    Player* getLeader() const;
	void setLeader(Player*);
	unsigned int getLvl() const;
	void setLvl(unsigned int) ;
	unsigned long getExperience() const;
	void setExperience(unsigned long);

	vector<Player*> getPlayers() const;
};

#endif	/* GUILD_H */

