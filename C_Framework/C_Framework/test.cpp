#include "pch.h"
#include "test.h"


test::test() : sprite("Assets/1.png")
{
	SetCollision(&sprite);
}

void test::Update(float deltaTime)
{
	if (GetAsyncKeyState(VK_UP))
		position.y += 1250 * deltaTime;
	if (GetAsyncKeyState(VK_DOWN))
		position.y -= 1250 * deltaTime;
	if (GetAsyncKeyState(VK_LEFT))
		position.x -= 1250 * deltaTime;
	if (GetAsyncKeyState(VK_RIGHT))
		position.x += 1250 * deltaTime;

	if (GetAsyncKeyState(VK_SPACE))
		sprite.rotate += 12500 * deltaTime;
}

void test::OnCollisionInprogress(Object * another, float deltaTime)
{
	if (another->tag == "Wall")
	{
		Wall* wall = static_cast<Wall*>(another);
		if (wall->kind == 4 || wall->kind == 2 || wall->kind == 1)
		{
			int a;
			a = 0;

		}
	}
}

void test::LateUpdate(float deltaTime)
{
	//Direct3D::GetInstance()->MoveCamera(D3DXVECTOR3( position.x, position.y, 0));
}

void test::Render()
{
	sprite.pos = position;
	sprite.Render();
	Object::Render();
}
