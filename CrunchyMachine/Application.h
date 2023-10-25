#pragma once
#include "Window/Window.h"
#include "DirectX12/D3DApp.h"
#include "GameTimer.h"
#include "Engine/GameObjectManager.h"


class Application
{
	Window mMainWindow;
	D3DApp mDirectX;
	GameTimer mTimer;

	bool mAppPaused;

	void CalculateFrameStats();

	void Update(GameTimer timer);

	void Render(GameTimer timer);

	void EndFrame(GameTimer timer);

public:
	Application();
	~Application() = default;

	void Init();

	int Run();
};

