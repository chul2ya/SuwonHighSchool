#pragma once

class Collision
{
public:
	 
	RECT mRect = RECT{ 0, 0, 0, 0 };
	vector<D3DXVECTOR2> mLines;
	float mRadius = 0.0f;
};

class Object
{
public:

	Collision mCollision = Collision();
	D3DXVECTOR2 mPosition = D3DXVECTOR2(0.0f, 0.0f);
	int mLayer = 0;
	bool mDestroy = false;

	virtual bool Init() = 0;
	virtual void Term() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void LateUpdate(float deltaTime) = 0;
	virtual void Render() = 0;

};

class ObjectManager
{
private:

	vector<Object*> mObjects;
	vector<Object*> mAddObjects;

public:

	void AddObject(Object* object);

	virtual void Init();
	virtual void Term();
	virtual void Update(float deltaTime);
	virtual void Render();

};
