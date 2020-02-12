#pragma once
class Object
{
public:
	D3DXVECTOR2 position = D3DXVECTOR2(0.0f, 0.0f);
	vector<D3DXVECTOR2> collisionLine;
	string tag = "";

	bool isRemove = false;

	virtual void Update(float deltaTime) = 0;
	virtual void OnCollisionInprogress(Object* another, float deltaTime) { };
	virtual void LateUpdate(float deltaTime) = 0;
	virtual void Render();
	virtual void SetCollision(Sprite* spr);
};

