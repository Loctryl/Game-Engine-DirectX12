#pragma once
#include <iostream>
#include <vector>
#include "../../CrunchyMachine/GameTimer.h"

class GameObject;


class GameObjectManager {

public:

	GameObjectManager();
	~GameObjectManager();

	static GameObjectManager* GetInstance();

	void Init();
	void Run(GameTimer* gt);
	void DeleteGameObject(GameTimer* gt);

	void AddGameObject(GameObject* go);

private:

	static GameObjectManager* mInstance;

	std::vector<GameObject*> mGameObjects;
};