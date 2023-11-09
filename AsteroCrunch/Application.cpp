#include "Application.h"
#include "Window/Window.h"
#include "DirectX12/D3DApp.h"
#include "Engine/GameTimer.h"
#include "Engine/GameObjectManager.h"
#include "Engine/ComponentManager/RenderManager.h"
#include "Engine/Engine.h"
#include "Engine/Input.h"
#include "GameObjects/Player/SpaceShip.h"
#include "GameObjects/Environment/AsteroCreator.h"
#include "UI/Score.h"
#include "UI/CrossAir.h"
#include "UI/Life.h"
#include "GameObjects/Environment/PlanetCreator.h"
#include "GameObjects/Enemies/EnemiesCreator.h"

#include <random>


Application::Application()
{
	mMainWindow = new Window();
	mDirectX = D3DApp::GetInstance();
	mTimer = new GameTimer();
	mAppPaused = false;
	mInput = Input::GetInstance();
	mGoManager = GameObjectManager::GetInstance();
	mEngine = Engine::GetInstance();
}

Application::~Application()
{
	RELPTR(mTimer);
	RELPTR(mDirectX);
	RELPTR(mMainWindow);
	RELPTR(mInput);
	RELPTR(mGoManager);
	RELPTR(mEngine);
}

void Application::Init()
{
	srand(time(0));

	Score* uiScore = new Score();
	GameObjectManager::GetInstance()->SetScore(uiScore);
	CrossAir* uiCrossAir = new CrossAir();

	SpaceShip* ship = new SpaceShip();
	ship->SetCam(GameObjectManager::GetInstance()->GetCamera());
	ship->mLife = new Life(ship->GetMaxHp());

	EnemiesCreator* enemiesCreator = new EnemiesCreator();

	AsteroCreator* astCreator = new AsteroCreator();

	PlanetCreator* plntCreator = new PlanetCreator();
}

int Application::Run()
{
	MSG msg = { nullptr };

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
			if (!Update(mTimer)) running = false;
			Render();
			EndFrame(mTimer->DeltaTime());
		}

	}

	return (int)msg.wParam;
}

void Application::CalculateFrameStats() const
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

bool Application::Update(GameTimer* timer) const
{
    CalculateFrameStats();
	mEngine->Update(timer->DeltaTime());
	
	mInput->UpdateArray(timer->DeltaTime());

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

	if (!mGoManager->Run(timer)) { return false; }
	return true;
}

void Application::Render() const
{
	mEngine->mRenderManager->Render();
	mDirectX->Draw();
}

void Application::EndFrame(float deltaTime) const
{
	mGoManager->DeleteGameObject(mTimer->DeltaTime());
}