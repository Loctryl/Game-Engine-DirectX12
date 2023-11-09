#include "BaseState.h"
#include "StateMachineComponent.h"
#include "EngineResources/framework.h"

StateMachineComponent::StateMachineComponent(BaseState* state)
{
	mState = state;
	mComponentType = STATE_MACHINE;
}

StateMachineComponent::~StateMachineComponent() { RELPTR(mState); }

void StateMachineComponent::SwitchState(BaseState* state)
{
	mState->OnEnd();
	RELPTR(mState);

	mState = state;
	state->SetGameObject(mGameObject);
	mState->OnStart();
}

void StateMachineComponent::Update(float deltaTime) const
{
	mState->SetGameObject(mGameObject);
	mState->OnUpdate(deltaTime);
}