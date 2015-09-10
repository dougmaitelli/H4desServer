/* 
 * File:   Item.h
 * Author: DougM
 *
 * Created on 4 de Dezembro de 2010, 19:54
 */

#ifndef ITEM_H
#define	ITEM_H

class Item {
private:
    // General
    unsigned long id;
	char name[20];
	ItemType type;
	unsigned int attack;
	unsigned int defense;
	unsigned int level_required;

	// Bonuses
	unsigned int hp;
	unsigned int mp;
	unsigned int str_req;
	unsigned int intl_req;
	unsigned int dex_req;
	unsigned int agi_req;
	unsigned int str;
	unsigned int intl;
	unsigned int sau;
	unsigned int per;
	unsigned int car;
	unsigned int dex;
	unsigned int agi;
	unsigned int magic;

public:
    Item();
    virtual ~Item();
};

#endif	/* ITEM_H */

