#include "VelocityManager.h"
#include "Engine/GameObject.h"

VelocityManager::VelocityManager()
{
	mComponentType = VELOCITY;
	mComponents = std::vector<Velocity*>();
}

VelocityManager::~VelocityManager()
{
}

void VelocityManager::Update()
{
}
