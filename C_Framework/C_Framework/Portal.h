#pragma once
class Portal : public GameObject
{
public:
	Sprite spr;
	Room* nextRoom = nullptr;
	int Kind = 1;

	Portal();
	virtual ~Portal();

	virtual void Update(float deltaTime);
	virtual void OnCollisionInprogress(Object* another, float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void Render();
};

