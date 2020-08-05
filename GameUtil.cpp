#include "Game.h"

void GameUtil::OnCreate()
{
	auto device = DXUTGetD3D9Device();

	if (FAILED(D3DXCreateFont(device, 20, 10, 0, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, L"¸¼Àº °íµñ", &mFont)))
	{
		assert(0);
		return;
	}

	if (FAILED(D3DXCreateLine(device, &mLine)))
	{
		assert(0);
		return;
	}

	mLine->SetAntialias(true);
	mLine->SetWidth(1.0f);
}

void GameUtil::OnReset()
{
	auto device = DXUTGetD3D9Device();

	D3DXMATRIX mat;
	D3DXMatrixOrthoOffCenterLH(&mat, 0.0f, 1280.0f, 0.0f, 720.0f, 0.0f, 1.0f);
	device->SetTransform(D3DTS_PROJECTION, &mat);

	D3DXMATRIX view;
	D3DXVECTOR3 eye = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	D3DXVECTOR3 at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&view, &eye, &at, &up);
	device->SetTransform(D3DTS_VIEW, &view);

	mFont->OnResetDevice();
	mLine->OnResetDevice();
}

void GameUtil::OnLost()
{
	mFont->OnLostDevice();
	mLine->OnLostDevice();
}

void GameUtil::OnDestroy()
{
	mFont->Release();
	mFont = nullptr;
	mLine->Release();
	mLine = nullptr;
}

void GameUtil::DrawRect(const RECT & rect)
{
	DrawLine(D3DXVECTOR2((float)rect.left, (float)rect.top), D3DXVECTOR2((float)rect.right, (float)rect.top));
	DrawLine(D3DXVECTOR2((float)rect.right, (float)rect.top), D3DXVECTOR2((float)rect.right, (float)rect.bottom));
	DrawLine(D3DXVECTOR2((float)rect.right, (float)rect.bottom), D3DXVECTOR2((float)rect.left, (float)rect.bottom));
	DrawLine(D3DXVECTOR2((float)rect.left, (float)rect.bottom), D3DXVECTOR2((float)rect.left, (float)rect.top));
}

void GameUtil::DrawLine(const D3DXVECTOR2 & p1, const D3DXVECTOR2 & p2)
{
	auto device = DXUTGetD3D9Device();
	mLine->Begin();
	auto vertices = { p1, p2 };
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	device->SetTransform(D3DTS_WORLD, &mat);
	mLine->Draw(vertices.begin(), 2, D3DCOLOR_ARGB(255, 255, 255, 255));
	mLine->End();
}

void GameUtil::DrawFont(wstring str)
{
	RECT rect = { 0, 0, 0, 0 };
	if (FAILED(mFont->DrawTextW(nullptr, str.c_str(), str.length(), &rect, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255))))
		assert(false);
}
