#pragma once
#include "Shy_Skill.h"

class SwordAttack : public Skill
{
public:
	virtual void InitSkill() override
	{
		name = "베기";
		type = SkILLTYPE::ATTACK;	
	}

	void SetValue() override
	{
		value = 5;
	}
};

class ThrowSand : public Skill
{
public:
	virtual void InitSkill() override
	{
		name = "모래뿌리기";
		type = SkILLTYPE::ATTACK;
	}
};

class Head : public Skill
{
public:
	virtual void InitSkill() override
	{
		name = "박치기";
		type = SkILLTYPE::ATTACK;
	}
};

class FireBall : public Skill
{
public:
	void InitSkill()override
	{
		name = "파이어볼";
		type = SkILLTYPE::ATTACK;	
	}
};

class BodyAttack : public Skill
{
public:
	void InitSkill() override
	{
		name = "몸통박치기";
		type = SkILLTYPE::ATTACK;
	}
};

class Punch : public Skill
{
	void InitSkill() override
	{
		name = "막치기";
		type = SkILLTYPE::ATTACK;
	}
};

class Shiled : public Skill
{
public:
	void InitSkill() override
	{
		name = "막기";
		type = SkILLTYPE::SHIELD;
	}
};

class Bandage : public Skill
{
public:
	void InitSkill() override
	{
		name = "붕대감기";
		value = 5 + (rank * 1.45f);
		type = SkILLTYPE::HEAL;
	}
};

class Bite : public Skill
{
	void InitSkill() override
	{
		name = "물기";
		type = SkILLTYPE::ATTACK;
	}
};

class Wave : public Skill
{
	void InitSkill() override
	{
		name = "초음파";
		value = 2;
		type = SkILLTYPE::ATTACK;
	}
};

class Sleeping : public Skill
{
	void InitSkill() override
	{
		name = "잠자기";
		value = 2;
		type = SkILLTYPE::ATTACK;
	}

};


class Fear : public Skill
{
	void InitSkill() override
	{
		name = "공포";
		value = 0;
		type = SkILLTYPE::ATTACK;
	}
};

class Playful : public Skill
{
public:
	void InitSkill() override
	{
		name = "농땡이";
		type = SkILLTYPE::ATTACK;
	}

};

class Idiot : public Skill
{
	void InitSkill() override
	{
		name = "멍때리기";
		type = SkILLTYPE::ATTACK;
	}
};

