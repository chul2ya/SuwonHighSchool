#pragma once


class Kick : public Skill
{
public:
	Kick(Character* caster);

	virtual void SkillUpdate(float deltaTime) override;
};