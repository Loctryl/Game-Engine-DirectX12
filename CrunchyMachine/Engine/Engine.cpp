#include "Engine.h"

Engine* Engine::mInstance = nullptr;

Engine::Engine()
{
	mPhysicsManager = new PhysicsManager();
	mRenderManager = new RenderManager();
	mStateMachineManager = new StateMachineManager();
}

Engine::~Engine()
{
	RELPTR(mPhysicsManager);
	RELPTR(mRenderManager);
	RELPTR(mStateMachineManager);
}

void Engine::Update(float deltaTime)
{
	mPhysicsManager->Update(deltaTime);
	mRenderManager->Update(deltaTime);
	mStateMachineManager->Update(deltaTime);
}

bool Engine::HasComponent(ComponentType componentType, GameObject* go)
{
	switch (componentType)
	{
	case(PHYSICS):
		return mPhysicsManager->HasComponent(go);
		break;

	case(RENDER):
		return mRenderManager->HasComponent(go);
		break;

	case(STATEMACHINE):
		return mStateMachineManager->HasComponent(go);
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
	case(PHYSICS):
		mPhysicsManager->RemoveComponent(go);
		break;

	case(RENDER):
		mRenderManager->RemoveComponent(go);
		break;

	case(STATEMACHINE):
		mStateMachineManager->RemoveComponent(go);
		break;

	default:
		break;
	}
}

// Removes the components of a game object.
void Engine::DeleteGameObject(GameObject* go)
{
	mPhysicsManager->RemoveComponent(go);
	mRenderManager->RemoveComponent(go);
	mStateMachineManager->RemoveComponent(go);
}

Engine* Engine::GetInstance()
{
	if (mInstance != nullptr) return mInstance;
	mInstance = new Engine();
	return mInstance;
}


