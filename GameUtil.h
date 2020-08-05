#pragma once

class Sprite;
class SpriteDrawInfo;

class Vertex
{
public:
	D3DXVECTOR3 mPosition;
	D3DCOLOR mDiffuse;
	D3DXVECTOR2 mUV;
};
#define VertexFVF ( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

class GameUtil : public SingletonDX<GameUtil>
{

	LPD3DXFONT mFont;
	LPD3DXLINE mLine;
	LPDIRECT3DVERTEXBUFFER9 mSpriteVB;

public:

	~GameUtil();

	virtual void OnCreate() override;
	virtual void OnDestroy() override;
	virtual void OnReset() override;
	virtual void OnLost() override;

	void DrawRect(const RECT& rect);
	void DrawLine(const D3DXVECTOR2& p1, const D3DXVECTOR2& p2);
	void DrawFont(wstring str);

	LPDIRECT3DVERTEXBUFFER9 GetSpriteVertexBuffer() { return mSpriteVB; }
};