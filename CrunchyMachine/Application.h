#pragma once
#include "Astero.h"

class Window;
class D3DApp;
class GameTimer;
class Camera;
class Input;

// First class of the app, for calling and instancing engine
class Application
{
	Window* mMainWindow;
	D3DApp* mDirectX;
	GameTimer* mTimer;
	Input* mInput;

	vector<GameObject*> asts;

	bool mAppPaused;

	void CalculateFrameStats();

	void Update(GameTimer* timer);

	void Render();

	void EndFrame(float timer);

public:
	Application();
	~Application();

	void Init();

	int Run();
};

