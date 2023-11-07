#pragma once
#include "Engine/GameObject.h"


class UIElement : public GameObject
{
	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

public:
	UIElement();

	//vector<XMFLOAT4> numbersUV;
};
