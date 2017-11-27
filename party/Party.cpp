/*
 * File:   Party.cpp
 * Author: Douglas Maitelli
 *
 * Created on December, 4 2010, 19:54
 */

#include "Party.h"

#include "../player/Player.h"

Party::Party() {
}

Party::~Party() {
}

vector<Player*> Party::getPlayers() const {
	return players;
}

