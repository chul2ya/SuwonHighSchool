#include "pch.h"


Enemy::Enemy() : Character("Kyo Kusanagi")
{
	tag = "KyoKusanagi";
	enemyTag = "TerryBogard";
	AddSkill(new Kick(this));
	standUpFream = 6;
	moveSpeed = 250.f;
	SetCollision(&stateSprs[0]);
	position.x += 500;
	hp = 10;
}

Enemy::Enemy(Player* player) : Character("Kyo Kusanagi")
{
	tag = "KyoKusanagi";
	enemyTag = "TerryBogard";
	m_Player = player;
	AddSkill(new Kick(this));
	standUpFream = 6;
	moveSpeed = 250.f;
	SetCollision(&stateSprs[0]);
	position.x += 500;
	hp = 10;
}

void Enemy::Update(float deltaTime)
{
	if (m_Player != nullptr)
	{
		if (!IsHit)
		{
			AttackCool -= deltaTime;
			stateTime -= deltaTime;
			if (AttackCool <= 0.0f)
			{
				Casting("Kick");
				AttackCool = (rand() % 3) ? 0.2f : (float)(rand() % 3);
			}
			else if (stateTime > 0.0f && bState)
			{
			}
			else if (stateTime > 0.0f && !bState)
			{
				//moveDir = m_Player->position - position ;
				//D3DXVec2Normalize(&moveDir, &moveDir);
				moveDir.x = m_Player->position.x - position.x;
				D3DXVec2Normalize(&moveDir, &moveDir);
			}
			else
			{
				bState = !bState;
				stateTime = (float)(rand() % 3);
			}
		}
	}
	Character::Update(deltaTime);
}

void Enemy::LateUpdate(float deltaTime)
{
}

void Enemy::Render()
{
	
	Character::Render();
}
