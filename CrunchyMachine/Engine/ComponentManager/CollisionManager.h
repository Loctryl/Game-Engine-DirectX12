#pragma once
#include <iostream>
#include <vector>
#include "Engine/ComponentManager/ComponentManager.h"
#include "Engine/Component/Collider.h"

class GameObject;

class CollisionManager : ComponentManager<Collider>{

public:
	CollisionManager();
	~CollisionManager();

	void Update();

	void      AddComponent(Collider* component);
	Collider* GetComponent(GameObject* go);
	bool	  HasComponent(GameObject* go);
	void	  RemoveComponent(GameObject* go);
	void	  DeleteGameObject(GameObject* go);

	void AddFlag(std::wstring flag);

private:
	std::vector<std::wstring> mFlagsCollection;
};