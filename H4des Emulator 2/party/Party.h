/* 
 * File:   Party.h
 * Author: Douglas Maitelli
 *
 * Created on Dezember, 4 2010, 19:54
 */

#ifndef PARTY_H
#define	PARTY_H

using namespace std;

class Party {
private:
    vector<Player*> players;

public:
    Party();
    virtual ~Party();

    vector<Player*> getPlayers() const;
};

#endif	/* PARTY_H */

