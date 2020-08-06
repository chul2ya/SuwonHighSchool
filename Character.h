#pragma once

class Character : public Object
{
public:

	Sprite mSprite;

	virtual bool Init() override;
	virtual void Term() override;
	virtual void Update(float deltaTime) override;
	virtual void LateUpdate(float deltaTime) override;
	virtual void Render() override;
};