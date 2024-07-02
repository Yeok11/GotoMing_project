#pragma once
#include "Shy_Define.h"

enum class SkILLTYPE
{
	NONE,
	ATTACK,
	SHIELD,
	HEAL
};

class Skill
{
public:
	std::string name;
	SkILLTYPE type = SkILLTYPE::NONE;
	int value;
	int rank = 1;

	virtual void InitSkill()
	{
	}

	virtual void SetValue()
	{
		value = 5 + (rank / 2) * 1.22f;
	}
};