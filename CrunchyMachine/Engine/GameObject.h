#pragma once
#include <vector>
#include "Engine/Engine.h"
#include "Engine/Component/Component.h"

class Transform;
class RenderComponent;

// Base class to add an entity with his own components.
// Provides virtual state function to be override by child.
class GameObject 
{
public:
	GameObject(bool isIndependent = false);
	virtual ~GameObject();

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

	inline GameObject* GetParent() const { if (mParent) return mParent; return nullptr; };
	inline bool IsIndependent() const { return mIsIndependent; };

	// Used to destroy a gameObject at the end of the current frame
	bool mToDestroy = false;

	// Transform is a mandatory component without manager.
	Transform* mTransform;

	// Refers to the GameObject ID
	BitMask* mId;

	// Fields for displaying UI, should not stay in a more advanced version
	int mDigit = -1;
	float mDivider = 0;

	std::vector<GameObject*> mChildren;

protected:
	// Is the gameObject independent to his parent
	bool mIsIndependent;
	
	GameObject* mParent;
};