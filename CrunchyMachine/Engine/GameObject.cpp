#include "Engine/GameObject.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Component/Transform.h"


GameObject::GameObject(GameObject* parent)
{
	mParent = parent;
	if(mParent != nullptr)
		mParent->mChildren.push_back(this);
	mChildren = std::vector<GameObject*>();

	GameObjectManager::GetInstance()->AddGameObject(this);

	mTransform = new Transform();
}

GameObject::~GameObject()
{
	Engine::GetInstance()->DeleteGameObject(this);

	for (int i = 0; i < mChildren.size(); i++) {
		GameObject* child = mChildren.back();
		child->mParent = nullptr;
		child->ToDestroy = true;
		mChildren.pop_back();
	}
	ToDestroy = true;

	delete mTransform;
}

bool GameObject::HasComponent(ComponentType componentType)
{
	return Engine::GetInstance()->HasComponent(componentType, this);
}

void GameObject::RemoveComponent(ComponentType componentType)
{
	Engine::GetInstance()->RemoveComponent(componentType, this);
}
