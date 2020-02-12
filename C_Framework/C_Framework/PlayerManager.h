#pragma once
class PlayerManager
{
	PlayerManager() {};
	static PlayerManager* inst;
public:
	static PlayerManager* GetInstance()
	{
		if (!inst)
			inst = new PlayerManager();

		return inst;
	}

public:
	D3DXVECTOR2 PlayerPos = D3DXVECTOR2(0.0f, 0.0f);
	Room* NowRoom = nullptr;
	bool isBattle = false;
};