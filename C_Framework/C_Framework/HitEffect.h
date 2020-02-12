#pragma once
class HitEffect : public Object
{
	Sprite spr;

public:
	HitEffect();

	virtual void Update(float deltaTime) override;
	virtual void LateUpdate(float deltaTime) override;
	virtual void Render() override;
};