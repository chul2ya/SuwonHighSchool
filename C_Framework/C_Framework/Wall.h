#pragma once
class Wall : public GameObject
{
public:
	Sprite spr;
	int kind = 0; //1 �� 2 �� 3 �� 4 �� 5 ����

	Wall(string str);
	virtual ~Wall();

	virtual void Update(float deltaTime);
	virtual void OnCollisionInprogress(Object* another, float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void Render();

	virtual void FileLoad(std::string buffer);
};

