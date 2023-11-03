#include "Engine/GameObjectManager.h"
#include "Engine/GameObject.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Engine/Component/Camera.h"

GameObjectManager* GameObjectManager::mInstance = nullptr;

GameObjectManager::GameObjectManager() { mCamera = nullptr; }

GameObjectManager::~GameObjectManager()
{
	for (auto go : mGameObjects)
		RELPTR(go);
	mGameObjects.clear();

	for (auto go : mGameObjectsToInit)
		RELPTR(go);
	mGameObjectsToInit.clear();

	RELPTR(mCamera);
}

GameObjectManager* GameObjectManager::GetInstance()
{
	if (mInstance != nullptr) return mInstance;
	mInstance = new GameObjectManager();
	mInstance->Init();
	return mInstance;
}

Camera* GameObjectManager::GetCamera() { return mCamera; }

void GameObjectManager::Init() { mCamera = new Camera(); }

// Called every frame 
void GameObjectManager::Run(GameTimer* gt)
{
	// Manage game object initialization on the next frame of his call if he's call after this fonction.
	std::vector<int> toUpdateIndex = std::vector<int>();
	int maxindex = mGameObjectsToInit.size();

	// Initialize game object
	for (int i = 0; i < maxindex; i++) {
		mGameObjectsToInit[i]->OnInit();
		toUpdateIndex.push_back(i);
		mGameObjects.push_back(mGameObjectsToInit[i]);
	}
	// Clear list of objects to initialize
	for (int i = 0; i < toUpdateIndex.size(); i++) {
		if (mGameObjectsToInit.size() == 1)
			mGameObjectsToInit.clear();
		else
			mGameObjectsToInit.erase(mGameObjectsToInit.begin() + toUpdateIndex[i] - i);
	}

	// Calls OnUpdate(float deltaTime); for each game object
	for (int i = 0; i < mGameObjects.size(); i++)
		if (!mGameObjects[i]->ToDestroy)
			mGameObjects[i]->OnUpdate(gt->DeltaTime());
}

void GameObjectManager::DeleteGameObject(float gt)
{
	// Same fonction above on deleting objects

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

void GameObjectManager::AddGameObject(GameObject* go) { mGameObjectsToInit.push_back(go); }