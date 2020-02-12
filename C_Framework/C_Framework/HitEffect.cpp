#include "pch.h"

HitEffect::HitEffect() : spr("Assets/Effect/Boom/*.png")
{
	spr.loopAni = false;
	spr.aniTime = 0.03f;
}

void HitEffect::Update(float deltaTime)
{
	if (spr.curScene >= (int)spr.ptexs.size() - 1)
		isRemove = true;

	spr.Update(deltaTime);
}

void HitEffect::LateUpdate(float deltaTime)
{
}

void HitEffect::Render()
{
	spr.pos = position;
	spr.Render();
}
