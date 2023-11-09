#include "GameObjectManager.h"
#include "GameObject.h"
#include "Engine/Component/Camera.h"
#include "Engine/Component/SkyBox.h"
#include "GameTimer.h"


GameObjectManager* GameObjectManager::mInstance = nullptr;

GameObjectManager::GameObjectManager() { mCamera = nullptr; mSkyBox = nullptr; mScore = nullptr; }

GameObjectManager::~GameObjectManager()
{
	for (auto go : mGameObjects)
		RELPTR(go);
	mGameObjects.clear();

	for (auto go : mGameObjectsToInit)
		RELPTR(go);
	mGameObjectsToInit.clear();
}

GameObjectManager* GameObjectManager::GetInstance()
{
	if (mInstance != nullptr) return mInstance;
	mInstance = new GameObjectManager();
	mInstance->Init();
	return mInstance;
}

Camera* GameObjectManager::GetCamera() const { return mCamera; }

void GameObjectManager::Init()
{
	mCamera = new Camera();
	mSkyBox = new SkyBox();
}

// Called every frame 
bool GameObjectManager::Run(GameTimer* gt)
{
	// Manage game object initialization on the next frame of his call if he's call after this function.

	// Initialize game object
	for (int i = 0; i < mGameObjectsToInit.size(); i++) {
		mGameObjectsToInit[i]->OnInit();
		mGameObjects.push_back(mGameObjectsToInit[i]);
		mGameObjectsToInit.erase(mGameObjectsToInit.begin() + i);
		i--;
	}

	// Calls OnUpdate(float deltaTime); for each game object
	for (auto obj : mGameObjects)
		if (!obj->mToDestroy)
			obj->OnUpdate(gt->DeltaTime());

	if (mToEnd) return false;
	return true;
}

void GameObjectManager::DeleteGameObject(float gt)
{
	// Iteration to delete game objects
	for (int i = 0; i < mGameObjects.size(); i++) {
		if (mGameObjects[i]->mToDestroy) {
			mGameObjects[i]->OnDestroy();
			RELPTR(mGameObjects[i]);
			mGameObjects.erase(mGameObjects.begin() + i);
			i--;
		}
	}
}

void GameObjectManager::AddGameObject(GameObject* go) {	mGameObjectsToInit.push_back(go); }