#include "Engine/GameObject.h"
#pragma once
class Entity : public GameObject
{
	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

	int mCurrentHp;
	int mMaxHp;
public: 
	void InitMaxHp(int maxHp);
	void LoseHp(int qty);
	void GainHp(int qty);
	int GetCurrHp() { return mCurrentHp; }
	int GetMaxHp() { return mMaxHp; }

	void SetCurrHp(int amount);
};

