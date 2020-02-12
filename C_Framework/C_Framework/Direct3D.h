#pragma once


struct Direct3D
{
private:
	static Direct3D* inst;
	Direct3D();

public:
	static Direct3D* GetInstance() 
	{
		if (!inst)
			inst = new Direct3D();

		return inst;
	}

	struct Vertex
	{
		D3DXVECTOR3 pos;
		D3DCOLOR diffuse;
		D3DXVECTOR2 uvux;
	};

	const int VertexFVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_DIFFUSE;

	D3DXMATRIX viewMat;
	D3DXMATRIX projMat;

	ID3DXLine* pLine;
	IDirect3DVertexBuffer9* pVB;

	IDirect3D9* pD3D9;
	IDirect3DDevice9* pD3D9Device;

	const int screenWidth = 1280;
	const int screenHeight = 720;

	D3DXVECTOR3 CameraPos = { 0, 0, 0 };

	bool Initialize(HWND hWnd);

	void Render();

	void MoveCamera(D3DXVECTOR3 pos);
};