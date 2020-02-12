#include "pch.h"

Direct3D* Direct3D::inst = nullptr;


Direct3D::Direct3D() 
{
}

bool Direct3D::Initialize(HWND hWnd)
{
	pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	if (!pD3D9)
		return false;

	D3DPRESENT_PARAMETERS params;
	ZeroMemory(&params, sizeof(params));
	params.BackBufferWidth = screenWidth;
	params.BackBufferHeight = screenHeight;
	params.BackBufferFormat = D3DFMT_X8R8G8B8;
	params.BackBufferCount = 1;
	params.hDeviceWindow = hWnd;
	params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	params.Windowed = true;
	params.EnableAutoDepthStencil = true;
	params.AutoDepthStencilFormat = D3DFMT_D16;
	params.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;

	if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE::D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &params, &pD3D9Device)))
		return false;
	// 조명을 끈다
	pD3D9Device->SetRenderState(D3DRENDERSTATETYPE::D3DRS_LIGHTING, false);
	// z값 사용
	pD3D9Device->SetRenderState(D3DRENDERSTATETYPE::D3DRS_ZENABLE, true);
	// Alpha 허용
	pD3D9Device->SetRenderState(D3DRENDERSTATETYPE::D3DRS_ALPHABLENDENABLE, TRUE);
	pD3D9Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3D9Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pD3D9Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pD3D9Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	pD3D9Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	D3DXMatrixOrthoOffCenterLH(&projMat, 0.0f, (float)screenWidth, 0.0f, (float)screenHeight, 0.0f, 1000.0f);
	pD3D9Device->SetTransform(D3DTS_PROJECTION, &projMat);

	HRESULT hr = pD3D9Device->CreateVertexBuffer(4 * sizeof(Vertex), 0, VertexFVF, D3DPOOL::D3DPOOL_DEFAULT, &pVB, NULL);
	if (FAILED(hr)) return false;
	
	hr = D3DXCreateLine(pD3D9Device, &pLine);
	if (FAILED(hr)) return false;

	SceneManager::GetInstance()->AddScnen("Game", new GameScene);
	SceneManager::GetInstance()->ChangeScene("Game");

	return true;
}

void Direct3D::Render()
{
	Time::GetInstance()->Tick();

	SceneManager::GetInstance()->Update(Time::GetInstance()->deltaTime);

	pD3D9Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xABCDEFED, 1.0f, 0);

	pD3D9Device->BeginScene();

	SceneManager::GetInstance()->Render();

	pD3D9Device->EndScene();

	pD3D9Device->Present(NULL, NULL, NULL, NULL);
}

void Direct3D::MoveCamera(D3DXVECTOR3 pos)
{
	D3DXMatrixLookAtLH(&viewMat, &(pos - D3DXVECTOR3(screenWidth / 2.f, screenHeight / 2.f, 0)), &(pos - D3DXVECTOR3(screenWidth / 2.f, screenHeight / 2.f, -5.f)), &D3DXVECTOR3(0, 1.f, 0));
	pD3D9Device->SetTransform(D3DTS_VIEW, &viewMat);

	CameraPos = pos;

	//D3DXMATRIX projMat;
	//D3DXMatrixPerspectiveFovLH(&projMat, 0 * (3.141592f / 180), screenWidth / screenHeight, 0, 0);
	//pD3D9Device->SetTransform(D3DTS_PROJECTION, &projMat);
}
