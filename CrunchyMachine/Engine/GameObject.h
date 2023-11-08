#pragma once
#include "Engine/GameTimer.h"
#include <iostream>
#include <vector>
#include "Engine/Engine.h"
#include "Engine/Component/Component.h"

class Transform;
class RenderComponent;


// Base class to add an entity with his own components.
// Provides virtual state fonction to be override by child.
class GameObject 
{
public:
	GameObject(bool isIndependant = false);
	~GameObject();

	void virtual OnInit() = 0;
	void virtual OnUpdate(float deltaTime) = 0;
	void virtual OnDestroy() = 0;
	void virtual OnCollision(GameObject* go) = 0;

	template <class T = Component>
	void  AddComponent(T* component) 
	{
		component->mGameObject = this;
		Engine::GetInstance()->AddComponent<T>(component);
	}

	void AddParent(GameObject* parent);

	template <class T = Component>
	T* GetComponent(ComponentType componentType) { return Engine::GetInstance()->GetComponent<T>(componentType, this); }

	bool  HasComponent(ComponentType componentType);
	void  RemoveComponent(ComponentType componentType);

	inline GameObject* GetParent() { if (mParent) return mParent; return nullptr; };
	inline std::vector<GameObject*> GetChildren() { return mChildren; };
	inline bool IsIndependant() { return mIsIndependant; };

	//Used to destroy a gameObject at the end of the current frame
	bool ToDestroy = false;

	// Transform is a mandatory component without manager.
	Transform* mTransform;
	BitMask* mId;

	int mDigit = -1;

protected:
	//do the gameObject is independent to his parent
	bool mIsIndependant;


	GameObject* mParent;
	std::vector<GameObject*> mChildren;
};