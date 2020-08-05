#include "Game.h"

void TextureManager::OnCreate()
{
}

void TextureManager::OnDestroy()
{
	for (auto tex : mTextures)
	{
		tex.second->mTexture->Release();
		delete tex.second;
	}
	mTextures.clear();
}

void TextureManager::OnReset()
{
}

void TextureManager::OnLost()
{
}


Texture * TextureManager::GetTexture(wstring pathWithName)
{
	auto tf = mTextures.find(pathWithName);
	if (tf != mTextures.end())
		return tf->second;

	LPDIRECT3DTEXTURE9 texture;
	D3DXIMAGE_INFO info;
	if (FAILED(D3DXCreateTextureFromFileEx(DXUTGetD3D9Device(), pathWithName.c_str(),
		D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, nullptr, &texture)))
	{
		assert(0);
		return nullptr;
	}

	auto insert = mTextures.insert(make_pair(pathWithName, new Texture()));
	insert.first->second->mTexture = texture;
	insert.first->second->mInfo = info;
	return insert.first->second;
}