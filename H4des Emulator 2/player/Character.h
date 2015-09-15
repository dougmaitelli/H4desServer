/*
 * File:   Character.h
 * Author: Douglas Maitelli
 *
 * Created on Decembro, 4 2010, 19:15
 */

#ifndef CHARACTER_H
#define	CHARACTER_H

#include <string>
#include <vector>

#include "PlayerItem.h"
#include "../assets/Skill.h"
#include "../party/Party.h"
#include "../party/Guild.h"

using namespace std;

class PlayerItem;
class Skill;
class Party;
class Guild;

enum Sex {
    MALE,
    FEMALE
};

class Character {
private:
    // General
    unsigned long id;
    string name;
    Sex sex;
    unsigned short level;
    unsigned long experience;
    unsigned long money;
    unsigned int hp;
    unsigned int mp;
    unsigned int hp_max;
    unsigned int mp_max;

    unsigned short nation;
    unsigned short race;
    unsigned short profession;

    // Items
	vector<PlayerItem*> items;

    // Equipments
    PlayerItem* weapon;
    PlayerItem* second_weapon;
    PlayerItem* head;
    PlayerItem* armor;
    PlayerItem* hands;
    PlayerItem* feets;
    PlayerItem* legs;
    PlayerItem* belt;
    PlayerItem* robe;

    // Attributes
    unsigned short strength;
    unsigned short wisdom;
    unsigned short health;
    unsigned short perception;
    unsigned short charisma;
    unsigned short dexterity;
    unsigned short agility;
    unsigned short magic;
    unsigned short stamina;

    // Skills
    vector<Skill*> skills;

    // Points
    unsigned short attribute_points;
    unsigned short skill_points;

    // Social
    Party* party;
    Guild* guild;

    // Position
    unsigned short map;
    float x;
    float y;

    // Save Point
    unsigned short save_map;
    float save_x;
    float save_y;

    // Friends
    vector<Player*> friends;

public:
    Character();
    virtual ~Character();

    // General
    unsigned long GetId() const;
    string GetName() const;
    void SetName(string);
    Sex GetSex() const;
    void SetSex(Sex sex);
    unsigned short GetLevel() const;
    void SetLevel(unsigned short level);
    unsigned long GetExperience() const;
    void SetExperience(unsigned long experience);
    unsigned long GetMoney() const;
    void SetMoney(unsigned long money);
    unsigned int GetHp() const;
    void SetHp(unsigned int hp);
    unsigned int GetMp() const;
    void SetMp(unsigned int mp);
    unsigned int GetHp_max() const;
    void SetHp_max(unsigned int hp_max);
    unsigned int GetMp_max() const;
    void SetMp_max(unsigned int mp_max);

    unsigned short GetNation() const;
    void SetNation(unsigned short nation);
    unsigned short GetRace() const;
    void SetRace(unsigned short race);
    unsigned short GetProfession() const;
    void SetProfession(unsigned short profession);

    // Items
	vector<PlayerItem*> GetItems() const;

    // Equipments
    PlayerItem* GetWeapon() const;
    void SetWeapon(PlayerItem* weapon);
    PlayerItem* GetSecond_weapon() const;
    void SetSecond_weapon(PlayerItem* second_weapon);
    PlayerItem* GetHead() const;
    void SetHead(PlayerItem* head);
    PlayerItem* GetArmor() const;
    void SetArmor(PlayerItem* armor);
    PlayerItem* GetHands() const;
    void SetHands(PlayerItem* hands);
    PlayerItem* GetFeets() const;
    void SetFeets(PlayerItem* feets);
    PlayerItem* GetLegs() const;
    void SetLegs(PlayerItem* legs);
    PlayerItem* GetBelt() const;
    void SetBelt(PlayerItem* belt);
    PlayerItem* GetRobe() const;
    void SetRobe(PlayerItem* robe);

    // Attributes
    unsigned short GetStrength() const;
    void SetStrength(unsigned short strength);
    unsigned short GetWisdom() const;
    void SetWisdom(unsigned short wisdom);
    unsigned short GetHealth() const;
    void SetHealth(unsigned short health);
    unsigned short GetPerception() const;
    void SetPerception(unsigned short perception);
    unsigned short GetCharisma() const;
    void SetCharisma(unsigned short charisma);
    unsigned short GetDexterity() const;
    void SetDexterity(unsigned short dexterity);
    unsigned short GetAgility() const;
    void SetAgility(unsigned short agility);
    unsigned short GetMagic() const;
    void SetMagic(unsigned short magic);
    unsigned short GetStamina() const;
    void SetStamina(unsigned short stamina);

    // Skills
    vector<Skill*> GetSkills() const;

    // Points
    unsigned short GetAttribute_points() const;
    void SetAttribute_points(unsigned short attribute_points);
    unsigned short GetSkill_points() const;
    void SetSkill_points(unsigned short skill_points);

    // Social
    Party* GetParty() const;
    void SetParty(Party* party);
    Guild* GetGuild() const;
    void SetGuild(Guild* guild);

    // Position
    unsigned short GetMap() const;
    void SetMap(unsigned short map);
    float GetX() const;
    void SetX(float x);
    float GetY() const;
    void SetY(float y);

    // Save Point
    unsigned short GetSave_map() const;
    void SetSave_map(unsigned short save_map);
    float GetSave_x() const;
    void SetSave_x(float save_x);
    float GetSave_y() const;
    void SetSave_y(float save_y);

    // Friends
    vector<Player*> GetFriends() const;
};

#endif	/* CHARACTER_H */

