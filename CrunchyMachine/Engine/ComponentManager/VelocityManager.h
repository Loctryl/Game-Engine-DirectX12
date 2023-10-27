#pragma once
#include <iostream>
#include <vector>
#include "Engine/ComponentManager/ComponentManager.h"
#include "Engine/Component/Velocity.h"

class GameObject;

class VelocityManager : ComponentManager<Velocity>{

public:
	VelocityManager();
	~VelocityManager();

	void Update();

private:

};