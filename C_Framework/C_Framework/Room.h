#pragma once

class Room
{
public:
	enum NextRoom
	{
		nleft,
		ntop,
		nright,
		nbottom,
		nCount
	};
	Room* nextRooms[NextRoom::nCount] = { nullptr };
	D3DXVECTOR2 position = D3DXVECTOR2(0.0f, 0.0f);
	vector<GameObject*>spawnObjects;
	vector<GameObject*>spawnEnemys;

	string FileName = "";

	bool isCrear = false;

	void ObjectSpawn();
	void LoadRoom(string fileName);
	void SaveRoom(Room room, string fileName);
	void test();
};

