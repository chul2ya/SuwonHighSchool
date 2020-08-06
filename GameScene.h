#pragma once

class GameScene : public Scene
{
public:

	virtual void Create() override;
	virtual void Release() override;
	virtual void Init() override;
	virtual void Term() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};