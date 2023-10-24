#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

GameObjectManager* GameObjectManager::GetInstance()
{
	if (mInstance != nullptr) return mInstance;
	mInstance = new GameObjectManager();
	Init();
	return mInstance;
}

void GameObjectManager::Init()
{
	mGameObjects = std::vector<GameObject*>();
}

void GameObjectManager::Run(GameTimer* gt)
{
	for (int i = 0; i < mGameObjects.size(); i++) {
		if (!mGameObjects[i]->Initialized) {
			mGameObjects[i]->OnInit(gt);
		}

		if (!mGameObjects[i]->ToDestroy) {
			mGameObjects[i]->OnUpdate(gt);
		}
	}
}

void GameObjectManager::DeleteGameObject(GameTimer* gt)
{
	std::vector<int> toRemove = std::vector<int>();
	for (int i = 0; i < mGameObjects.size(); i++) {
		if (mGameObjects[i]->ToDestroy) {
			mGameObjects[i]->OnDestroy(gt);
			mGameObjects[i]->~GameObject();
			toRemove.push_back(i);
			mGameObjects.erase(mGameObjects.begin() + i);
		}
	}

	for (int i = 0; i < toRemove.size(); i++) {
		mGameObjects.erase(mGameObjects.begin() + toRemove[i]);
	}
}

void GameObjectManager::AddGameObject(GameObject* go)
{
	mGameObjects.push_back(go);
}
