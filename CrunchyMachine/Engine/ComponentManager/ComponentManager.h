#pragma once
#include "Engine/Component/Component.h"
#include "Resources/ComponentType.h"
#include <vector>
#include <iostream>

class GameObject;

template <class T = Component>
class ComponentManager
{
public:
	ComponentManager();
	~ComponentManager();

	void Init();

	void Update();

	void AddComponent(T* component);

	T*   GetComponent     (GameObject* go);
	bool HasComponent     (GameObject* go);
	void RemoveComponent  (GameObject* go);
	void DeleteGameObject (GameObject* go);

	ComponentType GetComponentType();

protected:

	ComponentType mComponentType;

	std::vector<T*> mComponents;

};