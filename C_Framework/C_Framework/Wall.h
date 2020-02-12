#pragma once
class Wall : public GameObject
{
public:
	Sprite spr;
	int kind = 0; //1 좌 2 위 3 오 4 아 5 발판

	Wall(string str);
	virtual ~Wall();

	virtual void Update(float deltaTime);
	virtual void OnCollisionInprogress(Object* another, float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void Render();

	virtual void FileLoad(std::string buffer);
};

