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

void Enemy::SetSkill(Skill _skill)
{
	_skill.SetValue();
	skills.push_back(_skill);
}

void Enemy::SetData()
{
	if (type == ENEMYTYPE::NONE)
	{
		Skill skillData;
		switch (rand() % 3)
		{
		case 0:
		{
			type = ENEMYTYPE::BAT;

			skillData = Bite();
			SetSkill(skillData);
			skillData = Wave();
			SetSkill(skillData);
			skillData = Sleeping();
			SetSkill(skillData);
			break;
		}

		case 1:
			type = ENEMYTYPE::SNAKE;

			skillData = Bite();
			SetSkill(skillData);
			skillData = Wave();
			SetSkill(skillData);
			skillData = Sleeping();
			SetSkill(skillData);
			break;

		case 2:
			type = ENEMYTYPE::SPIDER;

			type = ENEMYTYPE::BAT;
			skillData = Bite();
			SetSkill(skillData);
			skillData = Wave();
			SetSkill(skillData);
			skillData = Sleeping();
			SetSkill(skillData);
			break;
		}
	}

	
	SetNextAction();
}

void Enemy::SetNextAction()
{
	Skill skill;
	skill = skills[rand() % skills.size()];
	actionSkills.push_back(skill);
}

void HitEnemy()
{

}

void Character::UseSkill(Character & _target)
{
	switch (actionSkills[0].type)
	{
	case SkILLTYPE::ATTACK:
		Hit(_target, actionSkills[0]);
		break;
	}
}

void Character::Hit(Character& _target, Skill skill)
{
	skill.SetValue();
	int value = skill.value;
	if (skill.type == SkILLTYPE::ATTACK)
	{
		value *= -1;
	}
	_target.hp += value;
}

void Character::Prevent()
{
}

