#pragma once

class RoomManager
{
	const D3DXVECTOR2 left = D3DXVECTOR2(-1.0f, 0.0f);
	const D3DXVECTOR2 top = D3DXVECTOR2(0.0f, 1.0f);
	const D3DXVECTOR2 right = D3DXVECTOR2(1.0f, 0.0f);
	const D3DXVECTOR2 bottom = D3DXVECTOR2(0.0f, -1.0f);

	map<string, Room*> mRooms;
	vector<Room*> vRooms;

	Room* nowRoom = nullptr;
public:
	RoomManager();
	virtual ~RoomManager();

	void ChangeRoom(Room* room);
	void GenerateRooms();
	void test();
};

