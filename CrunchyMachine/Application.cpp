#include "Application.h"
#include "Window/Window.h"
#include "DirectX12/D3DApp.h"
#include "GameTimer.h"
#include "Engine/GameObjectManager.h"
#include "Engine/GameObject.h"
#include "GeoManager.h"
#include "Camera.h"
#include "SpaceShip.h"
#include "Input.h"


Application::Application()
{

    mMainWindow = new Window();
    mDirectX = D3DApp::GetInstance();
    mTimer = new GameTimer();
    mAppPaused = false;
	mInput = new Input();
}

Application::~Application()
{
	delete mTimer;
	delete mDirectX;
	delete mMainWindow;
	delete mInput;
}

void Application::Init()
{
	mMainWindow->InitWindow();
	D3DApp::GetInstance()->Init();

    Astero* a = new Astero();
    asts.push_back(a);
    
    SpaceShip* sp = new SpaceShip();

    asts.push_back(sp);


}

int Application::Run()
{
	MSG msg = { 0 };

	mTimer->Reset();

	// Boucle de messages principale :
	while (msg.message != WM_QUIT)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		mTimer->Tick();

		if (!mAppPaused)
		{
			Update(mTimer);
			Render(mTimer);
			EndFrame(mTimer);
		}

	}

	return (int)msg.wParam;
}

void Application::CalculateFrameStats()
{

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;
	frameCnt++;
	// Compute averages over one second period.
	if ((mTimer->TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;
		wstring fpsStr = to_wstring(fps);
		wstring mspfStr = to_wstring(mspf);
		wstring windowText =
			L" fps: " + fpsStr +
			L" mspf: " + mspfStr;
		SetWindowText(mMainWindow->GetHWND(), windowText.c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}

}

void Application::Update(GameTimer* timer)
{
    CalculateFrameStats();
	
	mInput->UpdateArray();

	switch (static_cast<int>(mInput->GetInputStates()[0])) {
	case 0:
		timer->ResetSlowMo();
		break;
	case 3:
		timer->IndentSlowMo();
		timer->SlowMotion(timer->SlowMoIndent());
		break;
	default:
		break;
	}

    GameObjectManager::GetInstance()->Run(timer);
}

void Application::Render(GameTimer* timer)
{
    RenderManager::GetInstance()->Render();
    mDirectX->Draw(timer);
}

void Application::EndFrame(GameTimer* timer)
{
    GameObjectManager::GetInstance()->DeleteGameObject(timer);
}