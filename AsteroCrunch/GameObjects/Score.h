#pragma once
#include "Engine/GameObject.h"

class UIDigit;

class Score : public GameObject
{
	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

public:
	Score();

	int mScore;
	vector<UIDigit*> mDigits;

	void SetDigits(int num);
};

