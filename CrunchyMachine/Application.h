#pragma once

class Window;
class D3DApp;
class GameTimer;


class Application
{
	Window* mMainWindow;
	D3DApp* mDirectX;
	GameTimer* mTimer;

	bool mAppPaused;

	void CalculateFrameStats();

	void Update(GameTimer* timer);

	void Render(GameTimer* timer);

	void EndFrame(GameTimer* timer);

public:
	Application();
	~Application() = default;

	void Init();

	int Run();
};

