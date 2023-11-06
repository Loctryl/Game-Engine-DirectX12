#pragma once
#include "Engine/ComponentManager/ComponentManager.h"
#include "Engine/Component/ScriptComponent.h"

class GameObject;

class ScriptManager : public ComponentManager<Script>
{
private:
public:

	ScriptManager();
	~ScriptManager();

	void AddComponent(Script* script) override;
	void RemoveComponent(GameObject* go)override;

	void Update(float deltaTime);
};