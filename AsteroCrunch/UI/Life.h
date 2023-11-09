#pragma once
#include "Engine/GameObject.h"

class UIElement;

class Life : public GameObject
{
	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

public:
	Life();
	Life(int maxLife);


	vector<UIElement*> mDigits;

	void LooseLifeOnUI(int currLife);
};

