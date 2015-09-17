/*
 * File:   Player.cpp
 * Author: DougM
 *
 * Created on 4 de Dezembro de 2010, 19:08
 */

#include "Player.h"

#include "../Server.h"
#include "Character.h"

Player::Player(Server* server) {
    this->server = server;
}

Player::~Player() {
}

Server* Player::getServer() const {
    return server;
}

unsigned long Player::getId() const{
    return id;
}

string Player::getUsername() const {
    return username;
}

unsigned short Player::getPermissionLevel() const {
    return permissionLevel;
}

void Player::setPermissionLevel(unsigned short permissionLevel) {
    this->permissionLevel = permissionLevel;
}

unsigned short Player::getWarnLevel() const {
    return warnLevel;
}

void Player::setWarnLevel(unsigned short warnLevel) {
    this->warnLevel = warnLevel;
}

unsigned char Player::getBan() const {
    return ban;
}

void Player::setBan(unsigned char ban) {
    this->ban = ban;
}

unsigned char Player::getHide() const {
    return hide;
}

void Player::setHide(unsigned char hide) {
    this->hide = hide;
}

Character* Player::getCurrentCharacter() const {
	return currentCharacter;
}

void Player::setCurrentCharacter(Character* character) {
	this->currentCharacter = character;
}

int Player::getSocket() const {
    return socket;
}

const char* Player::getIp() const {
    return &ip[0];
}

const char* Player::getSubnet() const {
    return &subnet[0];
}
