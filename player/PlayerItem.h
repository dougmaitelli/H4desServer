/*
 * File:   PlayerItem.h
 * Author: Douglas Maitelli
 *
 * Created on September, 9 2015, 19:44
 */

#ifndef PLAYERITEM_H
#define	PLAYERITEM_H

class Item;

class PlayerItem {
private:
    unsigned long id;
    Item* item;

public:
	PlayerItem(Item*);
    virtual ~PlayerItem();

    // General
    Item* GetItem() const;
};

#endif	/* PLAYERITEM_H */

