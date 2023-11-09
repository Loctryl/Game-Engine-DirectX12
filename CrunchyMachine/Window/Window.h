#pragma once
#include "EngineResources/framework.h"

// Handles the Windows window
class Window
{
	static HWND hWnd;
	HINSTANCE mHInst; // current instance
	WCHAR mSzTitle[MAX_LOADSTRING] = L"CrunchyMachine"; // The title bar text
	WCHAR mSzWindowClass[MAX_LOADSTRING] = L"CrunchyMachine"; // the main window class name
	wstring mTitle;

	HINSTANCE mPrevInstance = nullptr;
	LPWSTR mCmdLine = nullptr;
	int mCmdShow = SW_SHOW;

	BOOL InitInstance() const;

	ATOM MyRegisterClass() const;


public:
	Window();
	~Window() = default;

	bool InitWindow() const;

	static inline HWND& GetHWND() { return hWnd; }

	 inline HINSTANCE& GetHInstance() { return mHInst; }

	inline wstring GetWindowTitle() { return mTitle; }
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);