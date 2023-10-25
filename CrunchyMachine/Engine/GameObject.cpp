#include "GameObject.h"
#include "GameObjectManager.h"

GameObject::GameObject()
{
	mParent = nullptr;
	mChildren = std::vector<GameObject*>();

	GameObjectManager::GetInstance()->AddGameObject(this);

	//mTransform = nullptr;
	//mMesh = nullptr;
	//mCollider = nullptr;
}

GameObject::GameObject(GameObject* parent)
{
	mParent = parent;
	mParent->mChildren.push_back(this);
	mChildren = std::vector<GameObject*>();

	GameObjectManager::GetInstance()->AddGameObject(this);

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
	ToDestroy = true;
	//mTransform = nullptr;
	//mMesh = nullptr;
	//mCollider = nullptr;
}
