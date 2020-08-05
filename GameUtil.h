#pragma once

class GameUtil : public SingletonDX<GameUtil>
{
	
	LPD3DXFONT mFont;
	LPD3DXLINE mLine;

public:

	virtual void OnCreate() override;
	virtual void OnDestroy() override;
	virtual void OnReset() override;
	virtual void OnLost() override;

	void DrawRect(const RECT& rect);
	void DrawLine(const D3DXVECTOR2& p1, const D3DXVECTOR2& p2);
	void DrawFont(wstring str);

};