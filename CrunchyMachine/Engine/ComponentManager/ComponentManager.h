#pragma once
#include "Engine/Component/Component.h"
#include <vector>
#include <iostream>

class GameObject;

// Base class for components manager
template <class T = Component>
class ComponentManager
{
public:
	ComponentManager() { mComponentType = TEMPLATE; }

	~ComponentManager()
	{
		for (auto comp : mComponents)
			RELPTR(comp);
		mComponents.clear();
	}

	void Init();

	void Update();

	void AddComponent(T* component) { mComponents.push_back(component); }

	T* GetComponent(GameObject* go)
	{
		for (auto obj : mComponents) {
			if (obj->mGameObject == go)
				return obj;
		}
	}

	bool HasComponent(GameObject* go)
	{
		for (auto obj : mComponents) {
			if (obj->mGameObject == go)
				return true;
		}
		return false;
	}

	void RemoveComponent(GameObject* go)
	{
		for (int i = 0; i < mComponents.size(); i++) {
			if (mComponents[i]->mGameObject == go)
				if (mComponents.size() == 1)
					mComponents.clear();
				else
					mComponents.erase(mComponents.begin() + i);
		}
	}

	ComponentType GetComponentType() { return mComponentType; }

	std::vector<T*> GetComponents() { return mComponents; }

protected:
	ComponentType mComponentType;

	std::vector<T*> mComponents;
};