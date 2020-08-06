#include "Game.h"

bool Character::Init()
{
	mSprite = Sprite(L"Assets/Sample/");
	return true;
}

void Character::Term()
{
}

void Character::Update(float deltaTime)
{
	mSprite.Update(deltaTime);
}

void Character::LateUpdate(float deltaTime)
{
}

void Character::Render()
{
	SpriteRenderInfo info;
	info.mPosition = mPosition;
	mSprite.Render(info);
}
