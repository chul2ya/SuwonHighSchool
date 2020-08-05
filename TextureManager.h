#pragma once

class Texture
{
public:
	LPDIRECT3DTEXTURE9 mTexture;
	D3DXIMAGE_INFO mInfo;
};

class TextureManager : public SingletonDX<TextureManager>
{
private:

	map<wstring, Texture*> mTextures;

public:

	virtual void OnCreate() override;
	virtual void OnDestroy() override;
	virtual void OnReset() override;
	virtual void OnLost() override;

	Texture* GetTexture(wstring pathWithName);

};
