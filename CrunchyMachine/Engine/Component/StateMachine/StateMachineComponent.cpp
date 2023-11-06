#include "StateMachineComponent.h"
#include "BaseState.h"
#include "EngineResources/framework.h"

StateMachineComponent::StateMachineComponent(BaseState* state)
{
	mState = state;
	mComponentType = STATEMACHINE;
}

StateMachineComponent::~StateMachineComponent()
{
	RELPTR(mState);
}

void StateMachineComponent::SwitchState(BaseState* state)
{
	mState->OnEnd();
	mState->SetGameObject(nullptr);

	mState = state;
	state->SetGameObject(mGameObject);
	mState->OnStart();
}

void StateMachineComponent::Update(float deltatime)
{
	mState->OnUpdate(deltatime);
}
