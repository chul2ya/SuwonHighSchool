#include "pch.h"
#include "Enemy.h"
#include "Player.h"

void Room::ObjectSpawn()
{
	LoadRoom(FileName);

	Wall* wall = new Wall("1");
	wall->kind = 2;
	wall->NowRoom = this;
	wall->spr.center = D3DXVECTOR2(0.5f, 0.0f);
	wall->position = position - D3DXVECTOR2(0.0f, -1080.0f / 2.0f);
	wall->SetCollision(&wall->spr);
	spawnObjects.push_back(wall);
	wall = new Wall("1");
	wall->kind = 4;
	wall->NowRoom = this;
	wall->spr.center = D3DXVECTOR2(0.5f, 1.0f);
	wall->position = position - D3DXVECTOR2(0.0f, 1080.0f / 2.0f);
	wall->SetCollision(&wall->spr);
	spawnObjects.push_back(wall);
	wall = new Wall("2");
	wall->kind = 3;
	wall->NowRoom = this;
	wall->spr.center = D3DXVECTOR2(0.0f, 0.5f);
	wall->position = position - D3DXVECTOR2(-1920.0f / 2.0f, 0.0f);
	wall->SetCollision(&wall->spr);
	spawnObjects.push_back(wall);
	wall = new Wall("2");
	wall->kind = 1;
	wall->NowRoom = this;
	wall->spr.center = D3DXVECTOR2(1.0f, 0.5f);
	wall->position = position - D3DXVECTOR2(1920.0f / 2.0f, 0.0f);
	wall->SetCollision(&wall->spr);
	spawnObjects.push_back(wall);

	for (int i = 0; i < NextRoom::nCount; ++i)
	{
		if (nextRooms[i] == nullptr)
			continue;
		Portal* portal = new Portal;
		portal->NowRoom = this;
		portal->nextRoom = nextRooms[i];
		if (i == NextRoom::nleft)
		{
			portal->Kind = 1;
			portal->position = position + D3DXVECTOR2(-900.0f, -540.0f);
			portal->spr.center = D3DXVECTOR2(0.0f, 0.0f);
		}
		else if (i == NextRoom::ntop)
		{
			portal->Kind = 2;
			portal->position = position + D3DXVECTOR2(0.0f, 540.0f);
			portal->spr.center = D3DXVECTOR2(0.5f, 1.0f);
		}
		else if (i == NextRoom::nright)
		{
			portal->Kind = 1;
			portal->position = position + D3DXVECTOR2(900.0f, -540.0f);
			portal->spr.center = D3DXVECTOR2(1.0f, 0.0f);
		}
		else if (i == NextRoom::nbottom)
		{
			portal->Kind = 2;
			portal->position = position + D3DXVECTOR2(0.0f, -540.0f);
			portal->spr.center = D3DXVECTOR2(0.5f, 0.0f);
		}
		portal->SetCollision(&portal->spr);
		spawnObjects.push_back(portal);
	}

	for (auto it = spawnObjects.begin(); it != spawnObjects.end(); ++it)
	{
		(*it)->NowRoom = this;
		SceneManager::GetInstance()->curScene->AddObject((*it));
	}
}

void Room::LoadRoom(string fileName)
{
	FILE* fp = fopen(fileName.c_str(), "r");

	while (!feof(fp))
	{
		char buffer[255] = {};
		fgets(buffer, sizeof(buffer), fp);

		char* type = strtok(buffer, " ");
		if (type == nullptr)
			continue;
		std::string calc = type;

		GameObject* add = nullptr;
		if (calc == "KyoKusanagi")
		{
			add = new Enemy();
			add->position = position;
			add->FileLoad(buffer);
		}
		else if (calc == "Floor")
		{
			add = new Wall("3");
			add->position = position;
			add->FileLoad(buffer);
		}

		add->NowRoom = this;
		spawnObjects.push_back(add);
	}

	std::fclose(fp);

}

void Room::SaveRoom(Room room, string fileName)
{
	FILE* fp = fopen(fileName.c_str(), "w");

	for (int i = 0; i <(int) room.spawnObjects.size(); ++i)
	{
		room.spawnObjects[i]->FileSave(fp);
	}

	std::fclose(fp);
}

void Room::test()
{
	auto pLine = Direct3D::GetInstance()->pLine;

	pLine->SetWidth(5.0f);
	pLine->SetAntialias(true);

	D3DXVECTOR3 circle[5] = { };
	circle[0] = D3DXVECTOR3(-960, -540, 0) + D3DXVECTOR3(position.x, position.y, 0);
	circle[1] = D3DXVECTOR3(-960, 540, 0) + D3DXVECTOR3(position.x, position.y, 0);
	circle[2] = D3DXVECTOR3(960, 540, 0) + D3DXVECTOR3(position.x, position.y, 0);
	circle[3] = D3DXVECTOR3(960, -540, 0) + D3DXVECTOR3(position.x, position.y, 0);
	circle[4] = D3DXVECTOR3(-960, -540, 0) + D3DXVECTOR3(position.x, position.y, 0);
	

	D3DXMATRIX lineMat = Direct3D::GetInstance()->viewMat * Direct3D::GetInstance()->projMat;

	pLine->Begin();
	HRESULT hr = pLine->DrawTransform(circle, 5, &lineMat, D3DCOLOR_ARGB(255, 255, 0, 0));
	pLine->End();
}
