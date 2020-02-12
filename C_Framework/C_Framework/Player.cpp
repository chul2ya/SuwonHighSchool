#include "pch.h"


Player::Player() : Character("TerryBogard")
{
	tag = "Player";
	enemyTag = "TerryBogard";
	SetCollision(&stateSprs[0]);
	//SetCollisionAngle(D3DXVECTOR2(stateSprs[0].ptexs[0]->Info.Width / 2, stateSprs[0].ptexs[0]->Info.Height / 2), 1);
	standUpFream = 5;
	AddSkill(new Kick(this));
	hp = 10;
}

void Player::Update(float deltaTime)
{
	float move_x = 0;
	if (GetAsyncKeyState(VK_LEFT))
	{
		move_x -= 1;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		move_x += 1;
	}
	if (!IsHit)
	{
		moveDir.x = move_x;
	}

	if (GetAsyncKeyState(VK_UP))
	{
		if(moveDir.y == 0)
			moveDir.y = 1.0f;
	}


	if (GetAsyncKeyState('Q'))
	{
		Casting("Kick");
	}

	//if (GetAsyncKeyState(VK_SPACE)) {}
		//sprite.rotate += 12500 * deltaTime;

	Character::Update(deltaTime);
	PlayerManager::GetInstance()->NowRoom = NowRoom;
}

void Player::LateUpdate(float deltaTime)
{
	Character::LateUpdate(deltaTime);
	PlayerManager::GetInstance()->PlayerPos = position;
	D3DXVECTOR3 cameraPos = Direct3D::GetInstance()->CameraPos;
	cameraPos += (D3DXVECTOR3(position.x, position.y, 0) - cameraPos) * 3 * deltaTime;
	if (cameraPos.x <= NowRoom->position.x - 2020.0f / 2.0f + Direct3D::GetInstance()->screenWidth / 2.0f) cameraPos.x = NowRoom->position.x - 2020.0f / 2.0f + Direct3D::GetInstance()->screenWidth / 2.0f;
	else if (cameraPos.x >= NowRoom->position.x + 2020.0f / 2.0f - Direct3D::GetInstance()->screenWidth / 2.0f) cameraPos.x = NowRoom->position.x + 2020.0f / 2.0f - Direct3D::GetInstance()->screenWidth / 2.0f;
	if (cameraPos.y <= NowRoom->position.y - 1180.0f / 2.0f + Direct3D::GetInstance()->screenHeight / 2.0f) cameraPos.y = NowRoom->position.y - 1180.0f / 2.0f + Direct3D::GetInstance()->screenHeight / 2.0f;
	else if (cameraPos.y >= NowRoom->position.y + 1180.0f / 2.0f - Direct3D::GetInstance()->screenHeight / 2.0f) cameraPos.y = NowRoom->position.y + 1180.0f / 2.0f - Direct3D::GetInstance()->screenHeight / 2.0f;
	/*if (cameraPos.x <= NowRoom->position.x - 1920.0f / 2.0f + Direct3D::GetInstance()->screenWidth / 2.0f) cameraPos.x = NowRoom->position.x - 1920.0f / 2.0f + Direct3D::GetInstance()->screenWidth / 2.0f;
	else if (cameraPos.x >= NowRoom->position.x + 1920.0f / 2.0f - Direct3D::GetInstance()->screenWidth / 2.0f) cameraPos.x = NowRoom->position.x + 1920.0f / 2.0f - Direct3D::GetInstance()->screenWidth / 2.0f;
	if (cameraPos.y <= NowRoom->position.y - 1080.0f / 2.0f + Direct3D::GetInstance()->screenHeight / 2.0f) cameraPos.y = NowRoom->position.y - 1080.0f / 2.0f + Direct3D::GetInstance()->screenHeight / 2.0f;
	else if (cameraPos.y >= NowRoom->position.y + 1080.0f / 2.0f - Direct3D::GetInstance()->screenHeight / 2.0f) cameraPos.y = NowRoom->position.y + 1080.0f / 2.0f - Direct3D::GetInstance()->screenHeight / 2.0f;*/
	Direct3D::GetInstance()->MoveCamera(cameraPos);
	//Direct3D::GetInstance()->MoveCamera(D3DXVECTOR3(position.x, position.y, 0));
}

void Player::Render()
{
	Character::Render();
}
