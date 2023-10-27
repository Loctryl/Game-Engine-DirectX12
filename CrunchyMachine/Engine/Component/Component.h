#pragma once
#include "Resources/ComponentType.h"

class GameObject;

class Component {

public:

	Component() = default;
	~Component() = default;

	ComponentType mComponentType;
	GameObject* mGameObject;

private:

};