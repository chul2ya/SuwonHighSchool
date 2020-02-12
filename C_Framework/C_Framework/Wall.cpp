#include "pch.h"



Wall::Wall(string str) : spr("Assets/Wall/" + str + ".png" )
{
	tag = "Wall";

	SetCollision(&spr);
}

Wall::~Wall()
{
}

void Wall::Update(float deltaTime)
{
	spr.Update(deltaTime);
}

void Wall::OnCollisionInprogress(Object * another, float deltaTime)
{
}

void Wall::LateUpdate(float deltaTime)
{
}

void Wall::Render()
{
	spr.pos = position;
	spr.Render();
	Object::Render();
}

void Wall::FileLoad(std::string buffer)
{
	GameObject::FileLoad(buffer);
	spr.center = D3DXVECTOR2(0.5f, 1.0f);
	SetCollision(&spr);
	kind = 5;
}
