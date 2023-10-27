#include "Engine.h"
#include "Engine/ComponentManager/CollisionManager.h"

Engine* Engine::mInstance = nullptr;

Engine::Engine()
{
	mColliderManager = new CollisionManager();
}

Engine::~Engine()
{
}

bool Engine::HasComponent(ComponentType componentType, GameObject* go)
{
	switch (componentType)
	{
	case(collision):
		return mColliderManager->HasComponent(go);
	default:
		break;
	}
}

void Engine::RemoveComponent(ComponentType componentType, GameObject* go)
{
	switch (componentType)
	{
	case(collision):
		mColliderManager->HasComponent(go);
	default:
		break;
	}
}

void Engine::DeleteGameObject(GameObject* go)
{
	mColliderManager->DeleteGameObject(go);
}

Engine* Engine::GetInstance()
{
	if (mInstance != nullptr) return mInstance;
	return new Engine();
}


