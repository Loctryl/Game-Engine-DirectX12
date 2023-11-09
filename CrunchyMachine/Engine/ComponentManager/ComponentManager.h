#pragma once
#include "Engine/Component/Component.h"
#include <vector>

class GameObject;

// Base class for components manager
template <class T = Component>
class ComponentManager
{
protected:
	ComponentType mComponentType;

	std::vector<T*> mComponents;
	
public:
	ComponentManager() { mComponentType = TEMPLATE; }

	virtual ~ComponentManager()
	{
		for (auto comp : mComponents)
			RELPTR(comp);
		mComponents.clear();
	}
	
	virtual void Update(float deltaTime) = 0;

	void AddComponent(T* component) { mComponents.push_back(component); }

	T* GetComponent(GameObject* go)
	{
		for (auto obj : mComponents) {
			if (obj->mGameObject == go)
				return obj;
		}
		return nullptr;
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
		for (int i = 0; i < mComponents.size(); i++) 
			if (mComponents[i]->mGameObject == go)
				if (mComponents.size() == 1)
					mComponents.clear();
				else
					mComponents.erase(mComponents.begin() + i);
	}

	ComponentType GetComponentType() const { return mComponentType; }

	vector<T*> GetComponents() const { return mComponents; }
};