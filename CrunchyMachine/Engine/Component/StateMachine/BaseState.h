#pragma once

class BaseState
{
public:

	BaseState() = default;
	~BaseState() = default;

	virtual void OnStart() = 0;
	virtual void OnUpdate(float deltatime) = 0;
	virtual void OnEnd() = 0;

private:

};