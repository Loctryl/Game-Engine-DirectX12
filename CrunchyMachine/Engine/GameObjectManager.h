#pragma once
#include <iostream>
#include <vector>

class GameObject;
class GameTimer;
class Camera;


class GameObjectManager {

public:

	GameObjectManager();
	~GameObjectManager();

	static GameObjectManager* GetInstance();
	Camera* GetCamera();

	void Init();
	void Run(GameTimer* gt);
	void DeleteGameObject(GameTimer* gt);

	void AddGameObject(GameObject* go);

private:
	static GameObjectManager* mInstance;

	std::vector<GameObject*> mGameObjectsToInit;
	std::vector<GameObject*> mGameObjects;

	Camera* mCamera;
};