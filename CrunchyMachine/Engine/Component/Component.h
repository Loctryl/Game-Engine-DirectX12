#pragma once
#include "Resources/ComponentType.h"

class GameObject;

class Component {
public:

	Component() = default;
	~Component();

	ComponentType mComponentType;
	GameObject* mGameObject;
};