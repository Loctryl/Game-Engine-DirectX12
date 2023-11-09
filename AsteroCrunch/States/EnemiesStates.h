#pragma once
#include "Engine/Component/StateMachine/BaseState.h"
#define RANGE_DETECTION 400.f
#define ATTACK_RANGE 100.f

class Fighting : public BaseState {

public:
	Fighting(float fireRate ,float speed);
	~Fighting();

	void OnStart() override;
	void OnUpdate(float deltatime) override;
	void OnEnd() override;

private:
	GameObject* mPlayer;
	float mSpeed;
	float mFireRate;
	float mFireCooldown = 0.f;
};

class Flee : public BaseState {

public:
	Flee(float speed);
	~Flee();

	void OnStart() override;
	void OnUpdate(float deltatime) override;
	void OnEnd() override;

private:
	GameObject* mPlayer;
	float mSpeed;
};