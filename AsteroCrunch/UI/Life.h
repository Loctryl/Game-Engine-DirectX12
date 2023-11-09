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

	int mMaxLife = 3;

	int mCurrentLife = 3;

	vector<UIElement*> mDigits;

	void LooseLifeOnUI();
};

