#pragma once
class Player : public Character
{
public:
	Player();

	virtual void Update(float deltaTime) override;
	virtual void LateUpdate(float deltaTime) override;
	virtual void Render() override;
};

