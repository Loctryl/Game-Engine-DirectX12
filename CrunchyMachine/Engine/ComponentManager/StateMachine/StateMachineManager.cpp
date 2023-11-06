#include "StateMachineManager.h"
#include "EngineResources/framework.h"

StateMachineManager::StateMachineManager()
{
	mComponentType = STATEMACHINE;
	mComponents = std::vector<StateMachineComponent*>();
}


StateMachineManager::~StateMachineManager()
{
}


void StateMachineManager::Update(float deltaTime)
{
	for (auto obj : mComponents) {
		obj->Update(deltaTime);
	}
}