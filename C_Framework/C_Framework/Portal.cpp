#include "pch.h"

Portal::Portal() : spr("Assets/Portal/*.png")
{
	tag = "Portal";
}

Portal::~Portal()
{
}

void Portal::Update(float deltaTime)
{
	spr.Update(deltaTime);
}

void Portal::OnCollisionInprogress(Object * another, float deltaTime)
{
	if (another->tag == "Player") 
	{
		Player* player = static_cast<Player*>(another);
		if (Kind == 1)
		{
			float nextPos = -1 * player->position.x + player->NowRoom->position.x;
			player->position.x = nextPos - (nextPos > 0 ? player->stateSprs[0].ptexs[0]->Info.Width + 100 - nextRoom->position.x : -100 - nextRoom->position.x);
		}
		else if (Kind == 2)
		{
			
			float nextPos = -1 * player->position.y + player->NowRoom->position.y;
			player->position.x += 100.f;
			player->position.y = nextPos - (nextPos > 0 ? player->stateSprs[0].ptexs[0]->Info.Height - nextRoom->position.y : -nextRoom->position.y);
		}
		player->NowRoom = nextRoom;
		player->moveDir = D3DXVECTOR2(0.0f, -0.01f);
	}
}

void Portal::LateUpdate(float deltaTime)
{
}

void Portal::Render()
{
	spr.pos = position;
	spr.Render();
	Object::Render();
}
