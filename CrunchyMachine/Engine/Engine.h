#pragma once
#include <iostream>
#include <vector>
#include "ComponentManager/RenderManager.h"
#include "ComponentManager/Physics/PhysicsManager.h"
#include "ComponentManager/StateMachine/StateMachineManager.h"
#include "ComponentManager/ScriptManager.h"

class GameObject;
class PhysicsComponent;
class RenderComponent;
class StateMachineComponent;
class Script;
enum ComponentType;

// Main class and singleton.
// Manages all the component managers.
// Also provides base fonctions for game objects to manage their components.
class Engine 
{
public:
	Engine();
	~Engine();

	// Global game object call to add a component with a given type.
	template <class T = Component>
	void  AddComponent(T* component) 
	{
		switch (component->mComponentType)
		{
		case(PHYSICS):
			mPhysicsManager->AddComponent(reinterpret_cast<PhysicsComponent*>(component));
			break;

		case(RENDER):
			mRenderManager->AddComponent(reinterpret_cast<RenderComponent*>(component));
			break;

		case(STATEMACHINE):
			mStateMachineManager->AddComponent(reinterpret_cast<StateMachineComponent*>(component));
			break;

		case(SCRIPT):
			mScriptManager->AddComponent(reinterpret_cast<Script*>(component));
			break;
		default:
			break;
		}
	}

	template <class T = Component>
	T* GetComponent(ComponentType componentType, GameObject* go)
	{
		switch (componentType)
		{
		case(PHYSICS):
			return mPhysicsManager->GetComponent(go);
			break;

		case(RENDER):
			return mRenderManager->GetComponent(go);
			break;

		case(STATEMACHINE):
			return mStateMachineManager->GetComponent(go);
			break;

		case(SCRIPT):
			return mScriptManager->GetComponent(go);
			break;
		default:
			break;
		}
	}

	void Update(float deltaTime);

	bool  HasComponent(ComponentType componentType, GameObject* go);
	void  RemoveComponent(ComponentType componentType, GameObject* go);
	void  DeleteGameObject(GameObject* go);

	static Engine* GetInstance();

	PhysicsManager* mPhysicsManager;
	RenderManager* mRenderManager;
	StateMachineManager* mStateMachineManager;
	ScriptManager* mScriptManager;

private:
	static Engine* mInstance;
};