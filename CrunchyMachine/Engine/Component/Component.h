#pragma once
#include "Resources/framework.h"

class GameObject;

// Base class for a component
// Stores its type and the reference of the game object linked.
class Component 
{
public:
	Component() = default;
	~Component();

	ComponentType mComponentType;
	GameObject* mGameObject;
};