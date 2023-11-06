#include "DefaultState.h"
#include <iostream>

DefaultState::DefaultState() : BaseState()
{
}

DefaultState::~DefaultState()
{
}

void DefaultState::OnStart()
{
}

void DefaultState::OnUpdate(float deltatime)
{
	std::cout << "i'm here man fr fr" << std::endl;
}

void DefaultState::OnEnd()
{
}
