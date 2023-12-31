#pragma once
#include "Engine/Component/StateMachine/StateMachineComponent.h"
#include "Engine/ComponentManager/ComponentManager.h"


class StateMachineManager : public ComponentManager<StateMachineComponent> {
public:
	StateMachineManager();
	~StateMachineManager() override = default;

	void Update(float deltaTime) override;
};