#pragma once
#include "EngineResources/framework.h"
#include "EngineResources/Resource.h"

// Handles the Windows window
class Window
{
	static HWND hWnd;
	HINSTANCE hInst; // current instance
	WCHAR szTitle[MAX_LOADSTRING] = L"CrunchyMachine"; // The title bar text
	WCHAR szWindowClass[MAX_LOADSTRING] = L"CrunchyMachine"; // the main window class name
	wstring mTitle;

	HINSTANCE hPrevInstance = 0;
	LPWSTR lpCmdLine = 0;
	int nCmdShow = SW_SHOW;

	BOOL InitInstance();

	ATOM MyRegisterClass();


public:
	Window();
	~Window() = default;

	bool InitWindow();

	static HWND& GetHWND();

	HINSTANCE& GetHInstance();

	wstring GetWindowTitle();
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);