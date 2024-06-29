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

class FireBall : public Skill
{
public:
	void InitSkill()override
	{
		name = "파이어볼";
		type = SkILLTYPE::ATTACK;	
	}

	void SetValue() override	
	{
		value = 3 * (rank * 2.17f);
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

	void SetValue() override
	{
		value = 5 + (rank * 1.45f);
	}
};

class Punch : public Skill
{
	void InitSkill() override
	{
		name = "막치기";
		type = SkILLTYPE::ATTACK;
	}

	void SetValue() override
	{
		value = 5 + (rank * 1.45f);
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

	void SetValue() override
	{
		value = 5 + (rank * 1.45f);
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

	void SetValue() override
	{
		value = 3 * (rank * 2.17f);
	}
};

class Bite : public Skill
{
	void InitSkill() override
	{
		name = "물기";
		value = 5 + (rank * 1.45f);
		type = SkILLTYPE::ATTACK;
	}

	void SetValue() override
	{
		value = 3 * (rank * 2.17f);
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

	void SetValue() override
	{
		value = 3 * (rank * 2.17f);
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

	void SetValue() override
	{
		value = 3 * (rank * 2.17f);
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

	void SetValue() override
	{
		value = 3 * (rank * 2.17f);
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

	void SetValue() override
	{
		value = 3 * (rank * 2.17f);
	}
};

class Idiot : public Skill
{
	void InitSkill() override
	{
		name = "멍때리기";
		type = SkILLTYPE::ATTACK;
	}

	void SetValue() override
	{
		value = 3 * (rank * 2.17f);
	}
};

