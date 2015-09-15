/*
 * File:   Party.h
 * Author: Douglas Maitelli
 *
 * Created on December, 4 2010, 19:54
 */

#ifndef PARTY_H
#define	PARTY_H

using namespace std;

#include <vector>

#include "../player/Player.h"

class Player;

class Party {
private:
    vector<Player*> players;

public:
    Party();
    virtual ~Party();

    vector<Player*> getPlayers() const;
};

#endif	/* PARTY_H */

