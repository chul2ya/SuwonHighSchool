#pragma once

class Texture
{
public:
	LPDIRECT3DTEXTURE9 pImage;
	D3DXIMAGE_INFO Info;
};

class TextureManager : public SingleInstance<TextureManager>
{
private:
	map<string, Texture*> texMaps;

public:

	Texture * GetTexture(string pathWithName)
	{
		auto tf = texMaps.find(pathWithName);
		if (tf == texMaps.end())
		{
			Texture * tex = new Texture;
			
			auto device =  Direct3D::GetInstance()->pD3D9Device;
			HRESULT hr = D3DXCreateTextureFromFileEx(
				device,
				pathWithName.c_str(),
				D3DX_DEFAULT,
				D3DX_DEFAULT,
				1, 0,
				D3DFMT_UNKNOWN,
				D3DPOOL_DEFAULT,
				D3DX_DEFAULT,
				D3DX_DEFAULT, 0,
				&tex->Info, nullptr,
				&tex->pImage
			);

			if (FAILED(hr))
				return nullptr;

			tf = texMaps.insert(make_pair(pathWithName, tex)).first;
		}

		return tf->second;
	}
};

