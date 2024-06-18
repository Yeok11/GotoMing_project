#pragma once
#include "Shy_Define.h"

enum class CHARACTERTYPE 
{
	NULLTYPE,
	PLAYER,
	ENEMY,
};

class Character
{
public:
	Character();
	~Character();

private:
	int hp = 0;
	int speed = 0;
	vector<Skill> skills;

	CHARACTERTYPE type = CHARACTERTYPE::NULLTYPE;
};

class Player : public Character
{
	Player();


};