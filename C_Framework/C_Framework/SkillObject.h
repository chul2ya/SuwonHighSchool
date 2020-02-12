#pragma once
class SkillObject : public Object
{
public:
	SkillObject(string name);

	string enemyTag = "";

	int damage = 1;

	float duration = 0.0f;

	//float hitInterval;

	D3DXVECTOR2 moveDir = D3DXVECTOR2(0.0f, 0.0f);
	float moveSpeed;

private:
	Sprite spr;
	float pastTime = 0.0f;

	map<Object*, float> hitObjects;
	
	virtual void Update(float deltaTime) override;
	virtual void OnCollisionInprogress(Object* another, float deltaTime) override;
	virtual void LateUpdate(float deltaTime) override;
	virtual void Render() override;
};

