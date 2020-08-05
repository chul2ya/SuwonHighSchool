#include "Game.h"
#include <filesystem>

Sprite::Sprite(wstring path)
{
	if (experimental::filesystem::is_directory(path))
	{
		for (auto& file : experimental::filesystem::recursive_directory_iterator(path))
			mTextures.push_back(TextureManager::GetInstance()->GetTexture(file.path()));
	}
	else
	{
		mTextures.push_back(TextureManager::GetInstance()->GetTexture(path));
	}

	assert(mTextures.size());
}

void Sprite::Update(float deltaTime)
{
	mAniTime += deltaTime;
	if (mAniTime >= mAniMaxTime)
	{
		mAniTime -= mAniMaxTime;
		if (++mScene >= (int)mTextures.size())
		{
			mScene = 0;
		}
	}
}

void Sprite::Render(const SpriteRenderInfo& info)
{
	auto vb = GameUtil::GetInstance()->GetSpriteVertexBuffer();
	auto texture = mTextures[mScene];

	void* data;
	if (FAILED(vb->Lock(0, 0, &data, 0)))
	{
		assert(0);
		return;
	}

	Vertex v[4];
	// Left Top.
	v[0].mPosition = D3DXVECTOR3(0.0f, (float)texture->mInfo.Height, 0.0f);
	v[0].mDiffuse = D3DCOLOR_ARGB(int(mAlpha * 255.0f), int(mRed * 255.0f), int(mGreen * 255.0f), int(mBlue * 255.0f));
	v[0].mUV = D3DXVECTOR2(0.0f, 0.0f);

	// Right Top.
	v[1].mPosition = D3DXVECTOR3((float)texture->mInfo.Width, (float)texture->mInfo.Height, 0.0f);
	v[1].mDiffuse = D3DCOLOR_ARGB(int(mAlpha * 255.0f), int(mRed * 255.0f), int(mGreen * 255.0f), int(mBlue * 255.0f));
	v[1].mUV = D3DXVECTOR2(1.0f, 0.0f);

	// Left Bottom.
	v[2].mPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	v[2].mDiffuse = D3DCOLOR_ARGB(int(mAlpha * 255.0f), int(mRed * 255.0f), int(mGreen * 255.0f), int(mBlue * 255.0f));
	v[2].mUV = D3DXVECTOR2(0.0f, 1.0f);

	// Right Bottom.
	v[3].mPosition = D3DXVECTOR3((float)texture->mInfo.Width, 0.0f, 0.0f);
	v[3].mDiffuse = D3DCOLOR_ARGB(int(mAlpha * 255.0f), int(mRed * 255.0f), int(mGreen * 255.0f), int(mBlue * 255.0f));
	v[3].mUV = D3DXVECTOR2(1.0f, 1.0f);

	memcpy(data, (void*)v, sizeof(v));
	vb->Unlock();

	D3DXMATRIX mat;
	D3DXVECTOR2 scaleCen = info.mScaleCen + info.mCenter;
	scaleCen = D3DXVECTOR2(scaleCen.x * texture->mInfo.Width, scaleCen.y * texture->mInfo.Height);
	D3DXVECTOR2 rotateCen = info.mRotateCen + info.mCenter;
	rotateCen = D3DXVECTOR2(rotateCen.x * texture->mInfo.Width, rotateCen.y * texture->mInfo.Height);
	D3DXVECTOR2 position = info.mPosition - D3DXVECTOR2(info.mCenter.x * texture->mInfo.Width, info.mCenter.y * texture->mInfo.Height);
	D3DXMatrixTransformation2D(&mat, &scaleCen, 0.0f, &info.mScale, &rotateCen, D3DXToRadian(-info.mRotate), &position);

	auto device = DXUTGetD3D9Device();
	device->SetTransform(D3DTS_WORLD, &mat);
	device->SetStreamSource(0, vb, 0, sizeof(Vertex));
	device->SetFVF(VertexFVF);
	device->SetTexture(0, texture->mTexture);
	device->DrawPrimitive(D3DPRIMITIVETYPE::D3DPT_TRIANGLESTRIP, 0, 2);
}
