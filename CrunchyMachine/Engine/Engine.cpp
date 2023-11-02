#include "Engine.h"
#include "Engine/ComponentManager/CollisionManager.h"
#include "Engine/ComponentManager/RenderManager.h"
#include "Engine/ComponentManager/VelocityManager.h"

Engine* Engine::mInstance = nullptr;

Engine::Engine()
{
	mColliderManager = new CollisionManager();
	mVelocityManager = new VelocityManager();
	mRenderManager = new RenderManager();
}

Engine::~Engine()
{
	RELPTR(mColliderManager);
	RELPTR(mVelocityManager);
	RELPTR(mRenderManager);

	RELPTR(mInstance);
}

bool Engine::HasComponent(ComponentType componentType, GameObject* go)
{
	switch (componentType)
	{
	case(COLLISION):
		return mColliderManager->HasComponent(go);
		break;

	case(VELOCITY):
		return mVelocityManager->HasComponent(go);
		break;

	case(RENDER):
		return mRenderManager->HasComponent(go);
		break;
	default:
		return false;
		break;
	}
}

void Engine::RemoveComponent(ComponentType componentType, GameObject* go)
{
	switch (componentType)
	{
	case(COLLISION):
		mColliderManager->RemoveComponent(go);
		break;

	case(VELOCITY):
		mVelocityManager->RemoveComponent(go);
		break;

	case(RENDER):
		mRenderManager->RemoveComponent(go);
		break;

	default:
		break;
	}
}

// Removes the components of a game object.
void Engine::DeleteGameObject(GameObject* go)
{
	mColliderManager->RemoveComponent(go);
	mVelocityManager->RemoveComponent(go);
	mRenderManager->RemoveComponent(go);
}

Engine* Engine::GetInstance()
{
	if (mInstance != nullptr) return mInstance;
	mInstance = new Engine();
	return mInstance;
}


