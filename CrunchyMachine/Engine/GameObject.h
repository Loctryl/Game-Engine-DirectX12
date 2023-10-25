#pragma once
#include "GameTimer.h"
#include "GameTimer.h"
#include <iostream>
#include <vector>

class GameObject {

public:
	GameObject();
	GameObject(GameObject* parent);
	~GameObject();

	void virtual OnInit(GameTimer* gt) = 0;
	void virtual OnUpdate(GameTimer* gt) = 0;
	void virtual OnDestroy(GameTimer* gt) = 0;

	//Used to destroy a gameObject at the end of the current frame
	bool ToDestroy = false;

protected:
	GameObject* mParent;
	std::vector<GameObject*> mChildren;

	//Transform mTransform;
	//RenderItem mItem;
	//Collider mCollider;
};