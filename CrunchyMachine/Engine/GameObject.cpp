#include "GameObject.h"

GameObject::GameObject()
{
	mParent = nullptr;
	mChildren = std::list<GameObject*>();
	//mTransform = nullptr;
	//mMesh = nullptr;
	//mCollider = nullptr;
}

GameObject::GameObject(GameObject* parent)
{
	mParent = parent;
	mParent->mChildren.push_back(this);
	mChildren = std::list<GameObject*>();
	//mTransform = nullptr;
	//mMesh = nullptr;
	//mCollider = nullptr;
}

GameObject::~GameObject()
{
	for (int i = 0; i < mChildren.size(); i++) {
		GameObject* child = mChildren.back();
		child->mParent = nullptr;
		child->ToDestroy = true;
		mChildren.pop_back();
	}
	//mTransform = nullptr;
	//mMesh = nullptr;
	//mCollider = nullptr;
}
