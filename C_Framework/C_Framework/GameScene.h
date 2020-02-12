#pragma once
#include "Scene.h"
class GameScene : public Scene
{
	RoomManager roomManager;
public:

	virtual void Init() override;
	virtual void CollisionUpdate(float deltaTime);
	virtual void Term() override;
	virtual void Render() override;
};

