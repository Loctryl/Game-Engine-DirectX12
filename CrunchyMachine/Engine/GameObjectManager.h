#pragma once
#include <iostream>
#include <vector>

class GameObject;
class GameTimer;
class Camera;

// Singleton class.
// Manages game object's statement and state fonction calls.
class GameObjectManager 
{
public:
	GameObjectManager();
	~GameObjectManager();

	static GameObjectManager* GetInstance();
	Camera* GetCamera();

	void Init();
	void Run(GameTimer* gt);
	void DeleteGameObject(float gt);

	void AddGameObject(GameObject* go);

private:
	static GameObjectManager* mInstance;

	std::vector<GameObject*> mGameObjectsToInit;
	std::vector<GameObject*> mGameObjects;

	// Stores the camera cause it's a unique game object.
	Camera* mCamera;
};