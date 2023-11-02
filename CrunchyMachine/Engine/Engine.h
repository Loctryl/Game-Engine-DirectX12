#pragma once
#include <iostream>
#include <vector>
#include "ComponentManager/RenderManager.h"
#include "Component/RenderComponent.h"
#include "ComponentManager/Physics/PhysicsManager.h"
#include "Component/PhysicsComponent.h"

class GameObject;
enum ComponentType;

class Engine {

public:

	Engine();
	~Engine();

	template <class T = Component>

	void  AddComponent(T* component) {
		switch (component->mComponentType)
		{
		case(PHYSICS):
			mPhysicsManager->AddComponent(reinterpret_cast<PhysicsComponent*>(component));
			break;

		case(RENDER):
			mRenderManager->AddComponent(reinterpret_cast<RenderComponent*>(component));
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

private:
	
	static Engine* mInstance;
};