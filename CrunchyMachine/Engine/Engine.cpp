#include "Engine.h"
#include "Component/RenderComponent.h"
#include "GameObject.h"

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

Engine* Engine::GetInstance()
{
	if (mInstance != nullptr) return mInstance;
	mInstance = new Engine();
	return mInstance;
}

void Engine::Update(float deltaTime) const
{
	mPhysicsManager->Update(deltaTime);
	mRenderManager->Update(deltaTime);
	mStateMachineManager->Update(deltaTime);
}

bool Engine::HasComponent(ComponentType componentType, GameObject* go) const
{
	switch (componentType)
	{
	case(PHYSICS):
		return mPhysicsManager->HasComponent(go);
	case(RENDER):
		return mRenderManager->HasComponent(go);
	case(STATEMACHINE):
		return mStateMachineManager->HasComponent(go);
	default:
		return false;
	}
}

// Delete attributed component
void Engine::RemoveComponent(ComponentType componentType, GameObject* go) const
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
void Engine::DeleteGameObject(GameObject* go) const
{
	mPhysicsManager->RemoveComponent(go);
	mRenderManager->RemoveComponent(go);
	mStateMachineManager->RemoveComponent(go);
}


