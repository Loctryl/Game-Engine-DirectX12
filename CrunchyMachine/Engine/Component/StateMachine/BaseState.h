#pragma once

class GameObject;

// Base class for all states using the State Machine implementation
class BaseState
{
protected:
	GameObject* mGameObject;
	
public:

	BaseState();
	virtual ~BaseState();

	virtual void OnStart() = 0;
	virtual void OnUpdate(float deltaTime) = 0;
	virtual void OnEnd() = 0;

	inline void SetGameObject(GameObject* gameObject) {	mGameObject = gameObject ; }
};