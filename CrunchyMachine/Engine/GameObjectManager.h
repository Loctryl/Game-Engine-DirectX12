#pragma once
#include <iostream>
#include <vector>
#include "../../CrunchyMachine/GameTimer.h"
#include "GameObject.h"

class GameObjectManager {

public:

	GameObjectManager();
	~GameObjectManager();

	GameObjectManager* GetInstance();

	void Init();
	void Run(GameTimer* gt);
	void DeleteGameObject(GameTimer* gt);

	void AddGameObject(GameObject* go);

private:

	static GameObjectManager* mInstance;

	std::vector<GameObject*> mGameObjects;
};