#pragma once
#include "Engine/Component/Component.h"

class BaseState;

// Component that manages states for a game objet
class StateMachineComponent : public Component 
{
private:
	BaseState* mState;

public:
	StateMachineComponent(BaseState* state);
	~StateMachineComponent() override;

	void SwitchState(BaseState* state);
	void Update(float deltaTime) const;
};