#include "CollisionManager.h"
#include "../Engine/GameObject.h"

CollisionManager* CollisionManager::mInstance = nullptr;

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

CollisionManager* CollisionManager::GetInstance()
{
	if (mInstance != nullptr) return mInstance;
	return new CollisionManager();
}

void CollisionManager::Update()
{
}

void CollisionManager::AddFlag(std::wstring flag)
{
	for (auto _flag : mFlagsCollection) {
		if (_flag == flag) throw new std::invalid_argument("Flag already add");
	}
	mFlagsCollection.push_back(flag);
}

void CollisionManager::ClearObjects()
{
	for (auto go : mColliderObjects) {

	}

	std::vector<int> toRemove = std::vector<int>();

	for (int i = 0; i < mColliderObjects.size(); i++) {
		if (mColliderObjects[i]->ToDestroy) {
			toRemove.push_back(i);
		}
	}

	for (int i = 0; i < toRemove.size(); i++) {
		mColliderObjects.erase(mColliderObjects.begin() + toRemove[i] - i);
	}
}
