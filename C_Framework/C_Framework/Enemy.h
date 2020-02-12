#pragma once
class Enemy : public Character
{
	Player* m_Player = nullptr;
	float AttackCool = 0.0f;
	float stateTime = 0.0f;
	bool bState = false;

public:
	Enemy();
	Enemy(Player* player);

	virtual void Update(float deltaTime) override;
	virtual void LateUpdate(float deltaTime) override;
	virtual void Render() override;
};

