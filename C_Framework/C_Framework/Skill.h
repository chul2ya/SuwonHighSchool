#pragma once

class Character;

class Skill
{
public:
	enum State
	{
		Ready,
		Casting,
		Cancel,
		Cool,
		Phase
	};

	string name = "";
	State state = State::Ready;
	State nextState = State::Ready;
	float pastTime = 0.0f;
	float prevPastTime = 0.0f;
	float phaseTime = 0.5f;
	float castingTime = 1.0f;
	float coolTime = 0.0f;
	Character* caster;

	int phase = 0;
	int maxPhase = 2;

	Skill(string name, Character * caster);	

	bool onCast();

	bool IsCastingProgress();

	void Update(float deltaTime);

	virtual void SkillUpdate(float deltaTime) = 0;
};

