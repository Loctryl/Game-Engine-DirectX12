#include "CollisionManager.h"
#include "Engine/GameObject.h"


CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Update()
{
}

void CollisionManager::AddComponent(Collider* component)
{
	mComponents.push_back(component);
}

bool CollisionManager::HasComponent(GameObject* go)
{
	for (auto collider : mComponents) {
		if(collider)
	}
}

void CollisionManager::RemoveComponent(GameObject* go)
{
}

void CollisionManager::DeleteGameObject(GameObject* go)
{
}

void CollisionManager::AddFlag(std::wstring flag)
{
	for (auto _flag : mFlagsCollection) {
		if (_flag == flag) throw new std::invalid_argument("Flag already add");
	}
	mFlagsCollection.push_back(flag);
}