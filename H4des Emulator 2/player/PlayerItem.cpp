/*
 * File:   PlayerItem.cpp
 * Author: Douglas Maitelli
 *
 * Created on September, 9 2015, 19:44
 */

#include "PlayerItem.h"

#include "../assets/Item.h"

PlayerItem::PlayerItem(Item* item) {
	this->item = item;
}

PlayerItem::~PlayerItem() {
}

Item* PlayerItem::GetItem() const {
	return item;
}

