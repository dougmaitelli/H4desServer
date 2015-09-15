/*
 * File:   Character.cpp
 * Author: DougM
 *
 * Created on 4 de Dezembro de 2010, 19:15
 */

#include "Character.h"

Character::Character() {
}

Character::~Character() {
}
vector<Player*> Character::GetFriends() const {
    return friends;
}
void Character::SetSave_y(float save_y) {
    this->save_y = save_y;
}
float Character::GetSave_y() const {
    return save_y;
}
void Character::SetSave_x(float save_x) {
    this->save_x = save_x;
}
float Character::GetSave_x() const {
    return save_x;
}
void Character::SetSave_map(unsigned short save_map) {
    this->save_map = save_map;
}
unsigned short Character::GetSave_map() const {
    return save_map;
}
void Character::SetY(float y) {
    this->y = y;
}
float Character::GetY() const {
    return y;
}
void Character::SetX(float x) {
    this->x = x;
}
float Character::GetX() const {
    return x;
}
void Character::SetMap(unsigned short map) {
    this->map = map;
}
unsigned short Character::GetMap() const {
    return map;
}
void Character::SetGuild(Guild* guild) {
    this->guild = guild;
}
Guild* Character::GetGuild() const {
    return guild;
}
void Character::SetParty(Party* party) {
    this->party = party;
}
Party* Character::GetParty() const {
    return party;
}
void Character::SetSkill_points(unsigned short skill_points) {
    this->skill_points = skill_points;
}
unsigned short Character::GetSkill_points() const {
    return skill_points;
}
void Character::SetAttribute_points(unsigned short attribute_points) {
    this->attribute_points = attribute_points;
}
unsigned short Character::GetAttribute_points() const {
    return attribute_points;
}
vector<Skill*> Character::GetSkills() const {
    return skills;
}
void Character::SetStamina(unsigned short stamina) {
    this->stamina = stamina;
}
unsigned short Character::GetStamina() const {
    return stamina;
}
void Character::SetMagic(unsigned short magic) {
    this->magic = magic;
}
unsigned short Character::GetMagic() const {
    return magic;
}
void Character::SetAgility(unsigned short agility) {
    this->agility = agility;
}
unsigned short Character::GetAgility() const {
    return agility;
}
void Character::SetDexterity(unsigned short dexterity) {
    this->dexterity = dexterity;
}
unsigned short Character::GetDexterity() const {
    return dexterity;
}
void Character::SetCharisma(unsigned short charisma) {
    this->charisma = charisma;
}
unsigned short Character::GetCharisma() const {
    return charisma;
}
void Character::SetPerception(unsigned short perception) {
    this->perception = perception;
}
unsigned short Character::GetPerception() const {
    return perception;
}
void Character::SetHealth(unsigned short health) {
    this->health = health;
}
unsigned short Character::GetHealth() const {
    return health;
}
void Character::SetWisdom(unsigned short wisdom) {
    this->wisdom = wisdom;
}
unsigned short Character::GetWisdom() const {
    return wisdom;
}
void Character::SetStrength(unsigned short strength) {
    this->strength = strength;
}
unsigned short Character::GetStrength() const {
    return strength;
}
vector<PlayerItem*> Character::GetItems() const {
    return items;
}
void Character::SetRobe(PlayerItem* robe) {
    this->robe = robe;
}
PlayerItem* Character::GetRobe() const {
    return robe;
}
void Character::SetBelt(PlayerItem* belt) {
    this->belt = belt;
}
PlayerItem* Character::GetBelt() const {
    return belt;
}
void Character::SetLegs(PlayerItem* legs) {
    this->legs = legs;
}
PlayerItem* Character::GetLegs() const {
    return legs;
}
void Character::SetFeets(PlayerItem* feets) {
    this->feets = feets;
}
PlayerItem* Character::GetFeets() const {
    return feets;
}
void Character::SetHands(PlayerItem* hands) {
    this->hands = hands;
}
PlayerItem* Character::GetHands() const {
    return hands;
}
void Character::SetArmor(PlayerItem* armor) {
    this->armor = armor;
}
PlayerItem* Character::GetArmor() const {
    return armor;
}
void Character::SetHead(PlayerItem* head) {
    this->head = head;
}
PlayerItem* Character::GetHead() const {
    return head;
}
void Character::SetSecond_weapon(PlayerItem* second_weapon) {
    this->second_weapon = second_weapon;
}
PlayerItem* Character::GetSecond_weapon() const {
    return second_weapon;
}
void Character::SetWeapon(PlayerItem* weapon) {
    this->weapon = weapon;
}
PlayerItem* Character::GetWeapon() const {
    return weapon;
}
void Character::SetProfession(unsigned short profession) {
    this->profession = profession;
}
unsigned short Character::GetProfession() const {
    return profession;
}
void Character::SetRace(unsigned short race) {
    this->race = race;
}
unsigned short Character::GetRace() const {
    return race;
}
void Character::SetNation(unsigned short nation) {
    this->nation = nation;
}
unsigned short Character::GetNation() const {
    return nation;
}
void Character::SetMp_max(unsigned int mp_max) {
    this->mp_max = mp_max;
}
unsigned int Character::GetMp_max() const {
    return mp_max;
}
void Character::SetHp_max(unsigned int hp_max) {
    this->hp_max = hp_max;
}
unsigned int Character::GetHp_max() const {
    return hp_max;
}
void Character::SetMp(unsigned int mp) {
    this->mp = mp;
}
unsigned int Character::GetMp() const {
    return mp;
}
void Character::SetHp(unsigned int hp) {
    this->hp = hp;
}
unsigned int Character::GetHp() const {
    return hp;
}
void Character::SetMoney(unsigned long money) {
    this->money = money;
}
unsigned long Character::GetMoney() const {
    return money;
}
void Character::SetExperience(unsigned long experience) {
    this->experience = experience;
}
unsigned long Character::GetExperience() const {
    return experience;
}
void Character::SetLevel(unsigned short level) {
    this->level = level;
}
unsigned short Character::GetLevel() const {
    return level;
}
void Character::SetSex(Sex sex) {
    this->sex = sex;
}
Sex Character::GetSex() const {
    return sex;
}
void Character::SetName(string name) {
    this->name = name;
}
string Character::GetName() const {
    return name;
}
unsigned long Character::GetId() const {
    return id;
}

