#include "CollisionManager.h"
#include "Engine/Component/Collider.h"


CollisionManager::CollisionManager()
{
	mComponentType = COLLISION;
	mComponents = std::vector<Collider*>();
}

CollisionManager::~CollisionManager()
{
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