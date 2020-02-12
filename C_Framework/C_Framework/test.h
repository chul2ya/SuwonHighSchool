#pragma once
class test : public Object
{
	Sprite sprite;

public:
	test();

	virtual void Update(float deltaTime) override;
	virtual void OnCollisionInprogress(Object* another, float deltaTime) override;
	virtual void LateUpdate(float deltaTime) override;
	virtual void Render() override;
};

