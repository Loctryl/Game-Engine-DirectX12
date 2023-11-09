#pragma once
#include "Engine/Component/StateMachine/BaseState.h"

class Wandering : public BaseState {

public:
	Wandering();
	~Wandering();

	void OnStart() override;
	void OnUpdate(float deltatime) override;
	void OnEnd() override;

private:

};


class Fighting : public BaseState {

public:
	Fighting();
	~Fighting();

	void OnStart() override;
	void OnUpdate(float deltatime) override;
	void OnEnd() override;

private:

};

class Flee : public BaseState {

public:
	Flee();
	~Flee();

	void OnStart() override;
	void OnUpdate(float deltatime) override;
	void OnEnd() override;

private:

};