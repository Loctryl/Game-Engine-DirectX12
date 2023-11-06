#pragma once
#include "Engine/GameObject.h"

class BaseState
{
public:

	BaseState() = default;
	~BaseState() = default;

	virtual void OnStart() = 0;
	virtual void OnUpdate(float deltatime) = 0;
	virtual void OnEnd() = 0;

	inline void SetGameObject(GameObject* gameObject) {	mGameObject = gameObject ; }

private:
	GameObject* mGameObject;
};