#pragma once
#include "Engine/Component/Component.h"

class Script : public Component
{
public:
	Script();
	~Script();

	void virtual OnInit() = 0;
	void virtual OnUpdate(float deltaTime) = 0;
	void virtual OnDestroy() = 0;
	void virtual OnCollision(GameObject* go) = 0;
private:

};