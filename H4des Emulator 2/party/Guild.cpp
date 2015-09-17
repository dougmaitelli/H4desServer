/*
 * File:   Guild.cpp
 * Author: Douglas Maitelli
 *
 * Created on December, 4 2010, 19:54
 */

#include "Guild.h"

#include "../player/Player.h"

Guild::Guild() {
}

Guild::~Guild() {
}

unsigned long Guild::getId() const {
	return id;
}

const string Guild::getName() const {
	return name;
}

void Guild::setName(string name) {
	this->name = name;
}

Player* Guild::getLeader() const {
	return leader;
}

void Guild::setLeader(Player* leader) {
	this->leader = leader;
}

unsigned int Guild::getLvl() const {
	return lvl;
}

void Guild::setLvl(unsigned int lvl) {
	this->lvl = lvl;
}

unsigned long Guild::getExperience() const {
	return experience;
}

void Guild::setExperience(unsigned long experience) {
	this->experience = experience;
}

vector<Player*> Guild::getPlayers() const {
	return players;
}
