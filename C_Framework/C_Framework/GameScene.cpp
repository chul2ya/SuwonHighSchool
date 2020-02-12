#include "pch.h"
#include "test.h"

void GameScene::Init()
{
	AddObject(new test);
	Room room;

	roomManager.GenerateRooms(); 
	//room.LoadRoom("Assets/Room/test1.txt");
	//room.ObjectSpawn();
	//Player* player = new Player;
	//AddObject(player);
	//AddObject(new Enemy(player));
}

void GameScene::CollisionUpdate(float deltaTime)
{
	roomManager.ChangeRoom(PlayerManager::GetInstance()->NowRoom);
	Scene::CollisionUpdate(deltaTime);

	
}

void GameScene::Term()
{
}

void GameScene::Render()
{
	Scene::Render();
	roomManager.test();
}
