#include "Game.h"

GameUtil::~GameUtil()
{
	delete TextureManager::GetInstance();
}

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
	
	if (FAILED(device->CreateVertexBuffer(sizeof(Vertex) * 4, 0, VertexFVF, D3DPOOL_MANAGED, &mSpriteVB, nullptr)))
	{
		assert(0);
		return;
	}

	TextureManager::GetInstance()->OnCreate();

	mLine->SetAntialias(true);
	mLine->SetWidth(1.0f);
}

void GameUtil::OnReset()
{
	auto device = DXUTGetD3D9Device();

	mFont->OnResetDevice();
	mLine->OnResetDevice();

	D3DXMATRIX mat;
	D3DXMatrixOrthoOffCenterLH(&mat, 0.0f, 1280.0f, 0.0f, 720.0f, 0.0f, 1.0f);
	device->SetTransform(D3DTS_PROJECTION, &mat);

	D3DXMATRIX view;
	D3DXVECTOR3 eye = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	D3DXVECTOR3 at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&view, &eye, &at, &up);
	device->SetTransform(D3DTS_VIEW, &view);

	device->SetRenderState(D3DRENDERSTATETYPE::D3DRS_ZENABLE, D3DZB_TRUE);
	device->SetRenderState(D3DRENDERSTATETYPE::D3DRS_LIGHTING, FALSE);
	device->SetRenderState(D3DRENDERSTATETYPE::D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRENDERSTATETYPE::D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	device->SetRenderState(D3DRENDERSTATETYPE::D3DRS_CULLMODE, D3DCULL_NONE);
	device->SetRenderState(D3DRENDERSTATETYPE::D3DRS_ALPHABLENDENABLE, TRUE);
	device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	TextureManager::GetInstance()->OnReset();
}

void GameUtil::OnLost()
{
	mFont->OnLostDevice();
	mLine->OnLostDevice();

	TextureManager::GetInstance()->OnLost();
}

void GameUtil::OnDestroy()
{
	mFont->Release();
	mFont = nullptr;
	mLine->Release();
	mLine = nullptr;
	mSpriteVB->Release();
	mSpriteVB = nullptr;

	TextureManager::GetInstance()->OnDestroy();
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

void GameUtil::DrawTextFormat(const WCHAR* strMsg, ...)
{
	WCHAR strBuffer[512];

	va_list args;
	va_start(args, strMsg);
	vswprintf_s(strBuffer, 512, strMsg, args);
	strBuffer[511] = L'\0';
	va_end(args);

	RECT rect = { 0, 0, 0, 0 };
	if (FAILED(mFont->DrawTextW(nullptr, strBuffer, -1, &rect, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255))))
		assert(false);
}