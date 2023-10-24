#pragma once
#include "../GameTimer.h"
#include <iostream>
#include <list>

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

	//Used to initialize an object and to not render a new one in the middle of a frame
	bool Initialized = false;

private:
	GameObject* mParent;
	std::list<GameObject*> mChildren;

	//Transform mTransform;
	//MeshGeometrie mMesh;
	//Collider mCollider;
};