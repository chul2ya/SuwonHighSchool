#include "pch.h"


SkillObject::SkillObject(string name)
{
	if (name != "")
	{
		spr = Sprite("Assets/SkillObject/" + name + "/*.png");
	}
	SetCollision(&spr);
}

void SkillObject::Update(float deltaTime)
{
	if (pastTime > duration)
	{
		isRemove = true;
	}
	else
	{
		if (moveDir != D3DXVECTOR2(0.0f, 0.0f))
		{
			position += moveDir * moveSpeed * deltaTime;
		}
	}

	if ((int)spr.ptexs.size() != 0)
	{
		spr.Update(deltaTime);
	}

	pastTime += deltaTime;
}

void SkillObject::OnCollisionInprogress(Object * another, float deltaTime)
{
	if (hitObjects.find(another) != hitObjects.end())
		return;

	if (another->tag == enemyTag)
	{
		Character* ch = static_cast<Character*>(another);
		ch->Hit(1, ((ch->position.x - position.x > 0) ? false : true));
		ch->IsHit = true;
		hitObjects.insert(make_pair(ch, pastTime));
		if (ch->hp > 0)
		{
			isRemove = true;
			HitEffect* hit = new HitEffect();
			D3DXVECTOR2 NormalizePos = ch->position - position;
			D3DXVec2Normalize(&NormalizePos, &NormalizePos);
			hit->position = position + NormalizePos * (D3DXVec2Length(&(ch->position - position)) / 2);
			SceneManager::GetInstance()->curScene->AddObject(hit);
		}
	}
}

void SkillObject::LateUpdate(float deltaTime)
{
}

void SkillObject::Render()
{
	if ((int)spr.ptexs.size() != 0)
	{
		spr.pos = position;
		spr.Render();
	}
	Object::Render();
}
