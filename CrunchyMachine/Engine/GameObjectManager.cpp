#include "Engine/GameObjectManager.h"
#include "Engine/GameObject.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Engine/Component/Camera.h"

GameObjectManager* GameObjectManager::mInstance = nullptr;

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{
	for (auto go : mGameObjects)
		delete go;
	mGameObjects.clear();

	for (auto go : mGameObjects)
		delete go;
	mGameObjectsToInit.clear();

	delete mCamera;
}

GameObjectManager* GameObjectManager::GetInstance()
{
	if (mInstance != nullptr) return mInstance;
	mInstance = new GameObjectManager();
	mInstance->Init();
	return mInstance;
}

Camera* GameObjectManager::GetCamera()
{
	return mCamera;
}

void GameObjectManager::Init()
{
	mCamera = new Camera();
}

void GameObjectManager::Run(GameTimer* gt)
{
	// Initialize the news games objects

	std::vector<int> toUpdateIndex = std::vector<int>();
	int maxindex = mGameObjectsToInit.size();

	for (int i = 0; i < maxindex; i++) {
		mGameObjectsToInit[i]->OnInit();
		toUpdateIndex.push_back(i);
		mGameObjects.push_back(mGameObjectsToInit[i]);
	}
	for (int i = 0; i < toUpdateIndex.size(); i++) {
		if (mGameObjectsToInit.size() == 1)
			mGameObjectsToInit.clear();
		else
			mGameObjectsToInit.erase(mGameObjectsToInit.begin() + toUpdateIndex[i] - i);
	}


	for (int i = 0; i < mGameObjects.size(); i++)
		if (!mGameObjects[i]->ToDestroy)
			mGameObjects[i]->OnUpdate(gt->DeltaTime());

}

void GameObjectManager::DeleteGameObject(float gt)
{
	std::vector<int> toRemove = std::vector<int>();

	for (int i = 0; i < mGameObjects.size(); i++) {
		if (mGameObjects[i]->ToDestroy) {
			mGameObjects[i]->OnDestroy();
			toRemove.push_back(i);
		}
	}

	
	for (int i = 0; i < toRemove.size(); i++) {
		if (mGameObjects.size() == 1)
			mGameObjects.clear();
		else
			mGameObjects.erase(mGameObjects.begin() + toRemove[i]-i);
	}
}

void GameObjectManager::AddGameObject(GameObject* go)
{
	mGameObjectsToInit.push_back(go);
}
