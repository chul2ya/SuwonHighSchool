#pragma once

#include "pch.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) 
{
	WNDCLASSEX wndInfo;
	ZeroMemory(&wndInfo, sizeof(wndInfo));
	wndInfo.cbSize = sizeof(wndInfo);
	wndInfo.style = CS_CLASSDC;
	wndInfo.lpfnWndProc = WndProc;  
	wndInfo.hInstance = hInstance;
	wndInfo.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndInfo.lpszClassName = "Chul2Framework";
	RegisterClassExA(&wndInfo);

	HWND hWnd = CreateWindowEx(
		WS_EX_LEFT,
		"Chul2Framework",
		"Chul2Framework",
		WS_OVERLAPPEDWINDOW,
		100, 100,
		Direct3D::GetInstance()->GetInstance()->GetInstance()->GetInstance()->GetInstance()->GetInstance()->GetInstance()->GetInstance()->GetInstance()->GetInstance()->GetInstance()->screenWidth,
		Direct3D::GetInstance()->screenHeight,
		NULL, NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	if (Direct3D::GetInstance()->Initialize(hWnd)) 
	{
		while (true) {
			MSG msg;
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					break;
				
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				Direct3D::GetInstance()->Render();

				char chr[50];
				sprintf(chr, "FPS : %02d | Delta : %.4f", Time::GetInstance()->FPS, Time::GetInstance()->deltaTime);
				SetWindowTextA(hWnd, chr);
				
			}
		}
	}
	else 
	{
		MessageBox(NULL, "Failed Initialize Direct3D", "Error", MB_OK);
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
