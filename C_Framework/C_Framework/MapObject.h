#pragma once
class MapObject : public GameObject
{
public:
	MapObject();
	virtual ~MapObject();

	virtual void Update(float deltaTime);
	virtual void OnCollisionInprogress(Object* another, float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void Render();
};

