/* 
 * File:   Guild.h
 * Author: Douglas Maitelli
 *
 * Created Dezember, 4 2010, 19:54
 */

#ifndef GUILD_H
#define	GUILD_H

using namespace std;

class Guild {
private:
	//General
    unsigned long id;
    char name[26];
    Player* leader;
    unsigned int lvl;
    unsigned long experience;

    vector<Player*> players;

public:
    Guild();
    virtual ~Guild();

    // General
    unsigned long getId() const;
    const char* getName() const;
    void setName(char*);
    const Player*& getLeader() const;
	void setLeader(const Player*&);
	unsigned int getLvl() const;
	void setLvl(unsigned int) ;
	unsigned long getExperience() const;
	void setExperience(unsigned long);

	vector<Player*> getPlayers() const;
};

#endif	/* GUILD_H */

