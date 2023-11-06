#include "DefaultState.h"
#include <iostream>
#include "EngineResources/framework.h"

DefaultState::DefaultState()
{
	mGameObject = nullptr;
}

DefaultState::~DefaultState()
{
}

void DefaultState::OnStart()
{
}

void DefaultState::OnUpdate(float deltatime)
{
	//std::cout << "i'm here man fr fr" << std::endl;
}

void DefaultState::OnEnd()
{
}
