#include "pch.h"

RoomManager::RoomManager()
{
}


RoomManager::~RoomManager()
{
	for (auto it = vRooms.begin(); it != vRooms.end(); ++it)
	{
		delete (*it);
	}
}

void RoomManager::ChangeRoom(Room * room)
{
	if (nowRoom != room)
	{
		for (auto i = nowRoom->spawnObjects.begin(); i != nowRoom->spawnObjects.end(); ++i)
		{
			(*i)->isRemove = true;
		}
		nowRoom->spawnObjects.clear();
		nowRoom = room;
		nowRoom->ObjectSpawn();
	}
}

void RoomManager::GenerateRooms()
{
	srand((unsigned int)time(NULL));
	char roomKey[255] = "0,0";
	bool isBossRoom = false;
	int roomCount = rand() % 4 + 8;

	D3DXVECTOR2 roomPos = D3DXVECTOR2(0.0f, 0.0f);
	sprintf(roomKey, "%1.0f,%1.0f", roomPos.x, roomPos.y);

	Room* room = new Room;
	room->position = roomPos;
	room->FileName = ("Assets/Room/StartRoom.txt");
	mRooms[roomKey] = room;
	room->isCrear = true;
	Character* add = new Player();
	add->position = roomPos;
	add->NowRoom = room;
	SceneManager::GetInstance()->curScene->AddObject((add));
	vRooms.push_back(room);
	nowRoom = room;

	while (roomCount > 0)
	{
		auto it = vRooms.begin();
		int randomRoom = rand() % vRooms.size() + 1;
		for (int i = 1; randomRoom != i; ++i)
			++it;

		switch (rand() % 4 + 1)
		{
			case 1:
			{
				roomPos.x = (*it)->position.x / 2000.f + left.x;
				roomPos.y = (*it)->position.y / 1160.f + left.y;
				sprintf(roomKey, "%1.0f,%1.0f", roomPos.x, roomPos.y);
				if (mRooms[roomKey] != nullptr)
					continue;
				room = new Room;
				room->position = (*it)->position + left * 2000.f;
				mRooms[roomKey] = room;
				vRooms.push_back(room);
				--roomCount;
			}break;

			case 2:
			{
				roomPos.x = (*it)->position.x / 2000.f + top.x;
				roomPos.y = (*it)->position.y / 1160.f + top.y;
				sprintf(roomKey, "%1.0f,%1.0f", roomPos.x, roomPos.y);
				if (mRooms[roomKey] != nullptr)
					continue;
				room = new Room;
				room->position = (*it)->position + top * 1160.f;
				mRooms[roomKey] = room;
				vRooms.push_back(room);
				--roomCount;
			}break;

			case 3:
			{
				roomPos.x = (*it)->position.x / 2000.f + right.x;
				roomPos.y = (*it)->position.y / 1160.f + right.y;
				sprintf(roomKey, "%1.0f,%1.0f", roomPos.x, roomPos.y);
				if (mRooms[roomKey] != nullptr)
					continue;
				room = new Room;
				room->position = (*it)->position + right * 2000.f;
				mRooms[roomKey] = room;
				vRooms.push_back(room);
				--roomCount;
			}break;

			case 4:
			{
				roomPos.x = (*it)->position.x / 2000.f + bottom.x;
				roomPos.y = (*it)->position.y / 1160.f + bottom.y;
				sprintf(roomKey, "%1.0f,%1.0f", roomPos.x, roomPos.y);
				if (mRooms[roomKey] != nullptr)
					continue;
				room = new Room;
				room->position = (*it)->position + bottom * 1160.f;
				mRooms[roomKey] = room;
				vRooms.push_back(room);
				--roomCount;
			}break;
		}

	}

	for (auto it = vRooms.begin(); it != vRooms.end(); ++it)
	{
		if(vRooms.begin() != it)
			(*it)->FileName = ("Assets/Room/Room" + to_string((rand() % 4 + 1)) + ".txt");

		roomPos.x = (*it)->position.x / 2000.f + left.x;
		roomPos.y = (*it)->position.y / 1160.f + left.y;
		sprintf(roomKey, "%1.0f,%1.0f", roomPos.x, roomPos.y);
		if (mRooms[roomKey] != nullptr)
			(*it)->nextRooms[Room::nleft] = mRooms[roomKey];

		roomPos.x = (*it)->position.x / 2000.f + top.x;
		roomPos.y = (*it)->position.y / 1160.f + top.y;
		sprintf(roomKey, "%1.0f,%1.0f", roomPos.x, roomPos.y);
		if (mRooms[roomKey] != nullptr)
			(*it)->nextRooms[Room::ntop] = mRooms[roomKey];

		roomPos.x = (*it)->position.x / 2000.f + right.x;
		roomPos.y = (*it)->position.y / 1160.f + right.y;
		sprintf(roomKey, "%1.0f,%1.0f", roomPos.x, roomPos.y);
		if (mRooms[roomKey] != nullptr)
			(*it)->nextRooms[Room::nright] = mRooms[roomKey];

		roomPos.x = (*it)->position.x / 2000.f + bottom.x;
		roomPos.y = (*it)->position.y / 1160.f + bottom.y;
		sprintf(roomKey, "%1.0f,%1.0f", roomPos.x, roomPos.y);
		if (mRooms[roomKey] != nullptr)
			(*it)->nextRooms[Room::nbottom] = mRooms[roomKey];

	}

	vRooms.front()->ObjectSpawn();
}

void RoomManager::test()
{
	for (auto it = vRooms.begin(); it != vRooms.end(); ++it)
	{
		(*it)->test();
	}
}
