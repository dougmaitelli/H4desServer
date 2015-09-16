/*
 * File:   Party.cpp
 * Author: Douglas Maitelli
 *
 * Created on Dezember, 4 2010, 19:54
 */

#include "Party.h"

Party::Party() {
}

Party::~Party() {
}

vector<Player*> Party::getPlayers() const {
	return players;
}

