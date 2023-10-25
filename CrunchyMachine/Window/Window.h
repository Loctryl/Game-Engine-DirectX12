#pragma once
#include "Resources/framework.h"
#include "Resources/Resource.h"

class Window
{
	HWND hWnd;
	HINSTANCE hInst;                                // current instance
	WCHAR szTitle[MAX_LOADSTRING] = L"LearnD3D";                  // The title bar text
	WCHAR szWindowClass[MAX_LOADSTRING] = L"LearnD3D";            // the main window class name

	HINSTANCE hPrevInstance = 0;
	LPWSTR lpCmdLine = 0;
	int nCmdShow = SW_SHOW;


	BOOL InitInstance();

	ATOM MyRegisterClass();


public:
	Window();
	~Window() = default;

	bool InitWindow();

	HWND& GetHWND();

	HINSTANCE& GetHInstance();
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);