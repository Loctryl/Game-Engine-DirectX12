#include "StateMachineManager.h"
#include "EngineResources/framework.h"

StateMachineManager::StateMachineManager()
{
	mComponentType = STATE_MACHINE;
	mComponents = std::vector<StateMachineComponent*>();
}


void StateMachineManager::Update(float deltaTime)
{
	for (auto obj : mComponents) 
		obj->Update(deltaTime);
}
