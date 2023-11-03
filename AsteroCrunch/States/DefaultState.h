#pragma once
#include "Engine/Component/StateMachine/BaseState.h"

class DefaultState : public BaseState
{
public:
	DefaultState();
	~DefaultState();

	void OnStart() override;
	void OnUpdate(float deltatime) override;
	void OnEnd() override;

private:

};