#include "Application.h"

#include "Window/Window.h"
#include "DirectX12/D3DApp.h"
#include "Engine/GameTimer.h"
#include "Engine/GameObjectManager.h"
#include "Engine/ComponentManager/RenderManager.h"
#include "Engine/Engine.h"
#include "Engine/Input.h"
#include "GameObjects/Astero.h"
#include "GameObjects/Box.h"

Application::Application()
{
	mMainWindow = new Window();
	mDirectX = D3DApp::GetInstance();
	mTimer = new GameTimer();
	mAppPaused = false;
	mInput = Input::GetInstance();
}

Application::~Application()
{
	RELPTR(mTimer);
	RELPTR(mDirectX);
	RELPTR(mMainWindow);
	RELPTR(mInput);
}

void Application::Init()
{
	mMainWindow->InitWindow();
	D3DApp::GetInstance()->Init();

	for (int i = 0; i < 100; i++) {
		Box* box = new Box();
		asts.push_back(box);
	}

	for (int i = 0; i < 100; i++) {
		Astero* ast = new Astero();
		asts.push_back(ast);
	}

}

int Application::Run()
{
	MSG msg = { 0 };

	mTimer->Reset();
	bool running = true;

	// Boucle de messages principale :
	while (running)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				running = false;
		}

		mTimer->Tick();

		if (!mAppPaused)
		{
			Update(mTimer);
			Render();
			EndFrame(mTimer->DeltaTime());
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
		wstring windowText = mMainWindow->GetWindowTitle() +
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
	Engine::GetInstance()->Update(timer->DeltaTime());

	mInput->UpdateArray();

	switch (static_cast<int>(mInput->GetInputStates()[4])) {
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

void Application::Render()
{
	Engine::GetInstance()->mRenderManager->Render();
	mDirectX->Draw();
}

void Application::EndFrame(float deltaTime)
{
	GameObjectManager::GetInstance()->DeleteGameObject(mTimer->DeltaTime());
}