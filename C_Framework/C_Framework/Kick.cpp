#include "pch.h"
#include "Scene.h"
#include "Character.h"

Kick::Kick(Character * caster) : Skill("kick", caster)
{
	phaseTime = 0.5f;
	castingTime = 0.3f;
	maxPhase = 2;
	
}

void Kick::SkillUpdate(float deltaTime)
{
	if (state != State::Casting)
		return;

	if (prevPastTime < 0.15f && pastTime >= 0.15f)
	{
		SkillObject * obj = new SkillObject("boom");
		obj->duration = 1.0f;
		obj->moveDir = D3DXVECTOR2(1.0f, 0.0f);
		obj->moveSpeed = 100.0f;
		obj->position = caster->position;
		obj->enemyTag = caster->enemyTag;
		SceneManager::GetInstance()->curScene->AddObject(obj);
	}
}
