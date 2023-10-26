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
