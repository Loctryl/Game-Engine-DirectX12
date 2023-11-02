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
	GameObject(GameObject* parent = nullptr, bool isIndependant = false);
	~GameObject();

	void virtual OnInit(GameTimer* gt) = 0;
	void virtual OnUpdate(GameTimer* gt) = 0;
	void virtual OnDestroy(GameTimer* gt) = 0;
	void virtual OnCollision(GameObject* go) = 0;

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

	inline GameObject* GetParent() { if (mParent) return mParent; return nullptr; };
	inline std::vector<GameObject*> GetChildren() { return mChildren; };
	inline bool IsIndependant() { return mIsIndependant; };

	//Used to destroy a gameObject at the end of the current frame
	bool ToDestroy = false;

	Transform* mTransform;

protected:
	//do the gameObject is independent to his parent
	bool mIsIndependant;

	GameObject* mParent;
	std::vector<GameObject*> mChildren;
};