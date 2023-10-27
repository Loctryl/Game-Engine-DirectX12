#pragma once
#include "Engine/GameTimer.h"
#include <iostream>
#include <vector>

class Transform;
class RenderComponent;

class GameObject {

public:
	GameObject(GameObject* parent = nullptr);
	~GameObject();

	void virtual OnInit(GameTimer* gt) = 0;
	void virtual OnUpdate(GameTimer* gt) = 0;
	void virtual OnDestroy(GameTimer* gt) = 0;

	//Used to destroy a gameObject at the end of the current frame
	bool ToDestroy = false;

	Transform* mTransform;
	RenderComponent* mItem;
	//Collider mCollider;

protected:
	GameObject* mParent;
	std::vector<GameObject*> mChildren;
};