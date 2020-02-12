#include "pch.h"
#include "Character.h"


Skill::Skill(string name, Character * caster)
{
	this->name = name;
	this->caster = caster;
}

bool Skill::onCast()
{
	if (state == State::Ready)
	{
		nextState = State::Casting;
		return true;
	}
	else if (state == State::Phase)
	{
		nextState = State::Casting;
		++phase;
		return true;
	}
	return false;
}

bool Skill::IsCastingProgress()
{
	return state == State::Casting || nextState == State::Casting;
}

void Skill::Update(float deltaTime)
{
	pastTime += deltaTime;

	if (state != nextState)
	{
		state = nextState;
		pastTime = 0.0f;
	}

	SkillUpdate(deltaTime);

	switch (state)
	{
	case State::Ready:
		break;
	case State::Casting:
		if (pastTime > castingTime)
		{
			if (phase < maxPhase)
				nextState = State::Phase;
			else
				nextState = State::Cool;
		}

		break;
	case State::Cancel:
		break;
	case State::Cool:
		phase = 0;
		if (pastTime > coolTime)
			nextState = State::Ready;
		break;
	case State::Phase:
		if (pastTime > phaseTime)
			nextState = State::Cool;
		break;

	}
	prevPastTime = pastTime;
}
