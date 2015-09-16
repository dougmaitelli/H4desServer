/*
 * File:   Player.cpp
 * Author: DougM
 *
 * Created on 4 de Dezembro de 2010, 19:08
 */

#include "Player.h"

Player::Player(Server* server) {
    this->server = server;
}

Player::~Player() {
}

//TODO: Add Mising Getters and Setters

Server* Player::getServer() const {
    return server;
}

Character* Player::getCurrentCharacter() const {
	return currentCharacter;
}

void Player::setCurrentCharacter(Character* character) {
	this->currentCharacter = character;
}
