#include "Engine/GameObject.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Component/Transform.h"


GameObject::GameObject(bool isIndependant)
{
	mIsIndependant = isIndependant;

	// When created, automatically added to the list of game object.
	GameObjectManager::GetInstance()->AddGameObject(this);

	mTransform = new Transform(this);
	mId = new BitMask();
}

GameObject::~GameObject()
{
	// Removes all the component of the game object.
	Engine::GetInstance()->DeleteGameObject(this);

	// Resets parent and childs
	for (int i = 0; i < mChildren.size(); i++) {
		GameObject* child = mChildren.back();
		child->mParent = nullptr;
		child->ToDestroy = true;
		mChildren.pop_back();
	}
	ToDestroy = true;

	std::vector<GameObject*> childrenOfParents;

	RELPTR(mTransform);
}

void GameObject::AddParent(GameObject* parent)
{
	mParent = parent;
	mParent->mChildren.push_back(this);
}

bool GameObject::HasComponent(ComponentType componentType) { return Engine::GetInstance()->HasComponent(componentType, this); }

void GameObject::RemoveComponent(ComponentType componentType) { Engine::GetInstance()->RemoveComponent(componentType, this); }
