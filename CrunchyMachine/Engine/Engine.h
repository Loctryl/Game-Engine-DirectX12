#pragma once
#include <iostream>
#include <vector>
#include "ComponentManager/CollisionManager.h"
#include "ComponentManager/VelocityManager.h"
#include "ComponentManager/RenderManager.h"
#include "Component/Collider.h"
#include "Component/Velocity.h"
#include "Component/RenderComponent.h"

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
		case(COLLISION):
			mColliderManager->AddComponent(reinterpret_cast<Collider*>(component));
			break;

		case(VELOCITY):
			mVelocityManager->AddComponent(reinterpret_cast<Velocity*>(component));
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
		case(COLLISION):
			return mColliderManager->GetComponent(go);
			break;

		case(VELOCITY):
			return mVelocityManager->GetComponent(go);
			break;

		case(RENDER):
			return mRenderManager->GetComponent(go);
			break;
		default:
			break;
		}
	}

	bool  HasComponent(ComponentType componentType, GameObject* go);
	void  RemoveComponent(ComponentType componentType, GameObject* go);
	void  DeleteGameObject(GameObject* go);

	static Engine* GetInstance();

	CollisionManager* mColliderManager;
	VelocityManager* mVelocityManager;
	RenderManager* mRenderManager;

private:
	
	static Engine* mInstance;
};