#pragma once
#include "Engine/GameTimer.h"
#include <iostream>
#include <vector>
#include "Engine/Engine.h"
#include "Engine/Component/Component.h"

class Transform;
class RenderComponent;

class GameObject {

public:
	GameObject(GameObject* parent = nullptr);
	~GameObject();

	void virtual OnInit(GameTimer* gt) = 0;
	void virtual OnUpdate(GameTimer* gt) = 0;
	void virtual OnDestroy(GameTimer* gt) = 0;

	template <class T = Component>
	void  AddComponent(T* component) {
		component->mGameObject = this;
		Engine::GetInstance()->AddComponent<T>(component);
	}

	template <class T = Component>
	T* GetComponent(ComponentType componentType)
	{
		return Engine::GetInstance()->GetComponent<T>(componentType, this);
	}

	bool  HasComponent(ComponentType componentType);
	void  RemoveComponent(ComponentType componentType);

	//Used to destroy a gameObject at the end of the current frame
	bool ToDestroy = false;

	Transform* mTransform;

protected:
	GameObject* mParent;
	std::vector<GameObject*> mChildren;
};