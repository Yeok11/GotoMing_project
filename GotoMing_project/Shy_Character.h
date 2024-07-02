#pragma once
#include "SkillsList.h"
#include "02_HGameLogic.h"

class Character
{
protected:
	int startHp = 0;
	
	CHARACTER_STATE state = CHARACTER_STATE::WAIT;

public:
	int hp = 0;

	vector<Skill> skills = vector<Skill>();
	vector<Skill> actionSkills = vector<Skill>();

	inline CHARACTER_STATE CheckState() { return state; }
	void ChangeState(CHARACTER_STATE _state)
	{
		state = _state;
	}

	void UseSkill(Character & _target);
	void Hit(Character& _target, Skill * skill);

	string ShowHp()
	{
		return std::to_string(hp) + " / " + std::to_string(startHp);
	}
};

class Player : public Character
{
public:
	_targetplayer pos = {};
	Player() = default;
	Player(int _hp, CHARACTER_STATE _state);
	~Player();

	void SetSkill(Skill * _skill, int _num = 1);
	
	int skillLimit = 3;
};

enum class ENEMYTYPE
{
	NONE,
	BAT,
	SPIDER,
	SNAKE,
	SCULTURE
};

class Enemy : public Character
{
public:
	ENEMYTYPE type = ENEMYTYPE::NONE;

	Enemy() = default;
	Enemy(int _hp, CHARACTER_STATE _state);
	~Enemy();

	void SetSkill(Skill * _skill);
	void SetData();
	void SetNextAction();
};


