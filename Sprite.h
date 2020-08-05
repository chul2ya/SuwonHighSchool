#pragma once

class SpriteRenderInfo
{
public:
	D3DXVECTOR2 mPosition = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 mScaleCen = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 mScale = D3DXVECTOR2(1.0f, 1.0f);
	float mRotate = 0.0f;
	D3DXVECTOR2 mRotateCen = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 mCenter = D3DXVECTOR2(0.5f, 0.5f);
};

class Sprite
{
public:

	vector<Texture*> mTextures;
	float mAniTime = 0.0f;
	float mAniMaxTime = 0.05f;
	float mAlpha = 1.0f, mRed = 1.0f, mGreen = 1.0f, mBlue = 1.0f;
	int mScene = 0;

	Sprite(wstring path);
	void Update(float deltaTime);
	void Render(const SpriteRenderInfo& info);
};