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
    unsigned long gold;
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
    void SetSex(Sex);
    unsigned short GetLevel() const;
    void SetLevel(unsigned short);
    unsigned long GetExperience() const;
    void SetExperience(unsigned long);
    unsigned long GetGold() const;
    void SetGold(unsigned long);
    unsigned int GetHp() const;
    void SetHp(unsigned int);
    unsigned int GetMp() const;
    void SetMp(unsigned int);
    unsigned int GetHp_max() const;
    void SetHp_max(unsigned int);
    unsigned int GetMp_max() const;
    void SetMp_max(unsigned int);

    unsigned short GetNation() const;
    void SetNation(unsigned short);
    unsigned short GetRace() const;
    void SetRace(unsigned short);
    unsigned short GetProfession() const;
    void SetProfession(unsigned short);

    // Items
	vector<PlayerItem*> GetItems() const;

    // Equipments
    PlayerItem* GetWeapon() const;
    void SetWeapon(PlayerItem*);
    PlayerItem* GetSecond_weapon() const;
    void SetSecond_weapon(PlayerItem*);
    PlayerItem* GetHead() const;
    void SetHead(PlayerItem*);
    PlayerItem* GetArmor() const;
    void SetArmor(PlayerItem*);
    PlayerItem* GetHands() const;
    void SetHands(PlayerItem*);
    PlayerItem* GetFeets() const;
    void SetFeets(PlayerItem*);
    PlayerItem* GetLegs() const;
    void SetLegs(PlayerItem*);
    PlayerItem* GetBelt() const;
    void SetBelt(PlayerItem*);
    PlayerItem* GetRobe() const;
    void SetRobe(PlayerItem*);

    // Attributes
    unsigned short GetStrength() const;
    void SetStrength(unsigned short);
    unsigned short GetWisdom() const;
    void SetWisdom(unsigned short);
    unsigned short GetHealth() const;
    void SetHealth(unsigned short);
    unsigned short GetPerception() const;
    void SetPerception(unsigned short);
    unsigned short GetCharisma() const;
    void SetCharisma(unsigned short);
    unsigned short GetDexterity() const;
    void SetDexterity(unsigned short);
    unsigned short GetAgility() const;
    void SetAgility(unsigned short);
    unsigned short GetMagic() const;
    void SetMagic(unsigned short);
    unsigned short GetStamina() const;
    void SetStamina(unsigned short);

    // Skills
    vector<Skill*> GetSkills() const;

    // Points
    unsigned short GetAttribute_points() const;
    void SetAttribute_points(unsigned short);
    unsigned short GetSkill_points() const;
    void SetSkill_points(unsigned short);

    // Social
    Party* GetParty() const;
    void SetParty(Party*);
    Guild* GetGuild() const;
    void SetGuild(Guild*);

    // Position
    unsigned short GetMap() const;
    void SetMap(unsigned short);
    float GetX() const;
    void SetX(float);
    float GetY() const;
    void SetY(float);

    // Save Point
    unsigned short GetSave_map() const;
    void SetSave_map(unsigned short);
    float GetSave_x() const;
    void SetSave_x(float);
    float GetSave_y() const;
    void SetSave_y(float);

    // Friends
    vector<Player*> GetFriends() const;
};

#endif	/* CHARACTER_H */

