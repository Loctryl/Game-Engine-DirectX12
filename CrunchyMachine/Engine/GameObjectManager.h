#pragma once
#include <vector>

class GameObject;
class GameTimer;
class Camera;
class SkyBox;

// Singleton class.
// Manages game object's statement and state function calls.
class GameObjectManager 
{
private:
	static GameObjectManager* mInstance;

	std::vector<GameObject*> mGameObjectsToInit;
	std::vector<GameObject*> mGameObjects;

	bool mToEnd = false;
	
	// Stores the camera and sky box cause it's unique game objects.
	Camera* mCamera;
	SkyBox* mSkyBox;
	
public:
	GameObjectManager();
	~GameObjectManager();

	static GameObjectManager* GetInstance();
	Camera* GetCamera() const;

	void Init();
	bool Run(GameTimer* gt);
	void DeleteGameObject(float gt);

	void AddGameObject(GameObject* go);

	void EndGame() { mToEnd = true; }
};