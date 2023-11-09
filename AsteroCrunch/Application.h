#pragma once
#include <vector>
#include "Engine/GameObject.h"

class Window;
class D3DApp;
class GameTimer;
class Camera;
class Input;
class GameObjects;
class Engine;
class GameObjectManager;

class Application
{
private:
	Window* mMainWindow;
	D3DApp* mDirectX;
	GameTimer* mTimer;
	Input* mInput;
	Engine* mEngine;
	GameObjectManager* mGoManager;

	bool mAppPaused;

	void CalculateFrameStats() const;

	bool Update(GameTimer* timer) const;

	void Render() const;

	void EndFrame(float deltaTime) const;

public:
	Application();
	~Application();

	void Init();

	int Run();
};

