#pragma once
#include "EngineResources/framework.h"

class GameObject;

// Base class for a component
// Stores its type and the reference of the game object linked.
class Component 
{
public:
	Component() = default;
	virtual ~Component();

	ComponentType mComponentType;
	GameObject* mGameObject;
};