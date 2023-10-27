#pragma once
#include <iostream>
#include <vector>

class CollisionManager;
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
		case(collision):
			mColliderManager->AddComponent(T);
		default:
			break;
		}
	}

	template <class T = Component>
	T* GetComponent(ComponentType componentType, GameObject* go)
	{
		switch (componentType)
		{
		case(collision):
			return mColliderManager->GetComponent(go);
		default:
			break;
		}
	}

	bool  HasComponent(ComponentType componentType, GameObject* go);
	void  RemoveComponent(ComponentType componentType, GameObject* go);
	void  DeleteGameObject(GameObject* go);

	static Engine* GetInstance();

private:
	
	static Engine* mInstance;
	CollisionManager* mColliderManager;
};