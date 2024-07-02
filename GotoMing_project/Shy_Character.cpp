#include "Shy_Character.h"

Player::Player(int _hp, CHARACTER_STATE _state)
{
	startHp = _hp;
	hp = _hp;
	state = _state;
}

Player::~Player()
{
}

void Player::SetSkill(Skill * _skill, int _num)
{
	_skill->InitSkill();
	for (int i = 0; i < _num; i++)
	{
		skills.push_back(*_skill);
	}
}

Enemy::Enemy(int _hp, CHARACTER_STATE _state)
{
	startHp = _hp;
	hp = _hp;
	state = _state;
}

Enemy::~Enemy()
{
}

void Enemy::SetSkill(Skill * _skill)
{
	_skill->InitSkill();
	_skill->rank = rand() % 2 + 1;
	_skill->SetValue();
	skills.push_back(*_skill);
}

void Enemy::SetData()
{
	if (type == ENEMYTYPE::NONE)
	{
		Skill * skillData;
		type = ENEMYTYPE::BAT;

		skillData = new Bite();
		SetSkill(skillData);
		delete skillData;
		skillData = new Wave();
		SetSkill(skillData);
		delete skillData;
		skillData = new BodyAttack();
		SetSkill(skillData);
		delete skillData;
	}

	
	SetNextAction();
}

void Enemy::SetNextAction()
{
	Skill * skill;
	skill = &skills[rand() % skills.size()];
	actionSkills.push_back(*skill);
}


void Character::UseSkill(Character & _target)
{
	switch (actionSkills[0].type)
	{
	case SkILLTYPE::ATTACK:
		Hit(_target, &actionSkills[0]);
		break;
	}
}

void Character::Hit(Character& _target, Skill * skill)
{
	skill->SetValue();

	Sleep(200);
	int value = -skill->value;
	_target.hp += value;
}
