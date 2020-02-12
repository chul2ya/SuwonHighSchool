#include "pch.h"
#include <io.h>
#include <iostream>


Sprite::Sprite()
{
}

Sprite::Sprite(string path)
{
	_finddata_t fd;
	intptr_t handle;
	if ((handle = _findfirst(path.c_str(), &fd)) == -1L)
	{

		return;
	}
	path.erase(path.begin() + path.rfind("/") + 1, path.end());

	do
	{
		ptexs.push_back(TextureManager::GetInstance()->GetTexture(path + fd.name));
	} while (_findnext(handle, &fd) == 0);
	_findclose(handle);
}

Sprite::~Sprite()
{
}

void Sprite::Update(float deltaTime)
{
	curAniTime += deltaTime;
	if (curAniTime > aniTime) 
	{
		curAniTime -= aniTime;
		if (++curScene >= (int)ptexs.size())
		{
			if (loopAni)
				curScene = 0;
			else
				curScene  -= 1;
		}
	}
}

void Sprite::Render()
{
	Texture* pTex = ptexs[curScene];

	void* ppVB;
	HRESULT hr = Direct3D::GetInstance()->pVB->Lock(0, 0, &ppVB, 0);
	if (FAILED(hr)) return;

	auto pD3D9Device = Direct3D::GetInstance()->pD3D9Device;

	Direct3D::Vertex vertex[4] = {
		Direct3D::Vertex {D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_ARGB(a,r,g,b), D3DXVECTOR2(0.0f, 1.0f)},
		Direct3D::Vertex {D3DXVECTOR3(0.0f, (float)pTex->Info.Height, 0.0f), D3DCOLOR_ARGB(a,r,g,b), D3DXVECTOR2(0.0f, 0.0f)},
		Direct3D::Vertex {D3DXVECTOR3((float)pTex->Info.Width, 0.0f, 0.0f), D3DCOLOR_ARGB(a,r,g,b), D3DXVECTOR2(1.0f, 1.0f)},
		Direct3D::Vertex {D3DXVECTOR3((float)pTex->Info.Width, (float)pTex->Info.Height, 0.0f), D3DCOLOR_ARGB(a,r,g,b), D3DXVECTOR2(1.0f, 0.0f)},
	};

	std::memcpy(ppVB, vertex, sizeof(vertex));
	Direct3D::GetInstance()->pVB->Unlock();

	D3DXVECTOR2 _tex = D3DXVECTOR2((float)pTex->Info.Width, (float)pTex->Info.Height);
	D3DXVECTOR2 _center = D3DXVECTOR2(center.x * _tex.x, center.y * _tex.y);
	D3DXVECTOR2 _scaleAnchor = D3DXVECTOR2(scaleAnchor.x * _tex.x, scaleAnchor.y * _tex.y) + _center;
	D3DXVECTOR2 _rotateAnchor = D3DXVECTOR2(rotateAnchor.x * _tex.x, rotateAnchor.y * _tex.y) + _center;
	D3DXVECTOR2 _pos = pos - _center;

	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(&matrix, &_scaleAnchor, 0.0f, &scale, &_rotateAnchor, -rotate / 100, &_pos);

	pD3D9Device->SetTransform(D3DTS_WORLD, &matrix);

	pD3D9Device->SetTexture(0, pTex->pImage);	

	pD3D9Device->SetStreamSource(0, Direct3D::GetInstance()->pVB, 0, sizeof(Direct3D::Vertex));
	pD3D9Device->SetFVF(Direct3D::GetInstance()->VertexFVF);
	pD3D9Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 4);
}
