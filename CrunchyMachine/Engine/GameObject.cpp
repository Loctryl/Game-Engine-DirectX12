#include "GameObject.h"
#include "GameObjectManager.h"
#include "Engine/Component/Transform.h"


GameObject::GameObject(bool isIndependent)
{
	mIsIndependent = isIndependent;

	// When created, automatically added to the list of game object.
	GameObjectManager::GetInstance()->AddGameObject(this);

	mTransform = new Transform(this);
	mId = new BitMask();
}

GameObject::~GameObject()
{
	// Removes all the component of the game object.
	Engine::GetInstance()->DeleteGameObject(this);

	// Resets parent and child
	int size = mChildren.size();
	for (int i = 0; i < size; i++) {
		GameObject* child = mChildren.back();
		child->mParent = nullptr;
		child->mToDestroy = true;
		mChildren.pop_back();
	}
	mToDestroy = true;

	if (mParent) {
		std::vector<GameObject*> childrenOfParents = mParent->mChildren;

		for (int i = 0; i < childrenOfParents.size(); i++) 
			if (childrenOfParents[i] == this) 
				mParent->mChildren.erase(mParent->mChildren.begin() + i);
		
	}

	RELPTR(mTransform);
}

void GameObject::AddParent(GameObject* parent)
{
	mParent = parent;
	mParent->mChildren.push_back(this);
}

bool GameObject::HasComponent(ComponentType componentType) { return Engine::GetInstance()->HasComponent(componentType, this); }

void GameObject::RemoveComponent(ComponentType componentType) { Engine::GetInstance()->RemoveComponent(componentType, this); }
