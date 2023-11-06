#pragma once
#include "Engine/Component/Component.h"

class BaseState;

class StateMachineComponent : public Component 
{
private:
	BaseState* mState;

public:
	StateMachineComponent(BaseState* state);
	~StateMachineComponent();

	void SwitchState(BaseState* state);
	void Update(float deltatime);

};