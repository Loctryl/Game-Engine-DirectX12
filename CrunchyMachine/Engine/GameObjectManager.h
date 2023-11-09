#pragma once
#include <iostream>
#include <vector>

class GameObject;
class GameTimer;
class Camera;
class SkyBox;
class Score;

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
	Score* mScore;
public:
	GameObjectManager();
	~GameObjectManager();

	static GameObjectManager* GetInstance();
	Camera* GetCamera() const;
	Score* GetScore() { return mScore; }

	void SetScore(Score* score) { mScore = score; }

	void Init();
	bool Run(GameTimer* gt);
	void DeleteGameObject(float gt);

	void AddGameObject(GameObject* go);

	void EndGame() { mToEnd = true; }
};