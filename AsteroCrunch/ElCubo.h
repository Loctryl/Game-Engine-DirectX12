#pragma once
#include "Engine/GameObject.h"

class ElCubo : public GameObject 
{
	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;

public:

	ElCubo();

private:
};

