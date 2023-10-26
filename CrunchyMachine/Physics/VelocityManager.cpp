#include "VelocityManager.h"
#include "../Engine/GameObject.h"

VelocityManager* VelocityManager::mInstance = nullptr;

VelocityManager::VelocityManager()
{
}

VelocityManager::~VelocityManager()
{
}

VelocityManager* VelocityManager::GetInstance()
{
	if (mInstance != nullptr) return mInstance;
	return new VelocityManager();
}

void VelocityManager::Update()
{
}
